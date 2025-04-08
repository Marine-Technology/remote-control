#include <Arduino.h>
#include "elrs.h"
#include "oledMenu.h"
#include "settings.h"


void setup() {
    Serial.begin(9600);

    initOled();
    updateOledMenu(true, MODE_NOT_SET, false);
    initElrs();

    // Loading screen
    for (uint8_t _ = 0; _ < 4; ++_) {
        delay(350);
        updateOledMenu(true, MODE_NOT_SET, false);
    }
}

void loop() {
    static uint8_t iter = 0;
    static float lastVoltage = 0;
    static unsigned int mode = MODE_NOT_SET;

    bool needOledUpdate = false;
    ++iter;

    elrsUpdate();

    for (uint8_t channelNum = 1; channelNum <= 10; channelNum++) {
        unsigned int channel = getChannel(channelNum);

        if (channelNum == 8) {
            byte currentMode = getMode(channel);
            if (currentMode != mode) {
                needOledUpdate = true;
                mode = currentMode;
            }
        }

        Serial.print(channel);
        if (channelNum < 10) Serial.print(";");
    }
    Serial.println();

    if (needOledUpdate || (iter % 51) == 0) {
        updateOledMenu(false, mode, true);
    }

    if (!(iter % 10) && !isRadioConnected()) {
        while (true) {
            elrsUpdate();
            if (isRadioConnected()) break;
            Serial.println("0;0;0;0;0;0;0;0;0;0");
            updateOledMenu(false, MODE_NOT_SET, false);
        }
    }
}
