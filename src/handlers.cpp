#include "config.h"
#include "globals.h"
#include "handlers.h"
#include "web_ui.h"
#include "eeprom_module.h"
#include "artnet_module.h"
#include "dmx_module.h"
#include <ESP8266WiFi.h>

// Helper para obter IP do nó (replicado aqui para evitar dependência)
static IPAddress getNodeIP() {
    IPAddress ip = WiFi.localIP();
    if (ip == IPAddress(0, 0, 0, 0)) ip = WiFi.softAPIP();
    return ip;
}

void handleRoot() {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");

    auto sendPgm = [](const char* pgm) {
        size_t total = strlen_P(pgm);
        size_t offset = 0;
        char   chunk[512];
        while (offset < total) {
            size_t sz = min((size_t)512, total - offset);
            memcpy_P(chunk, pgm + offset, sz);
            server.sendContent(chunk, sz);
            offset += sz;
            yield();
        }
    };

    sendPgm(HTML_HEAD);

    {
        char dyn[256];
        String ip   = getNodeIP().toString();
        const char* mode = (WiFi.status() == WL_CONNECTED) ? "STA" : "AP";
        snprintf(dyn, sizeof(dyn),
            "<div class='sub'>IP: <b>%s</b> (%s)"
            "&nbsp;|&nbsp;Net:<b>%d</b> Sub:<b>%d</b> Uni:<b>%d</b>"
            "&nbsp;|&nbsp;Porta ArtNet:<b>%d</b></div>",
            ip.c_str(), mode,
            artnetNet, artnetSubnet, artnetUniverse, artnetPort);
        server.sendContent(dyn);
    }

    sendPgm(HTML_JS);
    sendPgm(HTML_BODY);

    server.sendContent("");
}

void handleData() {
    static char buf[2048];  // Buffer maior para 512 canais

    int chStart = 1, chCount = 512;
    if (server.hasArg("start")) chStart = constrain(server.arg("start").toInt(), 1, 512);
    if (server.hasArg("count")) chCount = constrain(server.arg("count").toInt(), 1, 512);
    if (chStart + chCount - 1 > 512) chCount = 512 - chStart + 1;

    uint32_t dmxIntervalMs = (uint32_t)dmxData[1] * 30000UL / 255;
    uint32_t agoSecs = (dmxRunning) ? ((millis() - lastPacketMs) / 1000UL) : 999;

    int n = snprintf(buf, sizeof(buf),
        "{\"running\":%d,\"cont\":%d,\"val\":%d,\"ago\":%lu,"
        "\"pktOk\":%lu,\"pktFilt\":%lu,"
        "\"net\":%d,\"sub\":%d,\"uni\":%d,\"port\":%d,"
        "\"interval\":%lu,\"s1\":%d,\"s2\":%d,\"s3\":%d,"
        "\"chStart\":%d,\"ch\":[",
        dmxRunning ? 1 : 0, testContinuous ? 1 : 0, testValue,
        agoSecs,
        (unsigned long)pktOk, (unsigned long)pktFilt,
        artnetNet, artnetSubnet, artnetUniverse, artnetPort,
        (unsigned long)dmxIntervalMs,
        dmxData[1], dmxData[2], dmxData[3], chStart);

    for (int i = 0; i < chCount && n < (int)sizeof(buf) - 6; i++) {
        if (i > 0) buf[n++] = ',';
        n += snprintf(buf + n, sizeof(buf) - n, "%d", dmxData[chStart + i]);
    }
    if (n < (int)sizeof(buf) - 3) {
        buf[n++] = ']'; buf[n++] = '}'; buf[n] = '\0';
    }

    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", buf);
}

void handleDmxSet() {
    if (!server.hasArg("ch") || !server.hasArg("val")) {
        server.send(400, "application/json", "{\"error\":\"Parâmetros ch e val obrigatórios\"}");
        return;
    }
    int ch  = server.arg("ch").toInt();
    int val = server.arg("val").toInt();
    
    if (ch < 1 || ch > 512 || val < 0 || val > 255) {
        server.send(400, "application/json", "{\"error\":\"ch 1-512, val 0-255\"}");
        return;
    }
    
    dmxData[ch] = (uint8_t)val;
    lastPacketMs = millis();
    dmxRunning = true;
    dmxSend();
    
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", "{\"ok\":true}");
}

void handleDmxSetBulk() {
    int n = server.arg("n").toInt();
    if (n < 1 || n > 16) {
        server.send(400, "application/json", "{\"error\":\"n deve estar entre 1 e 16\"}");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        String chKey = "ch" + String(i+1);
        String valKey = "val" + String(i+1);
        
        if (server.hasArg(chKey) && server.hasArg(valKey)) {
            int ch  = server.arg(chKey).toInt();
            int val = server.arg(valKey).toInt();
            
            if (ch >= 1 && ch <= 512 && val >= 0 && val <= 255) {
                dmxData[ch] = (uint8_t)val;
            }
        }
    }
    
    lastPacketMs = millis();
    dmxRunning = true;
    dmxSend();
    
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", "{\"ok\":true}");
}

