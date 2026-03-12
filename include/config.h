#ifndef CONFIG_H
#define CONFIG_H

// ===========================================================================
//  CONFIGURAÇÕES — ArtNet
// ===========================================================================
#define DEFAULT_ARTNET_PORT      6454
#define DEFAULT_ARTNET_NET       0
#define DEFAULT_ARTNET_SUBNET    0
#define DEFAULT_ARTNET_UNIVERSE  0

// ===========================================================================
//  CONFIGURAÇÕES — DMX
// ===========================================================================
#define DMX_TX_PIN               1
#define DMX_DE_PIN               16
#define DMX_CHANNELS             512
#define DMX_BREAK_US             100
#define DMX_MAB_US               12

// ===========================================================================
//  CONFIGURAÇÕES — ArtNet Protocol
// ===========================================================================
#define NODE_SHORT_NAME          "ONEBit Core"
#define NODE_LONG_NAME           "Interface ArtNet_DMX ONEBit Core"

// ===========================================================================
//  EEPROM
// ===========================================================================
#define EEPROM_SIZE              128
#define EEPROM_MAGIC             0xAB
#define EEPROM_SSID_LEN          33
#define EEPROM_PASS_LEN          65

// ===========================================================================
//  INTERVALO DE POLL REPLY
// ===========================================================================
#define POLL_REPLY_INTERVAL_MS   3000

#endif
