/** Some handy macros **/
#define Min(a,b) ((a) > (b) ? (b) : (a))
#define Max(a,b) ((a) > (b) ? (a) : (b))


struct SSConnection {
  uint8_t localState;
  uint8_t remoteState;
  uint8_t host[256];
  uint16_t port;
#if SS_ENCRYPTION == 2
  uint8_t authLen;
  uint8_t hostType;
  uint8_t hostRead;
  uint8_t hostLen;
#endif
#if SS_ENCRYPTION >= 10 && SS_ENCRYPTION < 20
  uint8_t iv[12];
  uint8_t hostLen;
  uint8_t host[256];
  uint16_t port;
#endif
};

/* States for LOCAL */
// shared
#define LOCAL_RESET 0
#define LOCAL_READY 1
#define LOCAL_COMPLETE 2
#define LOCAL_AWAIT_GREETING 3
#define LOCAL_AWAIT_ATYP 4
#define LOCAL_AWAIT_ADDR 5

// Socks stuff
#define LOCAL_AWAIT_AUTH 10
#define LOCAL_AWAIT_REQ 11
#define LOCAL_AWAIT_CMD 12

// SS states
#define LOCAL_AWAIT_IV 20

/* States for REMOTE */
#define REMOTE_RESET 0
#define REMOTE_CONNECTED 1

/* Some constants for the various protocols */
#define SOCKS_VERSION 5
#define SOCKS_AUTH_NO_AUTHENTICATION 0
#define SOCKS_AUTH_NEGOTIATE_FAIL 255

#define SOCKS_CMD_TCP 1
#define SOCKS_CMD_BIND 2
#define SOCKS_CMD_UDP 3

#define ADDR_TYPE_IPV4 1
#define ADDR_TYPE_DOMAIN 3
#define ADDR_TYPE_IPV6 4

/* Some extra consts */
#if SS_ENCRYPTION == 2
const uint8_t _socks_auth_fail[] = {
  SOCKS_VERSION, SOCKS_AUTH_NEGOTIATE_FAIL
};
const uint8_t _socks_auth_accept_noauth[] = {
  SOCKS_VERSION, SOCKS_AUTH_NO_AUTHENTICATION
};
const uint8_t _socks_error_proto[] = {
  SOCKS_VERSION, 7, 0, ADDR_TYPE_IPV4, 0, 0, 0, 0, 0, 0
};
const uint8_t _socks_error_generic[] = {
  SOCKS_VERSION, 1, 0, ADDR_TYPE_IPV4, 0, 0, 0, 0, 0, 0
};
const uint8_t _socks_connection_fail[] = {
  SOCKS_VERSION, 4, 0, ADDR_TYPE_IPV4, 0, 0, 0, 0, 0, 0
};
const uint8_t _socks_connection_success[] = {
  SOCKS_VERSION, 0, 0, ADDR_TYPE_IPV4, 0, 0, 0, 0, 0, 0
};
#endif
