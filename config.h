
/** Below are WiFi configurations **/
#define SS_MAX_CONNECTIONS 64
#define SS_SERVER_PORT 8080
/*
 * SS_ENCRYPTION - Configure what encryption to use
 * NOTE: This changes macro behavior!
 *  0 - none (DEBUGGING USE ONLY!), IV=0, greeting = 0
 *  1 - none (ss cleartext, DEBUGGING USE ONLY!), IV=0
 *  2 - none (socks5 cleartext, DEBUGGING USE ONLY!), IV=0
 *  10 - reserved, IV=12
 *  11 - chacha20-ietf, IV=12
 *  12 - chacha20-ietf-poly1305 (AEAD, experimental)
 *  21 - reserved, IV=16
 *  22 - aes-128-ctr, IV=16
 */
#define SS_ENCRYPTION 2

#define SS_PRINT_CONFIG 1

/** Below are WiFi configurations **/
const char* wifi_ssid = "netlab-2";
const char* wifi_password = "thisisnotyournetwork";

#define WIFI_RETRY_DELAY 500
#define WIFI_RETRY_COUNT 32


/** Below are system configurations **/
#define BUFFER_SIZE 4096
// Set this to 1 to evenly service all the connections (only copy as much as buffer per round)
#define LIMIT_TO_BUFFER 1
