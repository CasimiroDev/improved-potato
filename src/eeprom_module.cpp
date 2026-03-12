#include "config.h"
#include "globals.h"
#include "eeprom_module.h"
#include <EEPROM.h>

// Inicializa variável global wifiCreds
WifiCreds wifiCreds = {0};

void eepromLoad() {
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.get(0, wifiCreds);
    if (wifiCreds.magic != EEPROM_MAGIC) {
        memset(&wifiCreds, 0, sizeof(wifiCreds));
        wifiCreds.magic = EEPROM_MAGIC;
    }
}

void eepromSave() {
    EEPROM.begin(EEPROM_SIZE);
    EEPROM.put(0, wifiCreds);
    EEPROM.commit();
}

void eepromClear() {
    memset(&wifiCreds, 0, sizeof(wifiCreds));
    wifiCreds.magic = EEPROM_MAGIC;
    eepromSave();
}
