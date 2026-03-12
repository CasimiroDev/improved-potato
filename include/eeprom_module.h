#ifndef EEPROM_MODULE_H
#define EEPROM_MODULE_H

// ===========================================================================
//  EEPROM — Persistência de credenciais WiFi
// ===========================================================================

/**
 * Carrega credenciais WiFi da EEPROM.
 * Se o magic byte não bate, zera a struct.
 */
void eepromLoad();

/**
 * Salva credenciais WiFi na EEPROM.
 */
void eepromSave();

/**
 * Limpa credenciais WiFi da EEPROM.
 * Força reinicialização em modo AP.
 */
void eepromClear();

#endif
