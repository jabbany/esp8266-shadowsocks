#include <stdint.h>
#include <ESP8266WiFi.h>
#include "ssimpl.h"
#include "logger.hpp"

#define RC_SUCCESS 0
#define RC_ADDR_TYPE_NOT_SUPPORTED 1
#define RC_HOST_UNREACHABLE 2
#define RC_NOT_READY 3

void close_local (WiFiClient *local, SSConnection *connection);
uint8_t connect_remote (WiFiClient *remote, SSConnection *connection);
void negotiate_socks5 (WiFiClient *local, SSConnection *connection, uint8_t i);
