#ifndef GLOBALS_H
#define GLOBALS_H

#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPUpdateServer.h>

// ===========================================================================
//  CONFIGURAÇÕES EM RUNTIME
// ===========================================================================
extern uint16_t artnetPort;
extern uint8_t  artnetNet;
extern uint8_t  artnetSubnet;
extern uint8_t  artnetUniverse;

// ===========================================================================
//  ESTADO — DMX
// ===========================================================================
extern uint8_t dmxData[513];            // 0=START_CODE, 1-512=canais
extern uint8_t pollReplyBuf[239];       // Buffer para ArtPollReply
extern uint8_t udpBuf[640];             // Buffer para recebimento UDP
extern uint32_t lastPacketMs;
extern bool     dmxRunning;
extern uint32_t pktOk;
extern uint32_t pktFilt;

// ===========================================================================
//  ESTADO — Teste
// ===========================================================================
extern bool          testContinuous;
extern uint8_t       testValue;
extern unsigned long lastTestSend;
extern unsigned long lastDmxSend;
extern unsigned long lastPollReply;

// ===========================================================================
//  ESTADO — WiFi Scan
// ===========================================================================
extern bool     scanRequested;
extern bool     scanReady;
extern uint32_t scanStartMs;

// ===========================================================================
//  INST. GLOBAIS — Hardware/Network
// ===========================================================================
extern WiFiUDP          udp;
extern ESP8266WebServer server;
extern ESP8266HTTPUpdateServer otaServer;

// ===========================================================================
//  STRUCT — WiFi Credentials
// ===========================================================================
struct WifiCreds {
    uint8_t magic;
    char ssid[33];
    char pass[65];
};
extern WifiCreds wifiCreds;

#endif
