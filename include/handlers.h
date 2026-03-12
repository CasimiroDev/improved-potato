#ifndef HANDLERS_H
#define HANDLERS_H

// ===========================================================================
//  HTTP HANDLERS — Endpoints REST API
// ===========================================================================

/**
 * GET / - Página HTML completa (servi em chunks from PROGMEM)
 * Retorna dashboard com status, canais DMX, WiFi, config e OTA
 */
void handleRoot();

/**
 * GET /data?start=X&count=Y - Status de DMX em JSON
 * Parâmetros:
 *   start: canal inicial (1-512), default 1
 *   count: quantidade de canais (1-128), default 16
 * Resposta: {running, ago, pktOk, pktFilt, s1, s2, s3, chStart, ch:[]}
 */
void handleData();

/**
 * GET /config.json - Configuração ArtNet em JSON
 * Resposta: {port, net, sub, uni}
 */
void handleConfigJson();

/**
 * GET /artnet - Configurar parâmetros ArtNet
 * Parâmetros POST:
 *   port: porta UDP (1-65535), default 6454
 *   net: rede (0-127), default 0
 *   subnet: subnet (0-15), default 0
 *   universe: universo (0-15), default 0
 */
void handleArtnetCfg();

/**
 * GET /dmx-set?ch=X&val=Y - Setar canal DMX individual
 * Parâmetros:
 *   ch: canal (1-512)
 *   val: valor (0-255)
 */
void handleDmxSet();

/**
 * GET /dmx-set-bulk?n=K&ch1=...&val1=... - Setar múltiplos canais DMX
 * Parâmetros:
 *   n: quantidade de canais (1-16)
 *   ch1, ch2, ... chN: números dos canais
 *   val1, val2, ... valN: valores (0-255)
 */
void handleDmxSetBulk();

/**
 * POST /device - Atualizar configurações do dispositivo
 * Parâmetros POST:
 *   devname: nome do dispositivo
 *   appass: senha AP (mín 8 chars)
 *   status_led: ativar LED de status
 */
void handleDevice();

/**
 * GET /test-dmx?val=X[&cont=1] - Teste rápido de DMX
 * Parâmetros:
 *   val: valor (0-255) a enviar em todos os canais
 *   cont: 1=contínuo, 0=parar, undefined=single frame
 */
void handleTestDmx();

/**
 * GET /wifi-scan-start - Dispara WiFi scan assíncrono
 * Não bloqueia; retorna imediatamente
 * Usar handleWifiScanResult() para polling do resultado
 */
void handleWifiScanStart();

/**
 * GET /wifi-scan-result - Retorna resultado de scan anterior
 * Resposta: {status:"scanning"} ou {status:"done", nets:[...]}
 * Cada rede: {ssid, rssi, strength, secured}
 */
void handleWifiScanResult();

/**
 * POST /wifi-connect - Conectar a rede WiFi e salvar credenciais
 * Parâmetros POST:
 *   ssid: SSID da rede
 *   pass: senha (pode ser vazia)
 * Reinicia o dispositivo após sucesso
 */
void handleWifiConnect();

/**
 * GET /wifi-forget - Apagar credenciais e reiniciar em modo AP
 */
void handleWifiForget();

/**
 * GET /wifi-status - Status WiFi atual em JSON
 * Resposta: {connected, mode, ip, ssid, rssi}
 */
void handleWifiStatus();

#endif