void handleConfigJson() {
    char buf[128];
    snprintf(buf, sizeof(buf),
        "{\"port\":%d,\"net\":%d,\"sub\":%d,\"uni\":%d}",
        artnetPort, artnetNet, artnetSubnet, artnetUniverse);
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", buf);
}

void handleWifiScanStart() {
    WiFi.scanNetworks(true);
    scanReady     = false;
    scanRequested = true;
    scanStartMs   = millis();
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", "{\"ok\":true}");
}

void handleWifiScanResult() {
    int n = WiFi.scanComplete();

    if (n == WIFI_SCAN_RUNNING) {
        if (millis() - scanStartMs > 10000) {
            WiFi.scanDelete();
            server.send(200, "application/json", "{\"status\":\"done\",\"nets\":[]}");
        } else {
            server.send(200, "application/json", "{\"status\":\"scanning\"}");
        }
        return;
    }

    static char buf[1024];
    int written = snprintf(buf, sizeof(buf), "{\"status\":\"done\",\"nets\":[");

    if (n > 0) {
        for (int i = 0; i < n && written < (int)sizeof(buf) - 80; i++) {
            int  rssi     = WiFi.RSSI(i);
            int  strength = rssi > -50 ? 4 : rssi > -65 ? 3 : rssi > -75 ? 2 : 1;
            bool secured  = WiFi.encryptionType(i) != ENC_TYPE_NONE;
            String ssid = WiFi.SSID(i);
            ssid.replace("\"", "");
            written += snprintf(buf + written, sizeof(buf) - written,
                "%s{\"ssid\":\"%s\",\"rssi\":%d,\"strength\":%d,\"secured\":%s}",
                i > 0 ? "," : "",
                ssid.c_str(), rssi, strength, secured ? "true" : "false");
        }
    }

    if (written < (int)sizeof(buf) - 3) {
        buf[written++] = ']';
        buf[written++] = '}';
        buf[written]   = '\0';
    }

    WiFi.scanDelete();
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", buf);
}

void handleWifiConnect() {
    if (!server.hasArg("ssid") || server.arg("ssid").length() == 0) {
        server.send(400, "application/json", "{\"error\":\"SSID vazio\"}");
        return;
    }
    server.arg("ssid").toCharArray(wifiCreds.ssid, EEPROM_SSID_LEN);
    server.arg("pass").toCharArray(wifiCreds.pass, EEPROM_PASS_LEN);
    eepromSave();
    server.send(200, "application/json", "{\"ok\":true}");
    delay(500);
    ESP.restart();
}

void handleWifiForget() {
    eepromClear();
    server.send(200, "application/json", "{\"ok\":true}");
    delay(500);
    ESP.restart();
}

void handleWifiStatus() {
    bool connected = (WiFi.status() == WL_CONNECTED);
    char buf[200];
    snprintf(buf, sizeof(buf),
        "{\"connected\":%s,\"mode\":\"%s\",\"ip\":\"%s\",\"ssid\":\"%s\",\"rssi\":%d}",
        connected ? "true" : "false",
        connected ? "STA" : "AP",
        connected ? WiFi.localIP().toString().c_str() : WiFi.softAPIP().toString().c_str(),
        connected ? WiFi.SSID().c_str() : "ONEBit Core (AP)",
        connected ? WiFi.RSSI() : 0);
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "application/json", buf);
}

void handleTestDmx() {
    uint8_t val  = testValue;
    if (server.hasArg("val"))  val = (uint8_t)constrain(server.arg("val").toInt(), 0, 255);
    bool cont = server.hasArg("cont") && server.arg("cont") == "1";
    bool stop = server.hasArg("cont") && server.arg("cont") == "0";

    testValue = val;
    memset(dmxData + 1, val, DMX_CHANNELS);
    dmxData[0] = 0x00;

    if (stop) {
        testContinuous = false;
        memset(dmxData + 1, 0, DMX_CHANNELS);
        dmxSend();
    } else if (cont) {
        testContinuous = true;
    } else {
        dmxSend();
    }

    lastPacketMs = millis();
    dmxRunning   = (val > 0 || testContinuous);
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleDevice() {
    // Stub para configurações do dispositivo (nome, AP password, LED)
    // Em produção, salvar em EEPROM/SPIFFS
    server.sendHeader("Location", "/");
    server.send(303);
}

void handleArtnetCfg() {
    if (server.hasArg("port")) {
        uint16_t p = (uint16_t)constrain(server.arg("port").toInt(), 1, 65535);
        if (p != artnetPort) { artnetPort = p; udp.stop(); udp.begin(artnetPort); }
    }
    if (server.hasArg("net"))      artnetNet      = (uint8_t)constrain(server.arg("net").toInt(),      0, 127);
    if (server.hasArg("subnet"))   artnetSubnet   = (uint8_t)constrain(server.arg("subnet").toInt(),   0,  15);
    if (server.hasArg("universe")) artnetUniverse = (uint8_t)constrain(server.arg("universe").toInt(), 0,  15);
    sendArtPollReply();
    server.sendHeader("Location", "/");
    server.send(303);
}
