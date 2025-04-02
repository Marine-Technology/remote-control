#ifndef ELRS_H
#define ELRS_H

#include <Arduino.h>

bool initElrs();

void elrsUpdate();

unsigned int getChannel(uint8_t channelNum);

bool isRadioConnected();

#endif
