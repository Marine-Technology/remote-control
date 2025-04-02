#include <Arduino.h>
#include "voltage.h"
#include "settings.h"


float readVoltage() {
    int adcValue = analogRead(VOLTMETER_PIN);
    float pinVoltage = (adcValue / VOLTMETER_ADC_RESOLUTION) * VOLTMETER_ADC_REFERENCE;
    return pinVoltage * (VOLTMETER_R1 + VOLTMETER_R2) / VOLTMETER_R2;
}
