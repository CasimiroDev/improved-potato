#ifndef DMX_MODULE_H
#define DMX_MODULE_H

#include <stdint.h>

// ===========================================================================
//  DMX — Transmissão serial
// ===========================================================================

/**
 * Envia um frame DMX512 via UART com break + MAB corretos.
 * Estrutura DMX:
 *  - BREAK: 100 µs (nível baixo)
 *  - MAB: 12 µs (pausa)
 *  - Data: 513 bytes (START_CODE 0x00 + 512 valores DMX)
 */
void dmxSend();

#endif
