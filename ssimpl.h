#define min(a, b) (a > b ? b : a)

struct SSConnection {
  uint8_t localState;
  uint8_t remoteState;
};

#define LOCAL_RESET 0

#define LOCAL_CONNECTED 1

#define LOCAL_AWAIT_SOCKS_GREETING 10
#define LOCAL_AWAIT_SOCKS_

#define REMOTE_RESET 0
#define REMOTE_AWAIT_ADDRESS 1
#define REMOTE_AWAIT_PORT 2
#define REMOTE_CONNECTED 3
