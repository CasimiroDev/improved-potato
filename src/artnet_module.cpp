#include "config.h"
#include "globals.h"
#include "artnet_module.h"
#include "dmx_module.h"
#include <ESP8266WiFi.h>

// ===========================================================================
//  HELPERS — Obter IP do nó
// ===========================================================================
static IPAddress getNodeIP() {
    IPAddress ip = WiFi.localIP();
    if (ip == IPAddress(0, 0, 0, 0)) ip = WiFi.softAPIP();
    return ip;
}

static IPAddress getDirectedBroadcast() {
    IPAddress ip   = getNodeIP();
    IPAddress mask = (WiFi.status() == WL_CONNECTED)
                     ? WiFi.subnetMask()
                     : IPAddress(255, 255, 255, 0);
    return IPAddress(
        (uint8_t)(ip[0] | ~mask[0]), (uint8_t)(ip[1] | ~mask[1]),
        (uint8_t)(ip[2] | ~mask[2]), (uint8_t)(ip[3] | ~mask[3]));
}

// ===========================================================================
//  ArtPollReply
// ===========================================================================
void buildPollReply(uint8_t *buf) {
    IPAddress ip = getNodeIP();
    uint8_t   mac[6];
    WiFi.macAddress(mac);
    memset(buf, 0, 239);
    memcpy(buf, "Art-Net", 7);
    buf[8]  = 0x00; buf[9]  = 0x21;
    buf[10] = ip[0]; buf[11] = ip[1]; buf[12] = ip[2]; buf[13] = ip[3];
    buf[14] = artnetPort & 0xFF; buf[15] = (artnetPort >> 8) & 0xFF;
    buf[16] = 0x00; buf[17] = 0x01;
    buf[18] = artnetNet & 0x7F;
    buf[19] = artnetSubnet & 0x0F;
    buf[20] = 0xFF; buf[21] = 0xFF;
    buf[23] = 0xD2;
    strncpy((char *)&buf[26],  NODE_SHORT_NAME, 17);
    strncpy((char *)&buf[44],  NODE_LONG_NAME,  63);
    strncpy((char *)&buf[108], "#0001 [0000] OK", 63);
    buf[173] = 0x01; buf[174] = 0x40;
    buf[178] = 0x80;
    buf[190] = artnetUniverse & 0x0F;
    memcpy(&buf[201], mac, 6);
    buf[207] = ip[0]; buf[208] = ip[1]; buf[209] = ip[2]; buf[210] = ip[3];
    buf[211] = 0x01; buf[212] = 0x08;
}

void sendArtPollReply() {
    buildPollReply(pollReplyBuf);
    IPAddress bcast = getDirectedBroadcast();
    udp.beginPacket(bcast, artnetPort);
    udp.write(pollReplyBuf, 239);
    udp.endPacket();
}

void sendArtPollReplyTo(IPAddress dest) {
    buildPollReply(pollReplyBuf);
    udp.beginPacket(dest, artnetPort);
    udp.write(pollReplyBuf, 239);
    udp.endPacket();
}

// ===========================================================================
//  ArtNet RX
// ===========================================================================
void handleArtNet() {
    int pktSize = udp.parsePacket();
    if (pktSize < 10) return;
    IPAddress sender = udp.remoteIP();
    int len = udp.read(udpBuf, sizeof(udpBuf));
    if (len < 10) return;
    if (memcmp(udpBuf, "Art-Net", 7) != 0 || udpBuf[7] != 0x00) return;

    uint16_t opcode = udpBuf[8] | ((uint16_t)udpBuf[9] << 8);

    if (opcode == 0x2000) {
        sendArtPollReplyTo(sender);
        sendArtPollReply();
        return;
    }

    if (opcode == 0x5000 && len >= 18) {
        uint8_t pktNet     = udpBuf[15] & 0x7F;
        uint8_t pktSubUni  = udpBuf[14];
        uint8_t pktSubnet  = (pktSubUni >> 4) & 0x0F;
        uint8_t pktUniverse= pktSubUni & 0x0F;

        if (pktNet != artnetNet || pktSubnet != artnetSubnet || pktUniverse != artnetUniverse) {
            pktFilt++;
            return;
        }
        uint16_t dataLen = ((uint16_t)udpBuf[16] << 8) | udpBuf[17];
        if (dataLen > DMX_CHANNELS) dataLen = DMX_CHANNELS;
        dmxData[0] = 0x00;
        memcpy(dmxData + 1, udpBuf + 18, dataLen);
        dmxSend();
        lastPacketMs = millis();
        lastDmxSend  = lastPacketMs;
        dmxRunning   = true;
        pktOk++;
    }
}
