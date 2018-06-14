#include "logger.hpp"

void s_log(uint8_t type, const __FlashStringHelper* message, uint16_t cid) {
  if (type == WARN) {
    Serial.print("WARN: ");
  } else if (type == ERR) {
    Serial.print(" ERR: ");
  } else {
    Serial.print(" LOG: ");
  }
  Serial.print(message);
  Serial.print(" (");
  Serial.print(cid);
  Serial.println(")");
  Serial.flush();
}

void r_log(char* host,uint16_t port, uint8_t i) {
  Serial.print(" LOG: Connecting to remote ");
  Serial.print(host);
  Serial.print(":");
  Serial.print(port);
  Serial.print(" (");
  Serial.print(i);
  Serial.println(")");
  Serial.flush();
}
