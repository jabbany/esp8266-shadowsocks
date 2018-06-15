#include "proto.hpp"

void close_local(WiFiClient *c, SSConnection *connection) {
  connection->localState = LOCAL_RESET;
  c->flush();
  c->stop();
}

uint8_t connect_remote (WiFiClient *remote, SSConnection *connection) {
  if (connection->localState != LOCAL_READY) {
    return RC_NOT_READY; // No point in connecting since local was not ready
  }
  *remote = WiFiClient();
  switch(connection->addrType) {
    case ADDR_TYPE_IPV4:
      byte ip[4];
      memcpy(ip, connection->host, 4);
      return remote->connect(ip, connection->port) ? RC_SUCCESS : RC_HOST_UNREACHABLE;
    case ADDR_TYPE_DOMAIN:
      return remote->connect((char*) connection->host, connection->port) ?
        RC_SUCCESS : RC_HOST_UNREACHABLE;
    case ADDR_TYPE_IPV6:
    default:
      return RC_ADDR_TYPE_NOT_SUPPORTED;
  }
}

void negotiate_socks5 (WiFiClient *local, SSConnection *connection, uint8_t i) {
  switch(connection->localState) {
    case LOCAL_RESET:
      s_log(WARN, F("Attempting to negotiate reset connection"), i);
      return; // Can't negotiate with no connection
    case LOCAL_AWAIT_GREETING:
      connection->localState = local->read() == SOCKS_VERSION ? LOCAL_AWAIT_AUTH : LOCAL_RESET;
      if (connection->localState == LOCAL_RESET) {
        s_log(WARN, F("SOCKS version fail. Reset."), i);
        close_local(local, connection);
        return;
      }
    case LOCAL_AWAIT_AUTH:
      if (!local->available()) {
        return;
      }
      if (connection->authLen == 0) {
        connection->authLen = local->read();
        if (connection->authLen == 0) {
          local->write(_socks_auth_fail, 2);
          close_local(local, connection);
          return;
        }
      }
      while (local->available() && connection->authLen > 0) {
        if (local->read() == SOCKS_AUTH_NO_AUTHENTICATION) {
          local->write(_socks_auth_accept_noauth, 2);
          local->flush();
          connection->localState = LOCAL_AWAIT_REQ;
        }
        connection->authLen -= 1;
      }
      return;
    case LOCAL_AWAIT_REQ:
      if (!local->available()) {
        return;
      }
      while(connection->authLen > 0 && local->available()) {
        local->read(); // Consume the remaining auth stuff
        connection->authLen -= 1;
      }
      if (local->available() && local->read() != SOCKS_VERSION) {
        s_log(WARN, F("SOCKS Protocol Error"), i);
        local->write(_socks_error_proto, 10);
        close_local(local, connection); 
        return;
      } else {
        connection->localState = LOCAL_AWAIT_CMD;
      }
    case LOCAL_AWAIT_CMD:
      if (local->available() < 2) {
        return;
      }
      if (local->read() != SOCKS_CMD_TCP) {
        s_log(WARN, F("Unsupported SOCKS command"), i);
        local->write(_socks_error_proto, 10);
        close_local(local, connection);
        return;
      }
      if (local->read() != 0) {
        s_log(WARN, F("SOCKS Protocol Error: Reserved field"), i);
        local->write(_socks_error_proto, 10);
        close_local(local, connection);
        return;
      }
      connection->localState = LOCAL_AWAIT_ATYP;
    case LOCAL_AWAIT_ATYP:
      if (!local->available()) {
        return;
      }
      connection->addrType = local->read();
      if (connection->addrType != ADDR_TYPE_IPV4 &&
        connection->addrType != ADDR_TYPE_DOMAIN &&
        connection->addrType != ADDR_TYPE_IPV6) {
    
        s_log(WARN, F("SOCKS Protocol Error: Addr type"), i);
        local->write(_socks_error_proto, 10);
        close_local(local, connection);
        return;
      }
      connection->hostRead = 0;
      connection->hostLen = 0;
      connection->localState = LOCAL_AWAIT_ADDR;
    case LOCAL_AWAIT_ADDR:
      if (!local->available()) {
        return;
      }
      if (connection->addrType == ADDR_TYPE_DOMAIN) {
        if (connection->hostLen == 0) {
          connection->hostLen = local->read();
          if (connection->hostLen == 0) {
            s_log(WARN, F("SOCKS Protocol Error: Host Length Zero"), i);
            local->write(_socks_error_proto, 10);
            close_local(local, connection);
            return;
          }
        }
        while (local->available() && 
          connection->hostRead < connection->hostLen) {

          connection->hostRead += 1;
          connection->host[connection->hostRead - 1] = local->read();
        }
        if (connection->hostRead < connection->hostLen) {
          return; // Need to read more, but no data available yet
        }
        connection->host[connection->hostLen] = '\0';
      } else if (connection->addrType == ADDR_TYPE_IPV4) {
        if (local->available() < 4) {
          return; // Wait for mode data
        }
        local->readBytes(connection->host, 4);
      } else if (connection->addrType == ADDR_TYPE_IPV6) {
        if (local->available() < 16) {
          return;
        }
        local->readBytes(connection->host, 16);
      }
      if (local->available() < 2) {
        return; // Need to read more for port
      }
      connection->port = local->read() * 256 + local->read();
      connection->localState = LOCAL_READY;
    case LOCAL_READY:
      return; // Connection is ready, no need to negotiate
    default:
      s_log(WARN, F("Bad local state. Disconnecting."), i);
      close_local(local, connection);
      return;
  }
}
