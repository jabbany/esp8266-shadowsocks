#include <stdint.h>
#include <ESP8266WiFi.h>
#include "ssimpl.h"

#ifndef _LOGGER
#define _LOGGER
  #define LOG 0
  #define WARN 1
  #define ERR 2
  
  void s_log(uint8_t type, const __FlashStringHelper* message, uint16_t cid);
  void r_log(uint8_t addrType, char* host,uint16_t port, uint8_t i);
  void show_config(uint16_t ss_port);
#endif
