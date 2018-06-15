#include "logger.hpp"

void s_log(uint8_t type, const __FlashStringHelper* message, uint16_t cid) {
  if (type == WARN) {
    Serial.print(F("WARN: "));
  } else if (type == ERR) {
    Serial.print(F(" ERR: "));
  } else {
    Serial.print(F(" LOG: "));
  }
  Serial.print(message);
  Serial.print(F(" ("));
  Serial.print(cid);
  Serial.println(F(")"));
  #if ALWAYS_FLUSH_LOGS == 1
  Serial.flush();
  #endif
}

void r_log(uint8_t addrType, char* host,uint16_t port, uint8_t i) {
  Serial.print(F(" LOG: Connecting to remote "));
  if (addrType == ADDR_TYPE_DOMAIN) {
    Serial.print(host);
  } else if (addrType == ADDR_TYPE_IPV4) {
    Serial.print(host[0], DEC);
    Serial.print(".");
    Serial.print(host[1], DEC);
    Serial.print(".");
    Serial.print(host[2], DEC);
    Serial.print(".");
    Serial.print(host[3], DEC);
  }
  Serial.print(":");
  Serial.print(port);
  Serial.print(" (");
  Serial.print(i);
  Serial.println(")");
  Serial.flush();
}

void show_config(uint16_t ss_port) {
  Serial.print(F("Shadowsocks Server listening at "));
  Serial.print(WiFi.localIP());
  Serial.print(F(":"));
  Serial.println(ss_port, DEC);
}
