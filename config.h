
/** Below are WiFi configurations **/
#define SS_MAX_CONNECTIONS 8
#define SS_SERVER_PORT 8080
/*
 * SS_ENCRYPTION - Configure what encryption to use
 *  0 - none (DEBUGGING USE ONLY!), IV=0
 *  1 - none (socks5 cleartext, DEBUGGING USE ONLY!), IV=0
 *  2 - reserved, IV=12
 *  3 - chacha20-ietf, IV=12
 *  4 - reserved, IV=16
 *  5 - aes-128-ctr, IV=16
 *  6 - chacha20-ietf-poly1305 (AEAD, experimental)
 */
#define SS_ENCRYPTION 8

#define SS_PRINT_CONFIG 1

/** Below are WiFi configurations **/
const char* wifi_ssid = "netlab-2";
const char* wifi_password = "thisisnotyournetwork";

#define WIFI_RETRY_DELAY 5000
#define WIFI_RETRY_COUNT 32


/** Below are system configurations **/
#define BUFFER_SIZE 2048
