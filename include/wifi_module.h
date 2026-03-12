#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

// ===========================================================================
//  WiFi — Configuração e inicialização
// ===========================================================================

/**
 * Inicia o modo Access Point (AP).
 * SSID: "ONEBit Core"
 * Senha: (vazia - aberto)
 */
void startAP();

/**
 * Setup WiFi completo:
 * 1. Se há credenciais salvas, tenta conectar(Station)
 * 2. Se conectar falhar em 15s, cai para AP
 * 3. Se não houver credenciais, inicia em AP
 */
void wifiSetup();

#endif
