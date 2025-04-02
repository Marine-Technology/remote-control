#include <Arduino.h>
#include "elrs.h"
#include "settings.h"
#include <AlfredoCRSF.h>
#include <HardwareSerial.h>


HardwareSerial crsfSerial(1);
AlfredoCRSF crsf;


bool initElrs() {
    crsfSerial.begin(ELRS_SERIAL_BAUD, SERIAL_8N1, ELRS_SERIAL_RX, ELRS_SERIAL_TX);

    if (!crsfSerial) return false;
    
    crsf.begin(crsfSerial);
    return true;
}


void elrsUpdate() {
    crsf.update();
}


unsigned int getChannel(uint8_t channelNum) {
    int channel = crsf.getChannel(channelNum);
    if (!channel) return 0;
    return min(max(channel, 1000), 2000);
}


bool isRadioConnected() {
    return crsf.isLinkUp();
}
