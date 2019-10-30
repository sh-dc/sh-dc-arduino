//TODO: initialize time before we can use it
//#include <time.h>
//TODO: remove when switching to <time.h>
#include <Arduino.h>
uint32_t time(uint32_t param) { return millis() / 1000; }
