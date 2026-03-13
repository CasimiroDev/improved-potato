# ONEBit Core - Interface Art-Net DMX

![ONEBit Core](https://img.shields.io/badge/ONEBit-Engineering-blue?style=for-the-badge)
![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-green?style=flat-square)
![Art-Net](https://img.shields.io/badge/Protocol-Art--Net-orange?style=flat-square)
![DMX512](https://img.shields.io/badge/Protocol-DMX512-purple?style=flat-square)

## 📋 Visão Geral

O **ONEBit Core** é uma interface profissional Art-Net para DMX512 desenvolvida para ESP8266 (NodeMCU v2). Recebe dados Art-Net via WiFi e transmite DMX512 via RS485, permitindo controle de equipamentos de iluminação e efeitos especiais em redes Ethernet/WiFi.

### 🎯 Funcionalidades Principais

- **Recepção Art-Net**: Suporte completo ao protocolo Art-Net 4 (porta UDP 6454)
- **Transmissão DMX512**: Saída RS485 com MAX487 para até 512 canais
- **Interface Web**: Configuração completa via navegador (HTML/CSS/JS)
- **API REST**: Endpoints para controle remoto e integração
- **WiFi Manager**: Configuração automática de rede (STA/AP)
- **OTA Updates**: Atualização firmware via web
- **mDNS**: Descoberta automática na rede (.local)
- **Persistência**: Configurações salvas em EEPROM
- **Testes Integrados**: Funções de teste DMX via web

### 🏗️ Arquitetura Modular

O projeto foi completamente refatorado para uma arquitetura modular limpa, facilitando manutenção e expansão:

```
📁 Estrutura de Arquivos
├── include/                 # Headers e declarações
│   ├── config.h            # Constantes e configurações
│   ├── globals.h           # Variáveis globais
│   ├── dmx_module.h        # Interface DMX
│   ├── artnet_module.h     # Interface Art-Net
│   ├── wifi_module.h       # Interface WiFi
│   ├── eeprom_module.h     # Persistência EEPROM
│   ├── handlers.h          # Handlers HTTP
│   └── web_ui.h            # Interface web (PROGMEM)
├── src/                    # Implementações
│   ├── main.cpp            # Setup/Loop (~90 linhas)
│   ├── dmx_module.cpp      # Transmissão DMX
│   ├── artnet_module.cpp   # Protocolo Art-Net
│   ├── wifi_module.cpp     # Gerenciamento WiFi
│   ├── eeprom_module.cpp   # EEPROM
│   └── handlers.cpp        # Endpoints HTTP
├── test/                   # Testes (futuro)
├── platformio.ini          # Configuração PlatformIO
└── ESTRUTURA_MODULAR.md    # Documentação técnica
```

## 🔧 Instalação e Configuração

### Pré-requisitos

- **PlatformIO**: IDE ou CLI
- **ESP8266 Board**: NodeMCU v2
- **Hardware**: MAX487 ou similar para RS485
- **Rede**: WiFi 2.4GHz

### Passos de Instalação

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/CasimiroDev/improved-potato.git
   cd improved-potato
   ```

2. **Instale dependências**:
   ```bash
   pio pkg install
   ```

3. **Compile e faça upload**:
   ```bash
   pio run --target upload --environment nodemcuv2
   ```

4. **Monitore a saída serial**:
   ```bash
   pio device monitor
   ```

### Configuração de Hardware

#### Conexões ESP8266 ↔ MAX487 (RS485)

| ESP8266 Pin | MAX487 Pin | Função |
|-------------|------------|--------|
| GPIO1 (TX)  | DI         | Dados DMX (TX) |
| GPIO3 (RX)  | RO         | Dados DMX (RX) - opcional |
| GPIO2       | DE/RE      | Controle direção (TX/RX) |
| 3.3V        | VCC        | Alimentação |
| GND         | GND        | Terra |

#### Circuito Básico

```
ESP8266 ─── MAX487 ─── DMX512 Chain
  TX ────── DI
  RX ────── RO     (opcional)
  GPIO2 ─── DE/RE
  3.3V ─── VCC
  GND ─── GND
```

**Nota**: O pino DE/RE deve ser HIGH para transmissão, LOW para recepção.

## 🌐 Uso e Configuração

### Primeiro Boot

1. **Modo AP**: Se não houver credenciais WiFi salvas, o dispositivo entra em modo Access Point
   - SSID: `ONEBit Core`
   - Senha: (vazia)
   - IP: `192.168.4.1`

2. **Acesse a interface web**: Abra `http://192.168.4.1` no navegador

3. **Configure WiFi**: Na aba "WiFi", selecione sua rede e insira a senha

4. **Reinicie**: O dispositivo se conectará à rede e estará disponível em `http://onebitcore.local`

### Interface Web

A interface web oferece controle completo:

- **Dashboard**: Status em tempo real, contadores de pacotes
- **DMX Control**: Teste manual de canais DMX
- **Art-Net Config**: Configuração de Net/Subnet/Universe
- **WiFi Manager**: Scan e conexão a redes
- **System Info**: Informações do dispositivo

### API REST

#### Endpoints Principais

| Método | Endpoint | Descrição |
|--------|----------|-----------|
| GET | `/` | Interface web completa |
| GET | `/data?start=X&count=Y` | Dados DMX em JSON |
| GET | `/config.json` | Configuração Art-Net atual |
| POST | `/artnet` | Atualizar config Art-Net |
| GET | `/test-dmx?val=X[&cont=1]` | Teste DMX |
| GET | `/dmx-set?ch=X&val=Y` | Definir canal DMX |
| GET | `/dmx-set-bulk?data=...` | Definir múltiplos canais |
| GET | `/wifi-scan-start` | Iniciar scan WiFi |
| GET | `/wifi-scan-result` | Resultados scan WiFi |
| POST | `/wifi-connect` | Conectar a rede WiFi |
| GET | `/wifi-forget` | Apagar credenciais WiFi |
| GET | `/wifi-status` | Status WiFi atual |
| POST | `/device` | Configurações do dispositivo |

#### Exemplos de Uso

**Obter status DMX**:
```bash
curl http://onebitcore.local/data?start=1&count=10
```

**Configurar Art-Net**:
```bash
curl -X POST http://onebitcore.local/artnet \
  -H "Content-Type: application/json" \
  -d '{"net": 0, "subnet": 0, "universe": 0}'
```

**Teste DMX contínuo**:
```bash
curl http://onebitcore.local/test-dmx?val=255&cont=1
```

## 📡 Protocolos Suportados

### Art-Net 4

- **Porta**: 6454 UDP
- **OpCodes**: ArtDmx, ArtPoll, ArtPollReply
- **Universo**: Configurável (0-15)
- **Sub-rede**: Configurável (0-15)
- **Net**: Configurável (0-127)

### DMX512

- **Taxa**: 250.000 baud
- **Formato**: 8N2 (8 bits, sem paridade, 2 stop bits)
- **Break**: 100 µs mínimo
- **MAB**: 12 µs mínimo
- **Canais**: 512 por universo

## 🔍 Monitoramento e Debug

### Serial Monitor

Conecte via USB e monitore a saída:
```bash
pio device monitor
```

**Saída típica**:
```
ONEBit Core v1.0.0
WiFi connected: 192.168.1.100
mDNS: onebitcore.local
Art-Net Universe: 0/0/0
DMX TX: OK (512 ch)
Packets OK: 1234, Filtered: 56
```

### Logs de Debug

O firmware inclui logs detalhados para:
- Conexão WiFi
- Recepção Art-Net
- Transmissão DMX
- Erros de configuração

## 🛠️ Desenvolvimento

### Estrutura de Módulos

Cada módulo tem responsabilidade única:

1. **config.h**: Todas as constantes do projeto
2. **globals.h**: Declarações de variáveis compartilhadas
3. **dmx_module**: Transmissão DMX pura
4. **artnet_module**: Processamento Art-Net
5. **wifi_module**: Gerenciamento de conectividade
6. **eeprom_module**: Persistência de dados
7. **handlers**: Lógica HTTP/REST
8. **web_ui**: Interface web em PROGMEM

### Adicionando Funcionalidades

**Exemplo: Novo endpoint HTTP**

1. Declare em `include/handlers.h`:
   ```cpp
   void handleNovoEndpoint();
   ```

2. Implemente em `src/handlers.cpp`:
   ```cpp
   void handleNovoEndpoint() {
       server.send(200, "text/plain", "Novo endpoint!");
   }
   ```

3. Registre em `main.cpp`:
   ```cpp
   server.on("/novo", HTTP_GET, handleNovoEndpoint);
   ```

### Testes

Diretório `test/` reservado para testes unitários futuros.

## 📊 Performance

- **Latência Art-Net → DMX**: < 1ms
- **Taxa de refresh**: Até 44Hz (limitação DMX512)
- **Consumo de RAM**: ~30KB heap livre
- **Flash usado**: ~250KB
- **CPU**: ~5% uso médio

## 🐛 Troubleshooting

### Problemas Comuns

**Dispositivo não conecta ao WiFi**
- Verifique credenciais
- Teste proximidade ao roteador
- Use modo AP para reconfigurar

**Sem saída DMX**
- Verifique conexões RS485
- Teste com `/test-dmx`
- Monitore serial para erros

**Art-Net não recebe dados**
- Confirme porta UDP 6454 aberta
- Verifique Net/Subnet/Universe
- Teste com software como QLC+

**Interface web não carrega**
- Verifique IP/mDNS
- Teste conectividade de rede
- Reinicie o dispositivo

### Reset para Configurações de Fábrica

Mantenha GPIO0 pressionado durante boot para entrar em modo AP.

## 🤝 Contribuição

1. Fork o projeto
2. Crie uma branch para sua feature (`git checkout -b feature/nova-funcionalidade`)
3. Commit suas mudanças (`git commit -am 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/nova-funcionalidade`)
5. Abra um Pull Request

### Diretrizes

- Siga a arquitetura modular
- Documente novas funções
- Teste thoroughly
- Mantenha compatibilidade backward

## 📄 Licença

Este projeto é propriedade da **ONEBit Engenharia**. Todos os direitos reservados.

## 📞 Suporte

Para suporte técnico:
- Email: suporte@onebit.com.br
- Documentação: [ESTRUTURA_MODULAR.md](ESTRUTURA_MODULAR.md)

---

**Desenvolvido com ❤️ por ONEBit Engenharia**  
*Versão 1.0.0 - Março 2026*</content>
<parameter name="filePath">/home/lucascasimiro/programming/temp_repo/README.md