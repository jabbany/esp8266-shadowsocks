#include<stdint.h>
#include <ESP8266WiFi.h>

#define LOG 0
#define WARN 1
#define ERR 2

void s_log(uint8_t type, const __FlashStringHelper* message, uint16_t cid);
void r_log(char* host,uint16_t port, uint8_t i);
