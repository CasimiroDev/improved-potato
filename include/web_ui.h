#ifndef WEB_UI_H
#define WEB_UI_H

#include <pgmspace.h> // Corrigido: use <pgmspace.h> em vez de <pgmspace.h>

// ─────────────────────────────────────────────────────────────
// HEAD + CSS
// ─────────────────────────────────────────────────────────────
static const char HTML_HEAD[] PROGMEM = R"HTML(<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>ONEBit Core</title>
  <style>
    *{box-sizing:border-box;margin:0;padding:0}
    body{font-family:Arial,Helvetica,sans-serif;background:#0a0e14;color:#e9edf2}
    .page{max-width:980px;margin:0 auto;padding:10px 10px 36px}

    /* ── HEADER ── */
    .header{display:flex;align-items:center;justify-content:space-between;gap:10px;
            padding:8px 2px;border-bottom:1px solid #1b2431;margin-bottom:10px;flex-wrap:wrap}
    .brand{display:flex;align-items:center;gap:10px}
    .brand-logo{width:44px;height:44px;border-radius:8px;background:#fff;
                display:flex;align-items:center;justify-content:center;overflow:hidden;flex-shrink:0}
    .brand-logo img{max-width:100%;max-height:100%;display:block}
    .brand-main{font-size:1.1em;font-weight:bold;color:#0069b4;letter-spacing:.02em}
    .brand-sub{font-size:.75em;color:#6b7a8d;margin-top:2px}
    .header-right{text-align:right;font-size:.82em;color:#6b7a8d;line-height:1.6}
    .header-right b{color:#e9edf2}
    #dot{display:inline-block;width:8px;height:8px;border-radius:50%;
         background:#333;margin-left:5px;vertical-align:middle;transition:background .3s}

    /* ── TABS ── */
    .tabs{display:flex;overflow-x:auto;background:#0d1219;border-radius:8px;
          border:1px solid #1b2431;margin-bottom:12px}
    .tab{flex:1;min-width:76px;padding:9px 6px;text-align:center;cursor:pointer;
         font-size:.78em;color:#6b7a8d;border-bottom:2px solid transparent;
         white-space:nowrap;user-select:none;transition:color .2s,border-color .2s}
    .tab.active{color:#00a4ff;border-bottom-color:#00a4ff;background:#0b1520}
    .tab:hover:not(.active){color:#c0ccd8}
    .pane{display:none}
    .pane.active{display:block}

    /* ── CARDS ── */
    .card{background:#0d1219;border-radius:10px;padding:14px 14px 12px;
          margin-bottom:12px;border:1px solid #1b2431}
    .card h2{font-size:.9em;font-weight:bold;color:#8a9bb0;text-transform:uppercase;
             letter-spacing:.06em;margin-bottom:12px;padding-bottom:6px;border-bottom:1px solid #1b2431}

    /* ── METRICS ── */
    .dash-metrics{display:grid;grid-template-columns:repeat(auto-fit,minmax(120px,1fr));
                  gap:10px;margin-bottom:12px}
    .metric{background:#0a0e14;border:1px solid #1b2431;border-radius:8px;
            padding:12px 10px 10px;text-align:center}
    .metric-label{font-size:.68em;color:#6b7a8d;text-transform:uppercase;
                  letter-spacing:.05em;margin-bottom:6px}
    .metric-value{font-size:1.45em;font-weight:bold;line-height:1;color:#e9edf2}
    .metric-unit{font-size:.65em;color:#6b7a8d;margin-top:4px}

    /* ── BADGES ── */
    .status-badge{display:inline-flex;align-items:center;gap:6px;padding:4px 12px;
                  border-radius:20px;font-size:.82em;font-weight:bold}
    .status-badge.ok  {background:#0d2d1a;color:#4caf50;border:1px solid #1a5c32}
    .status-badge.warn{background:#2a1e09;color:#ffb74d;border:1px solid #5c3d12}
    .status-badge.err {background:#2a0d0d;color:#ef5350;border:1px solid #5c1a1a}
    .badge-dot{width:7px;height:7px;border-radius:50%}
    .ok   .badge-dot{background:#4caf50}
    .warn .badge-dot{background:#ffb74d}
    .err  .badge-dot{background:#ef5350}

    /* ── COLORS ── */
    .ok  {color:#4caf50}
    .warn{color:#ffb74d}
    .err {color:#ef5350}

    /* ── INFO ROWS ── */
    .info-row{display:flex;justify-content:space-between;align-items:center;
              font-size:.82em;padding:5px 0;border-bottom:1px solid #141b24}
    .info-row:last-child{border-bottom:none}
    .info-row .lk{color:#6b7a8d}
    .info-row .vl{color:#e9edf2;font-weight:bold;text-align:right}

    /* ── BARS ── */
    .ch-bars{display:flex;gap:10px;flex-wrap:wrap}
    .ch-bar-item{flex:1;min-width:70px}
    .ch-bar-label{font-size:.68em;color:#6b7a8d;margin-bottom:4px;
                  display:flex;justify-content:space-between}
    .ch-bar-track{background:#111820;border-radius:4px;height:8px;overflow:hidden}
    .ch-bar-fill{height:100%;border-radius:4px;
                 background:linear-gradient(90deg,#006b30,#00e676);transition:width .4s}

    /* ── DMX GRID (aba Canais) ── */
    .uni-selector{display:flex;align-items:center;gap:12px;flex-wrap:wrap;margin-bottom:14px}
    .uni-selector .lbl{font-size:.72em;color:#6b7a8d;white-space:nowrap}
    .uni-tabs{display:flex;gap:5px;flex-wrap:wrap}
    .uni-tab{padding:5px 14px;border-radius:20px;border:1px solid #1b2431;
             background:#0a0e14;color:#6b7a8d;font-size:.78em;cursor:pointer;
             transition:all .15s;user-select:none}
    .uni-tab.active{background:#0b2a45;color:#00a4ff;border-color:#00a4ff}
    .uni-tab:hover:not(.active){background:#111820;color:#c0ccd8}
    .uni-info{font-size:.72em;color:#4a6080;margin-bottom:10px}
    .dmx-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(52px,1fr));gap:5px}
    .dmx-cell{aspect-ratio:1;border-radius:5px;display:flex;flex-direction:column;
              align-items:center;justify-content:center;cursor:default;
              border:1px solid #1b2431;transition:background-color .25s;
              overflow:hidden;padding:2px}
    .dmx-ch{font-size:.6em;color:rgba(255,255,255,.55);font-weight:bold;line-height:1}
    .dmx-val{font-size:.72em;font-weight:bold;color:#fff;line-height:1;margin-top:3px}

    /* ── MESA DE CONTROLE DMX ── */
    .console-top{display:flex;align-items:center;gap:10px;flex-wrap:wrap;margin-bottom:14px}
    .console-top .lbl{font-size:.72em;color:#6b7a8d;margin-bottom:3px}
    .console-ch-input{width:80px;padding:5px 7px;border-radius:4px;
                      border:1px solid #1b2431;background:#080c10;
                      color:#e9edf2;font-size:.88em}
    .console-globals{display:flex;gap:6px;flex-wrap:wrap;margin-left:auto}
    .btn-mini{padding:6px 12px;border:none;border-radius:4px;cursor:pointer;
              font-size:.78em;color:#fff;font-weight:bold;transition:filter .15s}
    .btn-mini.full  {background:#2e7d32}
    .btn-mini.half  {background:#e65100}
    .btn-mini.zero  {background:#37474f}
    .btn-mini:hover {filter:brightness(1.2)}

    .faders-wrap{display:flex;overflow-x:auto;padding-bottom:10px;
                 margin:0 -14px;padding-left:14px;padding-right:14px}
    .fader-col{display:flex;flex-direction:column;align-items:center;
               flex-shrink:0;width:56px;margin:0 auto}
    .fader-ch-lbl{font-size:.7em;color:#6b7a8d;margin-bottom:6px;font-weight:bold}
    .fader-track{width:20px;height:160px;background:#111820;border-radius:10px;
                 position:relative;cursor:ns-resize;user-select:none;
                 border:1px solid #1b2431;overflow:hidden}
    .fader-fill{position:absolute;bottom:0;left:0;width:100%;border-radius:10px;
                background:linear-gradient(to top,#006b30,#00e676);transition:height .05s linear}
    .fader-thumb{position:absolute;left:0;width:100%;height:14px;background:#00a4ff;
                 border-radius:7px;border:1px solid #0069b4;box-shadow:0 0 8px rgba(0,164,255,.4);
                 cursor:ns-resize;transition:bottom .05s linear}
    .fader-val-lbl{font-size:.75em;color:#e9edf2;margin-top:8px;font-weight:bold}

    /* ── FORMULÁRIOS ── */
    .form-group{margin-bottom:10px}
    .lbl{font-size:.75em;color:#6b7a8d;margin-bottom:4px}
    input[type="text"],input[type="password"],input[type="number"],select{
      width:100%;padding:8px 10px;border-radius:6px;border:1px solid #1b2431;
      background:#080c10;color:#e9edf2;font-size:.88em;
      -webkit-appearance:none; /* Remove default styling for iOS */
    }
    input[type="number"]{-moz-appearance:textfield} /* Remove arrows for Firefox */
    input[type="number"]::-webkit-outer-spin-button,
    input[type="number"]::-webkit-inner-spin-button {
        -webkit-appearance: none; margin: 0; /* Remove arrows for Chrome, Safari, Edge */
    }
    select{padding-right:30px;background-image:url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24' fill='none' stroke='%236b7a8d' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpolyline points='6 9 12 15 18 9'%3E%3C/polyline%3E%3C/svg%3E");
           background-repeat:no-repeat;background-position:right 8px center;
           background-size:16px}
    .btn{padding:9px 16px;border:none;border-radius:6px;cursor:pointer;
         font-size:.88em;font-weight:bold;transition:filter .15s}
    .btn-ok    {background:#2e7d32;color:#fff}
    .btn-danger{background:#c62828;color:#fff}
    .btn-soft  {background:#1b2431;color:#e9edf2}
    .btn-alt   {background:#37474f;color:#e9edf2}
    .btn:hover {filter:brightness(1.2)}

    /* ── GRID DE 2 E 3 COLUNAS ── */
    .grid2{display:grid;grid-template-columns:1fr 1fr;gap:10px}
    .grid3{display:grid;grid-template-columns:1fr 1fr 1fr;gap:10px}
    @media (max-width:480px){
      .grid2,.grid3{grid-template-columns:1fr}
    }

    /* ── TÍTULOS DE SEÇÃO ── */
    .section-title{font-size:.75em;color:#8a9bb0;text-transform:uppercase;
                   letter-spacing:.05em;margin:16px 0 8px;padding-bottom:4px;
                   border-bottom:1px solid #1b2431}

    /* ── LISTA WIFI ── */
    .wifi-item{display:flex;justify-content:space-between;align-items:center;
               padding:8px 10px;border-bottom:1px solid #141b24;cursor:pointer;
               font-size:.88em;color:#e9edf2;transition:background .15s}
    .wifi-item:hover{background:#111820}
    .wifi-item:last-child{border-bottom:none}
    .wifi-bars{font-size:.9em;color:#6b7a8d}

    /* ── OTA ── */
    .ota-steps{font-size:.82em;color:#b0bec5;padding-left:18px;line-height:1.7;margin-top:4px}
    .ota-dropzone{border:2px dashed #1b2431;border-radius:8px;padding:20px;
                  text-align:center;color:#6b7a8d;font-size:.9em;cursor:pointer;
                  transition:all .2s;position:relative;overflow:hidden;margin-top:10px}
    .ota-dropzone.dragover{border-color:#00a4ff;background:#0b1520}
    .ota-dropzone input[type="file"]{position:absolute;left:0;top:0;width:100%;
                                     height:100%;opacity:0;cursor:pointer}
    .ota-icon{font-size:2.2em;margin-bottom:8px;display:block;color:#4a6080}
    .ota-filename{font-size:.8em;color:#e9edf2;margin-top:10px;font-weight:bold}
    .prog-wrap{background:#111820;border-radius:6px;height:16px;overflow:hidden;
               margin-top:12px;border:1px solid #1b2431;display:none}
    .prog-bar{height:100%;width:0%;background:#0069b4;border-radius:6px;
              display:flex;align-items:center;justify-content:center;
              font-size:.7em;color:#fff;font-weight:bold;transition:width .3s linear}
    .ota-msg{font-size:.8em;min-height:1.2em;margin-top:8px}
    .ota-msg.err{color:#ef5350}
    .ota-msg.info{color:#9bd8ff}
    .ota-msg.ok{color:#4caf50}

    /* -- NOVO: OTA TABS -- */
    .ota-tabs{display:flex;gap:5px;margin-bottom:12px;border-bottom:1px solid #1b2431;padding-bottom:5px}
    .ota-tab{padding:6px 12px;border-radius:6px;cursor:pointer;font-size:.8em;
             color:#6b7a8d;background:#0a0e14;border:1px solid transparent;
             transition:all .15s;user-select:none}
    .ota-tab.active{background:#0b1520;color:#00a4ff;border-color:#00a4ff}
    .ota-tab:hover:not(.active){color:#c0ccd8;background:#111820}
    .ota-pane{display:none;margin-top:10px}
    .ota-pane.active{display:block}

    /* ── REBOOT OVERLAY ── */
    .reboot-overlay{position:fixed;top:0;left:0;width:100%;height:100%;
                    background:rgba(0,0,0,.8);display:none;align-items:center;
                    justify-content:center;z-index:1000}
    .reboot-box{background:#0d1219;border-radius:12px;padding:24px;text-align:center;
                border:1px solid #1b2431;box-shadow:0 8px 20px rgba(0,0,0,.4)}
    .spinner{border:4px solid rgba(0,164,255,.2);border-top:4px solid #00a4ff;
             border-radius:50%;width:30px;height:30px;animation:spin 1s linear infinite;
             margin:10px auto}
    @keyframes spin{0%{transform:rotate(0deg)}100%{transform:rotate(360deg)}}

  </style>
</head>)HTML";
// ─────────────────────────────────────────────────────────────
// BODY
// ─────────────────────────────────────────────────────────────

static const char HTML_BODY[] PROGMEM = R"HTML(
<body>
<div class="page">
  <div class="header">
    <div class="brand">
      <div class="brand-logo"><img src="https://onebit.com.br/wp-content/uploads/2023/08/logo-onebit-icon-white.png" alt="ONEBit"></div>
      <div>
        <div class="brand-main">ONEBit Core</div>
        <div class="brand-sub">ArtNet &#harr; DMX512</div>
      </div>
    </div>
    <div class="header-right">
      <span id="hdr-ip">IP: <b>—</b> (AP)</span><br>
      <span id="hdr-artnet">Net:<b>—</b> Sub:<b>—</b> Uni:<b>—</b> &nbsp;|&nbsp; UDP:<b>6454</b></span>
      <span id="dot"></span>
    </div>
  </div>

  <!-- ══════════════════════════════════════════
       TABS
  ══════════════════════════════════════════ -->
  <div class="tabs">
    <div class="tab active" data-tab="status" onclick="showTab('status')">Status</div>
    <div class="tab" data-tab="canais" onclick="showTab('canais')">Canais</div>
    <div class="tab" data-tab="config" onclick="showTab('config')">Config</div>
    <div class="tab" data-tab="ota" onclick="showTab('ota')">Firmware</div>
  </div>

  <!-- ══════════════════════════════════════════
       PANE: STATUS
  ══════════════════════════════════════════ -->
  <section id="pane-status" class="pane active">
    <div class="card">
      <h2>ArtNet DMX</h2>
      <div class="dash-metrics">
        <div class="metric">
          <div class="metric-label">Status RX</div>
          <div class="status-badge err" id="rx-badge">
            <span class="badge-dot"></span>Aguardando
          </div>
        </div>
        <div class="metric">
          <div class="metric-label">Último pacote</div>
          <div class="metric-value" id="m-ago">—</div>
          <div class="metric-unit">segundos atrás</div>
        </div>
        <div class="metric">
          <div class="metric-label">Pacotes OK</div>
          <div class="metric-value" id="m-ok">0</div>
        </div>
        <div class="metric">
          <div class="metric-label">Pacotes filtrados</div>
          <div class="metric-value" id="m-filt">0</div>
        </div>
      </div>
      <div class="info-row">
        <span class="lk">Endereço ArtNet</span>
        <span id="st-artnet" class="vl">— / — / —</span>
      </div>
      <div class="info-row">
        <span class="lk">Porta UDP</span>
        <span class="vl">6454</span>
      </div>
      <div class="info-row">
        <span class="lk">Intervalo DMX</span>
        <span id="m-interval" class="vl">25ms</span>
      </div>
    </div>

    <div class="card">
      <h2>&#8984; WiFi</h2>
      <div class="info-row">
        <span class="lk">Status</span>
        <span id="ws-status" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Rede (SSID)</span>
        <span id="ws-ssid" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Endereço IP</span>
        <span id="ws-ip" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Sinal (RSSI)</span>
        <span id="ws-rssi" class="vl">—</span>
      </div>
    </div>

    <div class="card">
      <h2>Mesa de Controle DMX</h2>

      <!-- Controles superiores -->
      <div class="console-top">
        <div id="con-start-wrap">
          <div class="lbl">Canal inicial (1–497)</div>
          <input class="console-ch-input" type="number" id="con-start"
                 min="1" max="497" value="1" oninput="consoleRebuild()">
        </div>
        <div class="console-globals">
          <button class="btn-mini full" onclick="consoleFill(255)">FULL</button>
          <button class="btn-mini half" onclick="consoleFill(128)">HALF</button>
          <button class="btn-mini zero" onclick="consoleFill(0)">ZERO</button>
          <button class="btn-mini" style="background:#8e24aa;" onclick="consoleRandom()">RANDOM</button> <!-- NOVO BOTÃO -->
      </div>
      </div>

      <!-- Faders -->
      <div id="faders-section">
        <div class="faders-wrap" id="faders-wrap"></div>
      </div>

      <div class="console-hint">
        Scroll / drag / touch nos faders para controlar os canais DMX.
      </div>
    </div>
  </section>

  <!-- ══════════════════════════════════════════
       PANE: CANAIS — visualizar universo ativo
  ══════════════════════════════════════════ -->
  <section id="pane-canais" class="pane">
    <div class="card">
      <h2 id="card-ch-title">Canais DMX — Universo Ativo</h2>

      <div class="uni-info" id="uni-info">
        Exibindo canais 1–512 do universo ArtNet ativo.
      </div>

      <!-- Legenda de cor -->
      <div style="display:flex;align-items:center;gap:8px;margin-bottom:12px;
                  font-size:.72em;color:#6b7a8d">
        <div style="width:80px;height:8px;border-radius:4px;
             background:linear-gradient(90deg,#080c10,#00e053);
             border:1px solid #1b2431"></div>
        <span>0 (preto) → 255 (verde)</span>
      </div>

      <div class="dmx-grid" id="ch-grid"></div>
    </div>
  </section>

  <!-- ══════════════════════════════════════════
       PANE: CONFIG
  ══════════════════════════════════════════ -->
  <section id="pane-config" class="pane">

    <!-- ArtNet -->
    <div class="card">
      <h2>Endereço ArtNet</h2>
      <form action="/artnet" method="POST">
        <div class="grid3">
          <div>
            <div class="lbl">Net (0–127)</div>
            <input type="number" name="net" min="0" max="127" value="0">
          </div>
          <div>
            <div class="lbl">Sub-Net (0–15)</div>
            <input type="number" name="subnet" min="0" max="15" value="0">
          </div>
          <div>
            <div class="lbl">Universo (0–15)</div>
            <input type="number" name="universe" min="0" max="15" value="0">
          </div>
        </div>
        <div style="margin-top:4px;font-size:.72em;color:#4a6080">
          Porta UDP fixa: <b style="color:#8a9bb0">6454</b>
        </div>

        <!-- Campos de DMX avançado e Failsafe/Hold removidos, pois não são suportados pelo backend atual -->

        <button class="btn btn-ok" type="submit" style="margin-top:14px">
          &#10003; Aplicar configurações ArtNet
        </button>
      </form>
    </div>

    <!-- Dispositivo -->
    <div class="card">
      <h2>Dispositivo</h2>
      <form action="/device" method="POST">
        <div class="grid2">
          <div>
            <div class="lbl">Nome do dispositivo</div>
            <input type="text" name="devname" maxlength="32" placeholder="ONEBit-Core">
          </div>
          <div>
            <div class="lbl">Senha do AP (mín. 8 chars)</div>
            <input type="password" name="appass" minlength="8" maxlength="32"
                   placeholder="••••••••">
          </div>
        </div>
        <div style="margin-top:10px">
          <label style="display:flex;align-items:center;gap:8px;font-size:.83em;cursor:pointer">
            <input type="checkbox" name="status_led" value="1" checked style="width:auto">
            LED de status onboard ativo
          </label>
        </div>
        <button class="btn" type="submit" style="margin-top:12px">
          &#10003; Salvar configurações do dispositivo
        </button>
      </form>
    </div>

    <!-- WiFi dentro de Config -->
    <div class="card">
      <h2>&#8984; WiFi</h2>

      <div class="section-title">Conexão atual</div>
      <div class="info-row">
        <span class="lk">Status</span>
        <span id="cfg-ws-status" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Rede (SSID)</span>
        <span id="cfg-ws-ssid" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Endereço IP</span>
        <span id="cfg-ws-ip" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Sinal (RSSI)</span>
        <span id="cfg-ws-rssi" class="vl">—</span>
      </div>
      <button class="btn btn-danger" style="margin-top:10px" onclick="wifiForget()">
        &#10006; Esquecer rede e abrir AP
      </button>

      <div class="section-title">Redes disponíveis</div>
      <button class="btn btn-soft" id="wifi-scan-btn" onclick="wifiScan()">
        &#8635; Buscar redes WiFi
      </button>
      <div id="wifi-list" style="margin-top:10px"></div>

      <div id="wifi-form-card" style="display:none;margin-top:10px">
        <div class="section-title">Conectar à rede</div>
        <div style="margin-bottom:8px">
          <div class="lbl">SSID</div>
          <input type="text" id="wifi-ssid">
        </div>
        <div style="margin-bottom:8px">
          <div style="position:relative">
            <div class="lbl">Senha</div>
            <input type="password" id="wifi-pass" style="padding-right:32px">
            <span onclick="togglePass()"
                  style="position:absolute;right:9px;top:7px;cursor:pointer;
                         font-size:1.05em;user-select:none">👁️</span>
          </div>
        </div>
        <div id="wifi-form-msg" style="font-size:.8em;min-height:1.2em;margin-bottom:4px"></div>
        <button class="btn btn-ok" onclick="wifiConnect()">
          &#10003; Conectar e reiniciar
        </button>
        <button class="btn btn-alt" style="margin-top:6px"
                onclick="document.getElementById('wifi-form-card').style.display='none'">
          Cancelar
        </button>
      </div>
    </div>

  </section>

  <!-- ══════════════════════════════════════════
       PANE: OTA / FIRMWARE
  ══════════════════════════════════════════ -->
  <section id="pane-ota" class="pane">

    <div class="card">
      <h2>Versão Atual</h2>
      <div class="info-row">
        <span class="lk">Firmware</span>
        <span id="fw-version" class="vl">vX.Y.Z</span>
      </div>
      <div class="info-row">
        <span class="lk">Data de Compilação</span>
        <span id="fw-build-date" class="vl">YYYY-MM-DD HH:MM</span>
      </div>
    </div>

    <div class="card">
      <h2>Atualizar Firmware</h2>

      <div class="ota-tabs">
        <div class="ota-tab active" data-ota-tab="online" onclick="showOtaTab('online')">Online</div>
        <div class="ota-tab" data-ota-tab="manual" onclick="showOtaTab('manual')">Upload Manual</div>
      </div>

      <!-- OTA Pane: Online Update -->
      <div id="ota-pane-online" class="ota-pane active">
        <p style="font-size:.82em;color:#b0bec5;margin-bottom:10px;">
          Verifique e instale a versão mais recente do firmware diretamente da internet.
          Certifique-se de que o dispositivo esteja conectado a uma rede WiFi com acesso à internet.
        </p>
        <button class="btn btn-ok" id="ota-check-btn" onclick="otaCheckForUpdate()">
          &#8635; Verificar por Atualizações
        </button>
        <div id="ota-online-status" style="font-size:.8em;min-height:1.2em;margin-top:10px;"></div>
        <button class="btn" id="ota-install-btn" onclick="otaInstallUpdate()" disabled
                style="margin-top:12px;background:#00a4ff;color:#000;display:none;">
          &#8679; Instalar Atualização (v<span id="ota-new-version"></span>)
        </button>
      </div>

      <!-- OTA Pane: Manual Upload -->
      <div id="ota-pane-manual" class="ota-pane">
        <p style="font-size:.82em;color:#b0bec5;margin-bottom:10px;">
          Se você baixou um arquivo de firmware (.bin) do nosso site, pode enviá-lo aqui.
        </p>
        <div class="ota-dropzone" id="ota-dz">
          <input type="file" id="ota-input" accept=".bin">
          <span class="ota-icon">&#8681;</span>
          <div><b>Clique aqui</b> ou arraste o arquivo <code>.bin</code></div>
          <div style="font-size:.72em;color:#6b7a8d;margin-top:3px">
            Apenas <b>.bin</b> &middot; máximo 1 MB
          </div>
          <div class="ota-filename" id="ota-fname">Nenhum arquivo selecionado</div>
        </div>
        <div class="prog-wrap" id="ota-prog-wrap">
          <div class="prog-bar" id="ota-prog-bar">0%</div>
        </div>
        <div class="ota-msg" id="ota-msg"></div>
        <button class="btn" id="ota-btn" onclick="otaUpload()" disabled
                style="margin-top:12px;background:#00a4ff;color:#000">
          &#8679; Enviar Firmware
        </button>
      </div>
    </div>

    <div class="card" style="border-color:#3d2600">
      <h2 style="color:#ffb74d">&#9888; Avisos importantes</h2>
      <ul style="font-size:.82em;color:#b0bec5;padding-left:18px;line-height:1.7;margin-top:4px">
        <li>Use somente firmwares oficiais da ONEBit Engenharia.</li>
        <li>Um firmware incorreto pode exigir reprogramação via USB.</li>
        <li>Mantenha a energia estável durante todo o processo.</li>
        <li>Não feche esta aba enquanto a atualização estiver em andamento.</li>
      </ul>
    </div>

  </section>

  <!-- Reboot overlay -->
  <div class="reboot-overlay" id="reboot-overlay">
    <div class="reboot-box">
      <div style="font-size:1.6em;color:#0069b4">&#9654;</div>
      <h2 style="color:#4caf50;margin:6px 0;font-size:1em">Reiniciando...</h2>
      <div class="spinner"></div>
      <p style="color:#6b7a8d;font-size:.84em">Reconectando automaticamente em:</p>
      <div style="font-size:1.6em;font-weight:bold;color:#00a4ff;margin:4px 0"
           id="reboot-cd">15</div>
      <p style="color:#4a5568;font-size:.73em;margin-top:6px">
        Se não reconectar, acesse manualmente o IP do dispositivo.
      </p>
    </div>
  </div>

</div><!-- /.page -->
)HTML";

// ─────────────────────────────────────────────────────────────
// JAVASCRIPT
// ─────────────────────────────────────────────────────────────
static const char HTML_JS[] PROGMEM = R"HTML(
<script>
  // Variáveis globais para a mesa de controle DMX
  var conValues     = new Array(16).fill(0); // Armazena os valores dos 16 faders
  var conDragging   = -1; // Índice do fader sendo arrastado (-1 se nenhum)
  var conDragStartY = 0;  // Posição Y inicial do arrasto
  var conDragStartVal = 0; // Valor inicial do fader ao iniciar o arrasto

  // -- NOVO: Variáveis globais para OTA online --
  var latestFwUrl = ''; // Global para armazenar a URL do firmware mais recente
  var latestFwVersion = ''; // Global para armazenar a versão do firmware mais recente
  var currentFwVersion = ''; // Global para armazenar a versão atual do firmware

  // ═══════════════════════════════════════
  //  TABS
  // ═══════════════════════════════════════
  function showTab(id){
    document.querySelectorAll('.tab').forEach(function(t){
      t.classList.toggle('active', t.dataset.tab===id);
    });
    document.querySelectorAll('.pane').forEach(function(p){
      p.classList.toggle('active', p.id==='pane-'+id);
    });
    try{localStorage.setItem('tab',id);}catch(e){}
    if(id==='config') loadConfigValues(); // Carrega configs ao abrir aba
    if(id==='config' || id==='status') wifiStatusUpdate(); // Atualiza WiFi ao abrir aba
    if(id==='ota') otaLoadInfo(); // -- NOVO: Carrega info de firmware ao abrir aba OTA --
  }

  // ═══════════════════════════════════════
  //  OTA TABS
  // ═══════════════════════════════════════
  function showOtaTab(id){
    document.querySelectorAll('.ota-tab').forEach(function(t){
      t.classList.toggle('active', t.dataset.otaTab===id);
    });
    document.querySelectorAll('.ota-pane').forEach(function(p){
      p.classList.toggle('active', p.id==='ota-pane-'+id);
    });
    try{localStorage.setItem('otaTab',id);}catch(e){}
    // Reset messages when switching tabs
    otaMsg('','');
    otaOnlineStatus('','');
  }

  // ═══════════════════════════════════════
  //  BOOT
  // ═══════════════════════════════════════
  var updTimer   = null;
  var scanPollTimer = null;
  var otaFile    = null;
  // selUni não é mais necessário, pois o grid sempre mostra o universo ativo do dispositivo

  document.addEventListener('DOMContentLoaded', function(){
    var t = 'status';
    try{ t = localStorage.getItem('tab') || 'status'; }catch(e){}
    var otaT = 'online'; // <-- Adicione esta linha de volta
    try{ otaT = localStorage.getItem('otaTab') || 'online'; }catch(e){} // E esta

    showTab(t);
    showOtaTab(otaT);
    consoleRebuild();
    wifiStatusUpdate();
    setInterval(wifiStatusUpdate, 10000);
    setInterval(upd, 1000);
    otaInit();
    otaLoadInfo();
  });

  // ═══════════════════════════════════════
  //  POLLING PRINCIPAL — upd()
  // ═══════════════════════════════════════
  function schedUpd(){
    if(updTimer) clearTimeout(updTimer);
    updTimer = setTimeout(upd, 200);
  }

  function dmxColor(v){
    var g = Math.round(v * 0.88);
    var bg = 'rgb(0,'+g+','+Math.round(v*0.2)+')';
    var border = (v>10) ? ('rgba(0,'+Math.round(g*1.2)+',60,.6)') : '#1b2431';
    return {bg:bg, border:border};
  }

  function upd(){
    // Não passa mais 'uni', pois o backend sempre retorna o universo ativo
    fetch('/data?start=1&count=512')
      .then(function(r){ return r.json(); })
      .then(function(d){

        /* ── badge ── */
        var badge = document.getElementById('rx-badge');
        if(!d.running){
          badge.className = 'status-badge err';
          badge.innerHTML = '<span class="badge-dot"></span>Aguardando';
        } else if(d.ago < 3){
          badge.className = 'status-badge ok';
          badge.innerHTML = '<span class="badge-dot"></span>Ativo';
        } else {
          badge.className = 'status-badge warn';
          badge.innerHTML = '<span class="badge-dot"></span>Sem pacotes';
        }

        /* ── métricas ── */
        document.getElementById('m-ago').textContent =
          d.running ? (d.ago+'s') : '—';
        document.getElementById('m-ok').textContent   = d.pktOk;
        document.getElementById('m-filt').textContent = d.pktFilt;
        var ms = d.interval;
        document.getElementById('m-interval').textContent =
          ms===0 ? 'MAX' : ms<1000 ? (ms+'ms') : ((ms/1000).toFixed(1)+'s');

        /* ── dot pisca ── */
        var dot = document.getElementById('dot');
        dot.style.background =
          (dot.style.background === 'rgb(76, 175, 80)') ? '#333' : '#4caf50';

        /* ── header ArtNet ── */
        if(d.net !== undefined){
          document.getElementById('hdr-artnet').innerHTML =
            'Net:<b>'+d.net+'</b> Sub:<b>'+d.sub+'</b> Uni:<b>'+d.uni+
            '</b> &nbsp;|&nbsp; UDP:<b>6454</b>';
          document.getElementById('st-artnet').textContent =
            d.net+' / '+d.sub+' / '+d.uni;
        }

        /* ── uni-info: sempre mostra o universo ativo ── */
        var uniInfo = document.getElementById('uni-info');
        if(d.uni !== undefined){ // d.uni é o universo ativo do dispositivo
          uniInfo.innerHTML =
            'Exibindo canais 1–512 do universo ArtNet ativo: <b>'+d.uni+'</b>';
        }
        document.getElementById('card-ch-title').textContent =
          'Canais DMX — Universo ' + (d.uni !== undefined ? d.uni : 'Ativo');


        /* ── grid 512 canais — usa dados do universo solicitado ── */
        var grid   = document.getElementById('ch-grid');
        var html   = '';
        var chArr  = d.ch      || [];
        var chStart = d.chStart || 1;
        for(var i = 0; i < chArr.length; i++){
          var chNum = chStart + i;
          var v     = chArr[i];
          var c     = dmxColor(v);
          var tc    = (v>100) ? 'rgba(255,255,255,.9)' : 'rgba(255,255,255,.5)';
          html +=
            '<div class="dmx-cell" style="background-color:'+c.bg+
            ';border-color:'+c.border+'">' +
              '<span class="dmx-ch"  style="color:'+tc+'">'+chNum+'</span>'+
              '<span class="dmx-val" style="color:'+tc+'">'+v+'</span>'+
            '</div>';
        }
        grid.innerHTML = html;

        /* ── barras de status (canais 1-3) ── */
        if(d.s1 !== undefined){
          document.getElementById('ch1-val').textContent = d.s1;
          document.getElementById('ch1-bar').style.width = Math.round(d.s1/255*100)+'%';
          document.getElementById('ch2-val').textContent = d.s2;
          document.getElementById('ch2-bar').style.width = Math.round(d.s2/255*100)+'%';
          document.getElementById('ch3-val').textContent = d.s3;
          document.getElementById('ch3-bar').style.width = Math.round(d.s3/255*100)+'%';
        }


      })
      .catch(function(e){ console.error("Erro no polling principal:", e); });
  }

  // ═══════════════════════════════════════
  //  MESA DE CONTROLE DMX
  // ═══════════════════════════════════════
  function consoleRebuild(){
    var wrap = document.getElementById('faders-wrap');
    var startCh = consoleGetStart();
    var html = '';
    for(var i=0; i<16; i++){
      var ch = startCh + i;
      html += `
        <div class="fader-col">
          <div class="fader-ch-lbl">${ch}</div>
          <div class="fader-track" id="fader-track-${i}"
              onmousedown="faderMouseDown(event, ${i})"
              ontouchstart="faderTouchStart(event, ${i})"
              onwheel="faderWheel(event, ${i})">
            <div class="fader-fill" id="fader-fill-${i}"></div>
            <div class="fader-thumb" id="fader-thumb-${i}"></div>
          </div>
          <div class="fader-val-lbl" id="fader-val-${i}">0</div>
        </div>
      `;
    }
    wrap.innerHTML = html;
    // Atualiza os valores dos faders recém-criados
    for(var i=0; i<16; i++){
      faderSetValue(i, conValues[i]);
    }
  }

  function consoleGetStart(){
    var input = document.getElementById('con-start');
    var start = parseInt(input.value);
    if(isNaN(start) || start < 1) start = 1;
    if(start > 497) start = 497; // 512 - 16 + 1
    input.value = start;
    return start;
  }

  function faderSetValue(idx, val){
    val = Math.max(0, Math.min(255, val));
    conValues[idx] = val;

    var fill  = document.getElementById('fader-fill-'+idx);
    var thumb = document.getElementById('fader-thumb-'+idx);
    var lbl   = document.getElementById('fader-val-'+idx);

    if(fill)  fill.style.height  = (val/255 * 100) + '%';
    if(thumb) thumb.style.bottom = (val/255 * 160 - 7) + 'px'; // 160px altura da track, 14px altura do thumb / 2 = 7
    if(lbl)   lbl.textContent    = val;
  }

  function faderSend(idx){
    var startCh = consoleGetStart();
    var ch = startCh + idx;
    var val = conValues[idx];
    fetch(`/dmx-set?ch=${ch}&val=${val}`).catch(e => console.error("Erro ao enviar DMX:", e));
  }

  function consoleFill(value){
    for(var i=0; i<16; i++){
      faderSetValue(i, value);
    }
    // Envia todos os 16 faders de uma vez
    var startCh = consoleGetStart();
    var params = '';
    for(var i=0; i<16; i++){
      params += `&ch${startCh+i}=${conValues[i]}`;
    }
    fetch(`/dmx-set-bulk?${params.substring(1)}`).catch(e => console.error("Erro ao enviar DMX bulk:", e));
  }
  
  // -- NOVO: Função para preencher os faders com valores aleatórios --
  function consoleRandom(){
    for(var i=0; i<16; i++){
      // Gera um valor aleatório entre 0 e 255
      var randomVal = Math.floor(Math.random() * 256);
      faderSetValue(i, randomVal);
    }
    // Envia todos os 16 faders de uma vez (estático, não em loop)
    var startCh = consoleGetStart();
    var params = '';
    for(var i=0; i<16; i++){
      params += `&ch${startCh+i}=${conValues[i]}`;
    }
    fetch(`/dmx-set-bulk?${params.substring(1)}`).catch(e => console.error("Erro ao enviar DMX bulk (random):", e));
  }

  /* Mouse */
  function faderMouseDown(e, idx){
    e.preventDefault();
    conDragging    = idx;
    conDragStartY  = e.clientY;
    conDragStartVal= conValues[idx];
    document.addEventListener('mousemove', faderMouseMove);
    document.addEventListener('mouseup',   faderMouseUp);
  }
  function faderMouseMove(e){
    if(conDragging < 0) return;
    var delta = Math.round((conDragStartY - e.clientY) / 160 * 255);
    faderSetValue(conDragging, conDragStartVal + delta);
    faderSend(conDragging); // Envia o valor DMX em tempo real
  }
  function faderMouseUp(){
    if(conDragging >= 0){
      // faderSend(conDragging); // Já enviado em faderMouseMove
      conDragging = -1;
    }
    document.removeEventListener('mousemove', faderMouseMove);
    document.removeEventListener('mouseup',   faderMouseUp);
  }

  /* Touch */
  function faderTouchStart(e, idx){
    e.preventDefault();
    conDragging    = idx;
    conDragStartY  = e.touches[0].clientY;
    conDragStartVal= conValues[idx];
    document.addEventListener('touchmove', faderTouchMove);
    document.addEventListener('touchend',  faderTouchEnd);
  }
  function faderTouchMove(e){
    if(conDragging < 0) return;
    var delta = Math.round((conDragStartY - e.touches[0].clientY) / 160 * 255);
    faderSetValue(conDragging, conDragStartVal + delta);
    faderSend(conDragging); // Envia o valor DMX em tempo real
  }
  function faderTouchEnd(){
    if(conDragging >= 0){
      // faderSend(conDragging); // Já enviado em faderTouchMove
      conDragging = -1;
    }
    document.removeEventListener('touchmove', faderTouchMove);
    document.removeEventListener('touchend',  faderTouchEnd);
  }

  /* Wheel */
  function faderWheel(e, idx){
    e.preventDefault();
    var delta = e.deltaY > 0 ? -5 : 5; // Scroll down = -5, scroll up = +5
    faderSetValue(idx, conValues[idx] + delta);
    faderSend(idx); // Envia o valor DMX em tempo real
  }

  // ═══════════════════════════════════════
  //  CONFIGURAÇÕES (aba Config)
  // ═══════════════════════════════════════
  function loadConfigValues(){
    // Carrega os valores atuais do dispositivo para os campos do formulário
    fetch('/config.json') // Pega dados ArtNet
      .then(r => r.json())
      .then(d => {
        // ArtNet
        document.querySelector('input[name="net"]').value = d.net;
        document.querySelector('input[name="subnet"]').value = d.sub;
        document.querySelector('input[name="universe"]').value = d.uni;
        // O campo de porta não existe no backend para ser configurado via POST, é fixo.
        // document.querySelector('input[name="port"]').value = d.port;

        // Os campos de Dispositivo e DMX Avançado não são carregados aqui
        // pois o backend atual não os persiste nem os retorna em /data ou /config.json.
        // Se forem implementados, esta função precisará ser expandida.
      })
      .catch(e => console.error("Erro ao carregar configurações ArtNet:", e));
  }


  // ═══════════════════════════════════════
  //  WIFI
  // ═══════════════════════════════════════
  function wifiStatusUpdate(){
    fetch('/wifi-status')
      .then(function(r){ return r.json(); })
      .then(function(d){
        _wifiApply('ws-status',     'ws-ssid',     'ws-ip',     'ws-rssi',     d);
        _wifiApply('cfg-ws-status', 'cfg-ws-ssid', 'cfg-ws-ip', 'cfg-ws-rssi', d);
        var hdrIp = document.getElementById('hdr-ip');
        if(hdrIp) hdrIp.innerHTML =
          'IP: <b>'+d.ip+'</b> ('+(d.connected?'STA':'AP')+')';
      })
      .catch(function(e){ console.error("Erro ao atualizar status WiFi:", e); });
  }

  function _wifiApply(sid, sssid, sip, srssi, d){
    var es  = document.getElementById(sid);
    if(!es) return;
    es.textContent = d.connected ? 'Conectado (STA)' : 'AP ativo';
    es.className   = 'vl '+(d.connected ? 'ok' : 'warn');
    var ess = document.getElementById(sssid);
    var eip = document.getElementById(sip);
    var er  = document.getElementById(srssi);
    if(ess) ess.textContent = d.ssid || '—';
    if(eip) eip.textContent = d.ip   || '—';
    if(er){
      if(d.connected){
        er.textContent = d.rssi+' dBm';
        er.className   = 'vl '+(d.rssi>-65?'ok':(d.rssi>-75?'warn':'err'));
      } else {
        er.textContent = '—'; er.className = 'vl';
      }
    }
  }

  function wifiScan(){
    var list = document.getElementById('wifi-list');
    var btn  = document.getElementById('wifi-scan-btn');
    list.innerHTML =
      "<div style='color:#6b7a8d;font-size:.8em;padding:6px 0'>Buscando redes...</div>";
    btn.disabled = true;
    fetch('/wifi-scan-start')
      .then(function(){ scanPollTimer = setInterval(pollScanResult, 1000); })
      .catch(function(e){ console.error("Erro ao iniciar scan WiFi:", e); btn.disabled = false; });
  }

  function pollScanResult(){
    fetch('/wifi-scan-result')
      .then(function(r){ return r.json(); })
      .then(function(d){
        if(d.status === 'scanning') return;
        clearInterval(scanPollTimer);
        document.getElementById('wifi-scan-btn').disabled = false;
        var list = document.getElementById('wifi-list');
        if(!d.nets || d.nets.length === 0){
          list.innerHTML =
            "<div style='color:#6b7a8d;font-size:.8em;padding:6px 0'>Nenhuma rede encontrada.</div>";
          return;
        }
        var bars = ['','▂','▂▄','▂▄▆','▂▄▆█'];
        var html = '';
        for(var i = 0; i < d.nets.length; i++){
          var n  = d.nets[i];
          var ss = n.ssid.replace(/\\/g,'\\\\').replace(/'/g,"\\'");
          html +=
            '<div class="wifi-item" onclick="wifiSelect(\''+ss+'\')">'+
            '<span>'+(n.secured?'🔒 ':'')+n.ssid+'</span>'+
            '<span class="wifi-bars">'+bars[n.strength]+' '+n.rssi+'dBm</span>'+
            '</div>';
        }
        list.innerHTML = html;
      })
      .catch(function(e){ console.error("Erro ao obter resultado do scan WiFi:", e); });
  }

  function wifiSelect(ssid){
    document.getElementById('wifi-ssid').value = ssid;
    document.getElementById('wifi-pass').value = '';
    document.getElementById('wifi-form-msg').textContent = '';
    var card = document.getElementById('wifi-form-card');
    card.style.display = 'block';
    card.scrollIntoView({behavior:'smooth'});
    setTimeout(function(){ document.getElementById('wifi-pass').focus(); }, 300);
  }

  function togglePass(){
    var i = document.getElementById('wifi-pass');
    i.type = i.type === 'password' ? 'text' : 'password';
  }

  function wifiConnect(){
    var ssid = document.getElementById('wifi-ssid').value.trim();
    var pass = document.getElementById('wifi-pass').value;
    var msg  = document.getElementById('wifi-form-msg');
    if(!ssid){ msg.textContent='SSID não pode ser vazio.'; msg.style.color='#ef5350'; return; }
    msg.textContent = 'Salvando e reiniciando...'; msg.style.color = '#9bd8ff';
    fetch('/wifi-connect',{
      method:'POST',
      headers:{'Content-Type':'application/x-www-form-urlencoded'},
      body:'ssid='+encodeURIComponent(ssid)+'&pass='+encodeURIComponent(pass)
    })
    .then(function(r){ return r.json(); })
    .then(function(d){
      if(d.ok) showReboot();
      else{ msg.textContent='Erro: '+(d.error||'desconhecido'); msg.style.color='#ef5350'; }
    })
    .catch(function(e){ console.error("Erro ao conectar WiFi:", e); msg.textContent='Erro de conexão.'; msg.style.color='#ef5350'; });
  }

  function wifiForget(){
    if(!confirm('Apagar credenciais WiFi?\nO dispositivo irá reiniciar em modo AP.')) return;
    fetch('/wifi-forget').then(function(){ showReboot(); }).catch(function(e){ console.error("Erro ao esquecer WiFi:", e); });
  }

    // ═══════════════════════════════════════
  //  OTA
  // ═══════════════════════════════════════

  // -- NOVO: Função para exibir mensagens de status da atualização online --
  function otaOnlineStatus(txt, cls){
    var el = document.getElementById('ota-online-status');
    el.textContent = txt;
    el.className   = 'ota-msg'+(cls?' '+cls:'');
    // REMOVA as linhas que escondem/desabilitam o botão aqui:
    // document.getElementById('ota-install-btn').style.display = 'none';
    // document.getElementById('ota-install-btn').disabled = true;
  }

  // -- NOVO: Função para carregar informações do firmware atual --
  function otaLoadInfo(){
    fetch('/firmware-info')
      .then(r => r.json())
      .then(d => {
        document.getElementById('fw-version').textContent = d.version;
        document.getElementById('fw-build-date').textContent = d.buildDate;
        currentFwVersion = d.version; // Armazena a versão atual globalmente
      })
      .catch(e => {
        console.error("Erro ao carregar informações do firmware:", e);
        document.getElementById('fw-version').textContent = 'Erro';
        document.getElementById('fw-build-date').textContent = 'Erro';
      });
  }

  // -- NOVO: Função para verificar por atualizações online --
  function otaCheckForUpdate(){
    otaOnlineStatus('Verificando por atualizações...', 'info');
    document.getElementById('ota-check-btn').disabled = true;
    // Garante que o botão de instalar está escondido e desabilitado ANTES de verificar
    document.getElementById('ota-install-btn').style.display = 'none';
    document.getElementById('ota-install-btn').disabled = true;

    latestFwUrl = '';
    latestFwVersion = '';

    fetch('/ota-check')
      .then(r => r.json())
      .then(d => {
        document.getElementById('ota-check-btn').disabled = false;
        if(d.error){
          otaOnlineStatus('Erro ao verificar: ' + d.error, 'err');
          return;
        }
        if(d.latestVersion && d.latestUrl){
          latestFwVersion = d.latestVersion;
          latestFwUrl = d.latestUrl;

          if (compareVersions(currentFwVersion, latestFwVersion) < 0) {
            document.getElementById('ota-new-version').textContent = latestFwVersion;
            document.getElementById('ota-install-btn').style.display = 'inline-block'; // MOSTRA o botão
            document.getElementById('ota-install-btn').disabled = false; // HABILITA o botão
            otaOnlineStatus('Nova versão disponível: v' + latestFwVersion, 'ok');
          } else {
            otaOnlineStatus('Seu firmware está atualizado (v' + currentFwVersion + ').', 'info');
            // O botão permanece escondido/desabilitado, o que é o comportamento desejado
          }
        } else {
          otaOnlineStatus('Nenhuma atualização encontrada.', 'info');
          // O botão permanece escondido/desabilitado
        }
      })
      .catch(e => {
        console.error("Erro ao verificar atualizações online:", e);
        otaOnlineStatus('Erro de conexão ao verificar atualizações.', 'err');
        document.getElementById('ota-check-btn').disabled = false;
        // O botão permanece escondido/desabilitado
      });
  }

  // -- NOVO: Função para comparar versões (simplificada) --
  function compareVersions(v1, v2) {
      // Remove 'v' prefixo se existir
      v1 = v1.startsWith('v') ? v1.substring(1) : v1;
      v2 = v2.startsWith('v') ? v2.substring(1) : v2;

      const parts1 = v1.split('.').map(Number);
      const parts2 = v2.split('.').map(Number);

      for (let i = 0; i < Math.max(parts1.length, parts2.length); i++) {
          const p1 = parts1[i] || 0;
          const p2 = parts2[i] || 0;

          if (p1 < p2) return -1; // v1 é menor
          if (p1 > p2) return 1;  // v1 é maior
      }
      return 0; // Versões são iguais
  }


  // -- NOVO: Função para iniciar a atualização online --
  function otaInstallUpdate(){
    if(!latestFwUrl){
      otaOnlineStatus('Nenhuma atualização disponível para instalar.', 'err');
      return;
    }
    if(!confirm(
      'Tem certeza que deseja instalar a atualização v' + latestFwVersion + '?\n\n'+
      'O equipamento será reiniciado automaticamente.\n'+
      'Não desligue a energia durante o processo.')) return;

    otaOnlineStatus('Iniciando atualização online...', 'info');
    document.getElementById('ota-check-btn').disabled = true;
    document.getElementById('ota-install-btn').disabled = true;
    document.getElementById('ota-install-btn').style.display = 'none';

    fetch('/ota-install-online', {
      method: 'POST',
      headers: {'Content-Type': 'application/x-www-form-urlencoded'},
      body: 'url=' + encodeURIComponent(latestFwUrl)
    })
    .then(r => r.json())
    .then(d => {
      if(d.ok){
        otaOnlineStatus('Atualização iniciada! O dispositivo está reiniciando...', 'ok');
        showReboot();
      } else {
        otaOnlineStatus('Falha ao iniciar atualização: ' + (d.error || 'desconhecido'), 'err');
        document.getElementById('ota-check-btn').disabled = false;
      }
    })
    .catch(e => {
      console.error("Erro ao iniciar atualização online:", e);
      otaOnlineStatus('Erro de conexão ao iniciar atualização.', 'err');
      document.getElementById('ota-check-btn').disabled = false;
    });
  }

  // As funções otaInit, otaSelectFile, otaMsg, otaUpload permanecem as mesmas
  // ou com pequenas modificações para usar otaMsg() em vez de otaOnlineStatus()
  // para a aba de upload manual.

  function otaInit(){
    var dz  = document.getElementById('ota-dz');
    var inp = document.getElementById('ota-input');
    if(!dz || !inp) return;
    dz.addEventListener('dragover',  function(e){ e.preventDefault(); dz.classList.add('dragover'); });
    dz.addEventListener('dragleave', function(){  dz.classList.remove('dragover'); });
    dz.addEventListener('drop', function(e){
      e.preventDefault(); dz.classList.remove('dragover');
      var f = e.dataTransfer.files[0]; if(f) otaSelectFile(f);
    });
    inp.addEventListener('change', function(){ if(inp.files[0]) otaSelectFile(inp.files[0]); });
  }

  function otaSelectFile(f){
    otaFile = null; otaMsg('',''); // Usa otaMsg para a aba manual
    var fn = document.getElementById('ota-fname');
    if(!f.name.toLowerCase().endsWith('.bin')){
      otaMsg('Arquivo inválido. Selecione um arquivo .bin.','err');
      fn.textContent = 'Nenhum arquivo selecionado'; return;
    }
    if(f.size < 1024)   { otaMsg('Arquivo muito pequeno (< 1 KB).','err'); return; }
    if(f.size > 1048576){ otaMsg('Arquivo muito grande (> 1 MB).','err');  return; } // Limite de 1MB para ESP8266
    otaFile = f;
    fn.textContent = f.name+' ('+Math.round(f.size/1024)+' KB)';
    document.getElementById('ota-btn').disabled = false;
    otaMsg('Arquivo validado. Clique em "Enviar Firmware" para iniciar.','info');
  }

  function otaMsg(txt, cls){ // Esta função é para a aba de upload manual
    var el = document.getElementById('ota-msg');
    el.textContent = txt;
    el.className   = 'ota-msg'+(cls?' '+cls:'');
  }

  function otaUpload(){
    if(!otaFile){ otaMsg('Selecione um arquivo .bin primeiro.','err'); return; }
    if(!confirm(
      'Tem certeza que deseja atualizar o firmware?\n\n'+
      'O equipamento será reiniciado automaticamente.\n'+
      'Não desligue a energia durante o processo.')) return;
    var btn  = document.getElementById('ota-btn');
    var wrap = document.getElementById('ota-prog-wrap');
    var bar  = document.getElementById('ota-prog-bar');
    btn.disabled = true;
    wrap.style.display = 'block';
    bar.style.width = '0%'; bar.textContent = '0%'; bar.style.background = '#0069b4';
    otaMsg('Enviando firmware... não desligue o equipamento.','info');
    var xhr = new XMLHttpRequest();
    xhr.open('POST','/ota-update',true);
    xhr.upload.onprogress = function(e){
      if(e.lengthComputable){
        var pct = Math.round(e.loaded/e.total*100);
        bar.style.width = pct+'%'; bar.textContent = pct+'%';
      }
    };
    xhr.onload = function(){
      if(xhr.status === 200){
        bar.style.width = '100%'; bar.textContent = '100%'; bar.style.background = '#4caf50';
        otaMsg('Firmware enviado! O dispositivo está reiniciando...','ok');
        showReboot();
      } else {
        bar.style.background = '#ef5350';
        otaMsg('Falha (HTTP '+xhr.status+'): '+xhr.responseText,'err');
        btn.disabled = false;
      }
    };
    xhr.onerror   = function(){ otaMsg('Erro de conexão.','err');  btn.disabled = false; };
    xhr.ontimeout = function(){ otaMsg('Timeout.','err');           btn.disabled = false; };
    xhr.timeout   = 60000;
    var fd = new FormData();
    fd.append('firmware', otaFile, otaFile.name);
    xhr.send(fd);
  }

  // ═══════════════════════════════════════
  //  REBOOT OVERLAY
  // ═══════════════════════════════════════
  function showReboot(){
    var ov = document.getElementById('reboot-overlay');
    var cd = document.getElementById('reboot-cd');
    ov.style.display = 'flex';
    var secs = 15; cd.textContent = secs;
    var iv = setInterval(function(){
      secs--; cd.textContent = secs;
      if(secs <= 0){
        clearInterval(iv); cd.textContent = 'Reconectando...';
        var tries = 0;
        var retry = setInterval(function(){
          tries++;
          fetch('/').then(function(){
            clearInterval(retry); window.location.href = '/';
          }).catch(function(){
            if(tries > 20){ clearInterval(retry); cd.textContent = 'Recarregue manualmente.'; }
          });
        }, 1500);
      }
    }, 1000);
  }

  document.addEventListener('DOMContentLoaded', otaInit);
</script>
</body>
</html>
)HTML";
#endif // WEB_UI_H