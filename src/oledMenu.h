#ifndef OLED_MENU_H
#define OLED_MENU_H

#include <Arduino.h>

void drawIcon8x8(byte index);

void initOled();

void updateOledMenu(bool loading, float inputVoltage, byte mode, bool elrsConnected);

byte getMode(unsigned int channel7);

#endif