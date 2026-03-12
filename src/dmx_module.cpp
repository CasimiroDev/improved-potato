#include "config.h"
#include "globals.h"
#include "dmx_module.h"

void dmxSend() {
    Serial.flush();
    Serial.end();

    noInterrupts();
    pinMode(DMX_TX_PIN, OUTPUT);
    digitalWrite(DMX_TX_PIN, LOW);
    delayMicroseconds(DMX_BREAK_US);
    digitalWrite(DMX_TX_PIN, HIGH);
    delayMicroseconds(DMX_MAB_US);
    interrupts();

    Serial.begin(250000, SERIAL_8N2);
    delayMicroseconds(10);
    Serial.write(dmxData, DMX_CHANNELS + 1);
    yield();
}
