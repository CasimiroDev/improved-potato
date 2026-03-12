#ifndef ARTNET_MODULE_H
#define ARTNET_MODULE_H

#include <stdint.h>
#include <IPAddress.h>

// ===========================================================================
//  ArtNet Protocol — Poll Reply
// ===========================================================================

/**
 * Constrói o buffer da resposta ArtPollReply (239 bytes).
 * Usado para responder a broadcasts ArtPoll ou para publicidade periódica.
 */
void buildPollReply(uint8_t *buf);

/**
 * Envia ArtPollReply para broadcast 255.255.255.255
 */
void sendArtPollReply();

/**
 * Envia ArtPollReply diretamente para um endereço específico (resposta a Poll).
 */
void sendArtPollReplyTo(IPAddress dest);

// ===========================================================================
//  ArtNet Protocol — DMX Data
// ===========================================================================

/**
 * Processa pacotes ArtNet recebidos via UDP.
 * - Filtra por Net/Subnet/Universe
 * - Extrai dados DMX (máx 512 canais)
 * - Chama dmxSend() automaticamente
 * - Atualiza contadores (pktOk, pktFilt)
 * - Atualiza timestamp lastPacketMs
 */
void handleArtNet();

#endif
