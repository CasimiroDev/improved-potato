# 📋 Projeto ONEBit Core - Estrutura Modular

## Visão Geral
Refatoração completa de **1570 linhas** em um único `main.cpp` para uma **arquitetura modular limpa e profissional**, facilitando manutenção, testes e expansões futuras.

---

## 📁 Estrutura de Arquivos

```
include/
├── config.h              # Constantes e configurações
├── globals.h             # Declarações de variáveis globais
├── dmx_module.h          # Interface DMX
├── artnet_module.h       # Interface protocolo ArtNet
├── wifi_module.h         # Interface WiFi
├── eeprom_module.h       # Interface EEPROM
├── handlers.h            # Declarações de handlers HTTP
└── web_ui.h              # HTML/CSS/JS estático (PROGMEM)

src/
├── main.cpp              # Inicialização (setup/loop) - ~90 linhas simplificadas
├── dmx_module.cpp        # Implementação transmissão DMX
├── artnet_module.cpp     # Implementação protocolo ArtNet
├── wifi_module.cpp       # Implementação WiFi
├── eeprom_module.cpp     # Implementação EEPROM
└── handlers.cpp          # Implementação endpoints HTTP/REST
```

---

## 📦 Módulos Detalhados

### 1️⃣ **config.h** - Constantes
Centraliza TODAS as constantes do projeto. Ideal para ajustes e configurações.

**Categorias:**
- `DEFAULT_ARTNET_*` - Configurações ArtNet padrão
- `DMX_*` - Constantes DMX512
- `NODE_*` - Nome do nó
- `EEPROM_*` - Tamanho e estrutura EEPROM
- `POLL_REPLY_*` - Intervalo de poll reply

**Uso:** Alterar uma porta UDP? Mude em **um único lugar** em `config.h`

---

### 2️⃣ **globals.h** - Declarações Globais
Arquivo `.h` que **declara** todos as variáveis globais usadas em múltiplos módulos. As **definições** estão em `main.cpp`.

**Por que separar?**
- ✅ Evita circular dependencies
- ✅ Documentação clara de interface pública
- ✅ Facilita encontrar variáveis compartilhadas

**Conteúdo:**
```cpp
extern uint16_t artnetPort;      // Configurável via web
extern uint8_t  dmxData[513];    // Buffer DMX
extern WiFiUDP  udp;             // Socket UDP
extern ESP8266WebServer server;  // Servidor web
```

---

### 3️⃣ **dmx_module.{h|cpp}** - Transmissão DMX512
Isolado: apenas responsável por **enviar frame DMX via UART**.

**Interface pública:**
```cpp
void dmxSend();  // Envia 513 bytes (START_CODE + 512 canais)
```

**Detalhes:**
- Break de 100 µs + MAB de 12 µs
- Taxa: 250.000 baud, 8N2
- Controla pino DE do MAX487
- Usar `dmxData[513]` para dados

---

### 4️⃣ **artnet_module.{h|cpp}** - Protocolo ArtNet
Processa pacotes ArtNet UDP e controla poll replies.

**Interface pública:**
```cpp
void handleArtNet();              // Recebe e processa DMX via ArtNet
void sendArtPollReply();          // Broadcast poll reply
void sendArtPollReplyTo(IPAddr);  // Unicast poll reply
void buildPollReply(uint8_t*);    // Constrói pacote reply
```

**Lógica:**
1. Aguarda pacotes UDP na porta 6454
2. Valida magic "Art-Net" + versão
3. Filtra por Net/Subnet/Universe
4. Copia dados para `dmxData[]`
5. Chama `dmxSend()` automaticamente
6. Atualiza contadores `pktOk` / `pktFilt`

---

### 5️⃣ **wifi_module.{h|cpp}** - Conexão WiFi
Gerencia conexão Station ou Access Point.

**Interface pública:**
```cpp
void wifiSetup();   // Setup completo (STA ou AP)
void startAP();     // Força modo AP
```

**Fluxo:**
1. Tenta carregar credenciais da EEPROM
2. Se houver SSID, tenta conectar como STA (15s timeout)
3. Se falhar ou não houver credenciais, ativa AP
4. AP: SSID="ONEBit Core", senha vazia

---

### 6️⃣ **eeprom_module.{h|cpp}** - Persistência
Salva/carrega credenciais WiFi na EEPROM.

**Interface pública:**
```cpp
void eepromLoad();     // Carrega credenciais da EEPROM
void eepromSave();     // Salva credenciais na EEPROM
void eepromClear();    // Limpa e força reinicialização em AP
```

