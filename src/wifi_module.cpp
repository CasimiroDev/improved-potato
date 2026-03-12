#include "config.h"
#include "globals.h"
#include "wifi_module.h"
#include "eeprom_module.h"
#include <ESP8266WiFi.h>

void startAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(NODE_SHORT_NAME, "");
}

void wifiSetup() {
    eepromLoad();
    if (strlen(wifiCreds.ssid) > 0) {
        WiFi.mode(WIFI_STA);
        WiFi.begin(wifiCreds.ssid, wifiCreds.pass);
        unsigned long t = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - t < 15000) {
            delay(100);
            yield();
        }
        if (WiFi.status() != WL_CONNECTED) {
            startAP();
        }
    } else {
        startAP();
    }
}
