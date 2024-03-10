#include "esp32_can_builtin.h"

extern ESP32CAN CAN0;

extern volatile uint32_t biIntsCounter;
extern volatile uint32_t biReadFrames;

#define Can0 CAN0
//#define Can1 CAN1