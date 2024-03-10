#include "esp32_can.h"

// The objects in here are defined weak now. If you're using an EVTV board you need to do nothing.
// If you're using something else that uses different pins then just go ahead and redefine
// the objects with whichever pins you need.

// Set these to the proper pin numbers for you board. Set by default to correct for EVTV ESP32-Due
// rxpin       txpin
ESP32CAN __attribute__((weak)) CAN0(GPIO_NUM_44, GPIO_NUM_43);

// Select and uncomment the proper module you've got connected via SPI
