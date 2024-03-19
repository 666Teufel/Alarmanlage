// CustomCAN.h
#ifndef CustomCAN_h
#define CustomCAN_h

#include <Arduino.h>
#include <ArduinoCAN.h>

class CustomCAN {
public:
  CustomCAN(int rxPin, int txPin, int canId);

  void sendMessage(int messageId, const uint8_t* data, uint8_t length);
  bool receiveMessage();
  virtual void handleMessage(int messageId, const uint8_t* data, uint8_t length);

private:
  int canId;
};

#endif
