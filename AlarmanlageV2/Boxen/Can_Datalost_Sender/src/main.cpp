#include <ACAN_ESP32.h>

#define CAN_ID 0x123
#define CAN_BUS_SPEED 250000

static uint32_t gSentValue = 0;

void setup() {
  Serial.begin(115200);
  ACAN_ESP32_Settings settings(CAN_BUS_SPEED);
  const uint32_t errorCode = ACAN_ESP32::can.begin(settings);
  if (errorCode == 0) {
    Serial.println("CAN initialization successful");
  } else {
    Serial.print("CAN initialization error 0x");
    Serial.println(errorCode, HEX);
  }
}

void loop() {
  CANMessage message;
  message.id = CAN_ID;
  message.len = sizeof(gSentValue);
  message.data[0] = gSentValue & 0xFF;
  message.data[1] = (gSentValue >> 8) & 0xFF;
  message.data[2] = (gSentValue >> 16) & 0xFF;
  message.data[3] = (gSentValue >> 24) & 0xFF;

  ACAN_ESP32::can.tryToSend(message);
  gSentValue++;
  delay(1000); // Adjust delay as needed
}
