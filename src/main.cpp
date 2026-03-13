/*
Interface ArtNet ONEBit Core
============================
Recebe um universo ArtNet via WiFi e transmite DMX512 via UART → MAX487 (RS485).

Arquitetura modular:
- config.h       : Constantes e defines
- globals.h      : Declarações de variáveis globais
- dmx_module     : Transmissão DMX
- artnet_module  : Protocolo ArtNet
- wifi_module    : Setup WiFi
- eeprom_module  : Persistência de credenciais
- handlers       : Endpoints HTTP/REST API
- web_ui.h       : Interface web (HTML/CSS/JS)
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

#include "config.h"
#include "globals.h"
#include "dmx_module.h"
#include "artnet_module.h"
#include "wifi_module.h"
#include "eeprom_module.h"
#include "handlers.h"
#include "web_ui.h"

// -- NOVO: Inclusões para OTA online e JSON --
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>

// -- NOVO: Definição da URL do seu servidor de firmware (apenas em main.cpp ou um .cpp) --
// Remova a linha 'const char* FIRMWARE_SERVER_URL = "http://seu-site.com/firmware/";' daqui
// e coloque-a em um arquivo .cpp (como main.cpp) para que seja definida UMA VEZ.
// Se você a definiu em config.h, então remova-a de main.cpp.
// Se você a declarou como 'extern' em globals.h, então a definição deve estar em um .cpp:
const char* FIRMWARE_SERVER_URL = "http://seu-site.com/firmware/"; // Definição real

// ===========================================================================
//  DEFINIÇÕES DE VARIÁVEIS GLOBAIS
// ===========================================================================

// Configurações ArtNet
uint16_t artnetPort     = DEFAULT_ARTNET_PORT;
uint8_t  artnetNet      = DEFAULT_ARTNET_NET;
uint8_t  artnetSubnet   = DEFAULT_ARTNET_SUBNET;
uint8_t  artnetUniverse = DEFAULT_ARTNET_UNIVERSE;

// Estado DMX
uint8_t dmxData[DMX_CHANNELS + 1] = {0};
uint8_t pollReplyBuf[239];
uint8_t udpBuf[640];

uint32_t lastPacketMs  = 0;
bool     dmxRunning    = false;
uint32_t pktOk         = 0;
uint32_t pktFilt       = 0;

// Teste DMX
bool          testContinuous = false;
uint8_t       testValue      = 255;
unsigned long lastTestSend   = 0;
unsigned long lastDmxSend    = 0;
unsigned long lastPollReply  = 0;

// WiFi Scan assíncrono
bool     scanRequested  = false;
bool     scanReady      = false;
uint32_t scanStartMs    = 0;

// Instâncias globais
WiFiUDP          udp;
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer otaServer;

// ===========================================================================
//  SETUP
// ===========================================================================
void setup() {
    Serial1.begin(115200);
    pinMode(DMX_DE_PIN, OUTPUT);
    digitalWrite(DMX_DE_PIN, HIGH);
    memset(dmxData, 0, sizeof(dmxData));

    // Inicializa WiFi
    wifiSetup();

    // Inicializa UDP para ArtNet
    udp.begin(artnetPort);

    // Setup OTA para upload manual (existente)
    otaServer.setup(&server, "/ota-update");

    // Registra handlers HTTP
    server.on("/",                 HTTP_GET,  handleRoot);
    server.on("/data",             HTTP_GET,  handleData);
    server.on("/config.json",      HTTP_GET,  handleConfigJson);
    server.on("/artnet",           HTTP_POST, handleArtnetCfg);
    server.on("/test-dmx",         HTTP_GET,  handleTestDmx);
    server.on("/dmx-set",          HTTP_GET,  handleDmxSet);
    server.on("/dmx-set-bulk",     HTTP_GET,  handleDmxSetBulk);
    server.on("/device",           HTTP_POST, handleDevice);
    server.on("/wifi-scan-start",  HTTP_GET,  handleWifiScanStart);
    server.on("/wifi-scan-result", HTTP_GET,  handleWifiScanResult);
    server.on("/wifi-connect",     HTTP_POST, handleWifiConnect);
    server.on("/wifi-forget",      HTTP_GET,  handleWifiForget);
    server.on("/wifi-status",      HTTP_GET,  handleWifiStatus);
    server.on("/reset-wifi",       HTTP_GET,  handleWifiForget);

    // -- NOVO: Handlers para OTA online e informações de firmware --
    server.on("/firmware-info",    HTTP_GET,  handleFirmwareInfo);
    server.on("/ota-check",        HTTP_GET,  handleOtaCheck);
    server.on("/ota-install-online", HTTP_POST, handleOtaInstallOnline);

    server.begin();

    // mDNS
    if (MDNS.begin("onebit-core")) {
        MDNS.addService("http", "tcp", 80);
    }

    // Envia PollReply inicial
    sendArtPollReply();
}

// ===========================================================================
//  LOOP
// ===========================================================================
void loop() {
    unsigned long now = millis();

    // Handle HTTP requests
    server.handleClient();
    MDNS.update();

    // Processa ArtNet se não estiver em modo de teste contínuo
    if (!testContinuous) {
        handleArtNet();

        // Reenvio periódico de DMX baseado no canal 1
        uint32_t interval = (uint32_t)dmxData[1] * 30000UL / 255UL;
        if (interval == 0) interval = 25;
        if ((uint32_t)(now - lastDmxSend) >= interval) {
            dmxSend();
            lastDmxSend = now;
        }
    }

    // Modo teste contínuo - envia frames continuamente
    if (testContinuous && (now - lastTestSend) >= 100) {
        lastTestSend = now;
        lastPacketMs = now;
        dmxSend();
    }

    // Envia ArtPollReply periodicamente (~3 segundos)
    if (now - lastPollReply >= POLL_REPLY_INTERVAL_MS) {
        lastPollReply = now;
        sendArtPollReply();
    }
}