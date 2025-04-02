#include "Arduino.h"
#include "oledMenu.h"
#include "settings.h"
#include <GyverOLED.h>


GyverOLED<SSD1306_128x64, OLED_BUFFER> oled(0x3C);


const static uint8_t icons_8x8[][8] PROGMEM = {
    {0x00, 0xe0, 0x00, 0xf0, 0x00, 0xfc, 0x00, 0xff}, // 0 connected icon
    {0xc0, 0xa0, 0x90, 0x88, 0x84, 0x82, 0x01, 0xbd}, // 1 not connected icon
    {0xe7, 0x81, 0x81, 0x00, 0x00, 0x81, 0x81, 0xe7}, // 2 loading 1
    {0x24, 0x24, 0xe7, 0x00, 0x00, 0xe7, 0x24, 0x24}, // 3 loading 2
    {0xe0, 0xfc, 0xfe, 0xa3, 0xfe, 0xfc, 0xe0, 0x00}, // 4 mode not set
    {0x1c, 0x3e, 0x73, 0xe1, 0xe1, 0x73, 0x3e, 0x1c}, // 5 mode acro
    {0x18, 0x18, 0x24, 0xc3, 0xc3, 0x24, 0x18, 0x18}, // 6 mode stabilized
};


void drawIcon8x8(byte index) {
    size_t s = sizeof icons_8x8[index];
    for(unsigned int i = 0; i < s; i++) {
        oled.drawByte(pgm_read_byte(&(icons_8x8[index][i])));
    }
}


void initOled() {
    oled.init();
    oled.setContrast(255);
}


byte getMode(unsigned int channel7) {
    if (channel7 < 500) return MODE_NOT_SET;
    if (channel7 < 1500) return MODE_ACRO;
    return MODE_STABILIZED;
}


void updateOledMenu(bool loading, float inputVoltage, byte mode, bool elrsConnected) {
    static bool loadingIcon = false;

    oled.clear();

    oled.rect(0, 0, 127, 27, 1);

    oled.invertText(true);
    oled.setCursor(8, 1);
    oled.setScale(2);
    if (loading) {
        oled.print("  MT-01");
    } else {
        oled.print(inputVoltage, 1);
        oled.print(" v");
    }

    oled.invertText(false);
    oled.setScale(1);

    if (loading) {
        oled.setCursor(8, 5);
        oled.print("Loading...");
        oled.setCursor(111, 5);
        drawIcon8x8(loadingIcon + 2);
        loadingIcon = !loadingIcon;
        oled.update();
        return;
    }

    oled.setCursor(8, 4);
    oled.print(elrsConnected ? "ELRS Connected" : "Disconnected");
    oled.setCursor(111, 4);
    drawIcon8x8(!elrsConnected);
    
    String modeStr;
    
    switch (mode) {
        case MODE_ACRO: modeStr = "ACRO"; break;
        case MODE_STABILIZED: modeStr = "STABILIZED"; break;
        default: modeStr = "NOT SET"; break;
    }

    oled.setCursor(8, 6);
    oled.print("Mode ");
    oled.print(modeStr);

    oled.setCursor(111, 6);
    drawIcon8x8(4 + mode);

    oled.update();
}
