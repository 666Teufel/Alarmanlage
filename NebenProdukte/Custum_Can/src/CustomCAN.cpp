// CustomCAN.cpp
#include "CustomCAN.h"

CustomCAN::CustomCAN(int rxPin, int txPin, int canId) : canId(canId) {
  Can0.begin(CAN_SPEED_500KBPS, rxPin, txPin);
}

void CustomCAN::sendMessage(int messageId, const uint8_t* data, uint8_t length) {
  CAN_message_t msg;
  msg.id = canId + messageId;
  msg.len = length;
  memcpy(msg.buf, data, length);

  Can0.write(msg);
}

bool CustomCAN::receiveMessage() {
  CAN_message_t msg;
  if (Can0.read(msg)) {
    if (msg.id >= canId && msg.id < canId + 0x800) {
      handleMessage(msg.id - canId, msg.buf, msg.len);
      return true;
    }
  }
  return false;
}