**Estrutura:**
```cpp
struct WifiCreds {
    uint8_t magic;         // 0xAB - verificação
    char ssid[33];         // SSID (32 + null)
    char pass[65];         // Senha (64 + null)
};
```

---

### 7️⃣ **handlers.{h|cpp}** - Endpoints HTTP
Toda lógica de requisições HTTP/REST API.

**Endpoints implementados:**
| Método | Rota | Retorno |
|--------|------|------|
| GET | `/` | HTML completo |
| GET | `/data?start=X&count=Y` | JSON status DMX |
| GET | `/config.json` | JSON config ArtNet |
| POST | `/artnet` | Atualiza config |
| GET | `/test-dmx?val=X[&cont=1]` | Teste DMX |
| GET | `/wifi-scan-start` | Inicia scan WiFi |
| GET | `/wifi-scan-result` | Resultado scan |
| POST | `/wifi-connect` | Conecta WiFi |
| GET | `/wifi-forget` | Apaga credenciais |
| GET | `/wifi-status` | Status WiFi atual |

**Uso de buffers estáticos:**
```cpp
static char buf[1024];  // Reutiliza mesmo buffer por endpoint
```

---

### 8️⃣ **web_ui.h** - Interface Web
Strings HTML/CSS/JavaScript em `PROGMEM` (Flash, não RAM!).

**Organizei em 3 partes:**
1. `HTML_HEAD` - <!DOCTYPE> até </style>
2. `HTML_JS` - <script> do lado cliente
3. `HTML_BODY` - <div class="page"> e panes

**Vantagem:** ~8 KB de UI não consome RAM heap

---

### 9️⃣ **main.cpp** - Inicialização (REFATORADO)
Agora com apenas **~90 linhas**!

**Responsabilidades:**
```cpp
void setup() {
    // Inicializa Serial + pinos DMX
    // Carrega WiFi
    // Registra handlers HTTP
    // Inicia servidor web + mDNS
}

void loop() {
    server.handleClient();    // HTTP
    handleArtNet();          // ArtNet RX
    dmxSend();              // DMX TX periódico
    sendArtPollReply();     // Broadcast poll reply
}
```

---

## 🔧 Como Alterar o Código

### Exemplo 1: Mudar porta UDP
**Antes:** Procurar por "6454" em múltiplos lugares  
**Agora:** Altere em 1 único lugar:
```cpp
// include/config.h
#define DEFAULT_ARTNET_PORT 6454  // ← Mude aqui
```

### Exemplo 2: Adicionar novo endpoint HTTP
1. Declare em `include/handlers.h`
2. Implemente em `src/handlers.cpp`
3. Registre em `main.cpp`:
   ```cpp
   server.on("/novo-endpoint", HTTP_GET, handleNovoEndpoint);
   ```

### Exemplo 3: Ajustar timeout WiFi
```cpp
// include/wifi_module.cpp - linha ~18
while (WiFi.status() != WL_CONNECTED && millis() - t < 15000) {
    // ↑ Mude 15000 para outro valor (ms)
}
```

---

## 📊 Benefícios da Refatoração

| Aspecto | Antes | Depois |
|--------|-------|--------|
| **Linhas em main.cpp** | 1570 | ~90 |
| **Módulos** | 1 arquivo monolítico | 9+ módulos bem definidos |
| **Manutenção** | Difícil, tudo misturado | Fácil, responsabilidade única |
| **Testes** | Impossível testar isolado | Cada módulo testável |
| **Documentação** | Comentários inline espalhados | Headers com documentação clara |
| **Reuso** | Não | Sim, módulos reutilizáveis |
| **Tempo de modificação** | ~30 min encontrar coisa | ~2 min com estrutura clara |

---

## 🚀 Próximos Passos Sugeridos

1. **Criar testes unitários** para módulos (DMX, ArtNet)
2. **Extrair HTML/JS para arquivos** externos (atualmente em PROGMEM com string raw)
3. **Implementar logging modular** com macros
4. **Adicionar suporte a múltiplos universos** ArtNet
5. **Criar config.json persistente** com mais parâmetros

---

## 📚 Referências

- **ArtNet Protocol:** DMX512 over Ethernet (port 6454 UDP)
- **DMX512:** 250 kbaud, 8N2, START_CODE 0x00
- **ESP8266:** 80KB RAM, 4MB Flash em setores de 4KB

---

**Desenvolvido com ❤️ para ONEBit Engenharia**  
*Data: 12 de Março de 2026*
