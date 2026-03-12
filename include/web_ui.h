#ifndef WEB_UI_H
#define WEB_UI_H

#include <pgmspace.h>

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
              font-size:.78em;color:#fff;font-weight:bold}
    .btn-mini.full{background:#2e7d32}
    .btn-mini.half{background:#e65100}
    .btn-mini.zero{background:#37474f}
    .btn-mini:hover{filter:brightness(1.2)}

    .faders-wrap{display:flex;gap:6px;overflow-x:auto;padding-bottom:8px}
    .fader-col{display:flex;flex-direction:column;align-items:center;
               gap:5px;min-width:42px;flex-shrink:0}
    .fader-ch-lbl{font-size:.62em;color:#6b7a8d;font-weight:bold;text-align:center}
    .fader-val-lbl{font-size:.68em;color:#00a4ff;font-weight:bold;
                   text-align:center;min-width:28px}
    .fader-track{position:relative;width:26px;height:160px;
                 background:#111820;border-radius:13px;
                 border:1px solid #1b2431;cursor:pointer;touch-action:none}
    .fader-fill{position:absolute;bottom:0;left:0;right:0;
                border-radius:13px;background:linear-gradient(0deg,#006b30,#00e676);
                transition:height .08s}
    .fader-thumb{position:absolute;left:50%;transform:translateX(-50%);
                 width:22px;height:14px;border-radius:7px;
                 background:#e9edf2;box-shadow:0 1px 4px rgba(0,0,0,.6);
                 cursor:grab;transition:bottom .08s}
    .fader-thumb:active{cursor:grabbing}

    /* ── WIFI LIST ── */
    .wifi-item{display:flex;justify-content:space-between;align-items:center;
               padding:8px 7px;border-radius:6px;border:1px solid #1b2431;
               margin-bottom:6px;font-size:.82em;cursor:pointer;transition:background .15s}
    .wifi-item:hover{background:#111820}
    .wifi-bars{color:#9bd8ff;font-size:.8em;white-space:nowrap}

    /* ── FORMS ── */
    .lbl{font-size:.7em;color:#6b7a8d;margin-bottom:3px}
    input[type=number],input[type=text],input[type=password],select{
      width:100%;padding:6px 8px;border-radius:4px;border:1px solid #1b2431;
      background:#080c10;color:#e9edf2;font-size:.88em}
    .btn{display:block;width:100%;padding:9px;border:none;border-radius:5px;
         cursor:pointer;font-size:.86em;margin-top:8px;color:#fff;
         background:#0069b4;text-align:center}
    .btn:hover{filter:brightness(1.15)}
    .btn:disabled{background:#2a3545;color:#555;cursor:not-allowed}
    .btn-alt   {background:#222c3a}
    .btn-danger{background:#b71c1c}
    .btn-ok    {background:#2e7d32}
    .btn-warn  {background:#e65100}
    .btn-soft  {background:#0d1a2a;border:1px solid #1b3355}
    .grid2{display:grid;grid-template-columns:1fr 1fr;gap:10px}
    .grid3{display:grid;grid-template-columns:1fr 1fr 1fr;gap:10px}

    /* ── OTA ── */
    .ota-steps{list-style:none;padding:0;margin:0;counter-reset:step}
    .ota-steps li{counter-increment:step;padding:5px 0 5px 28px;position:relative;
                  font-size:.83em;color:#b0bec5}
    .ota-steps li::before{content:counter(step);position:absolute;left:0;top:4px;
                          width:19px;height:19px;border-radius:50%;background:#101e2d;
                          color:#00a4ff;display:flex;align-items:center;
                          justify-content:center;font-size:.72em;font-weight:bold}
    .ota-dropzone{border:2px dashed #1b2431;border-radius:8px;padding:22px 12px;
                  text-align:center;cursor:pointer;background:#080c10;
                  position:relative;font-size:.84em}
    .ota-dropzone.dragover{border-color:#00a4ff;background:#0a1825}
    .ota-dropzone input[type=file]{position:absolute;inset:0;opacity:0;
                                   cursor:pointer;width:100%}
    .ota-icon{font-size:1.8em;display:block;margin-bottom:5px;color:#00a4ff}
    .ota-filename{font-size:.78em;color:#00a4ff;margin-top:5px;
                  min-height:1.1em;word-break:break-all}
    .prog-wrap{background:#080c10;border-radius:4px;height:18px;
               overflow:hidden;margin-top:10px;display:none}
    .prog-bar{height:100%;width:0%;background:#0069b4;border-radius:4px;
              display:flex;align-items:center;justify-content:center;
              font-size:.7em;font-weight:bold;transition:width .3s}
    .ota-msg{text-align:center;font-size:.82em;margin-top:7px;
             min-height:1.3em;padding:6px;border-radius:4px;display:none}
    .ota-msg.ok  {display:block;background:#0d2418;color:#4caf50}
    .ota-msg.err {display:block;background:#2d0e0e;color:#ef5350}
    .ota-msg.info{display:block;background:#0a1825;color:#9bd8ff}

    /* ── REBOOT OVERLAY ── */
    .reboot-overlay{position:fixed;inset:0;background:rgba(0,0,0,.88);
                    display:none;align-items:center;justify-content:center;
                    z-index:999;flex-direction:column}
    .reboot-box{background:#0d1219;border-radius:12px;padding:26px 20px;
                text-align:center;max-width:310px;border:1px solid #1b2431}
    .spinner{width:38px;height:38px;border:4px solid #111820;border-top-color:#0069b4;
             border-radius:50%;animation:spin 1s linear infinite;margin:12px auto}
    @keyframes spin{to{transform:rotate(360deg)}}

    /* ── SECTION DIVIDER ── */
    .section-title{font-size:.75em;font-weight:bold;color:#4a6080;
                   text-transform:uppercase;letter-spacing:.07em;
                   margin:16px 0 8px;padding-bottom:5px;border-bottom:1px solid #141b24}

    @media(max-width:560px){
      .header{flex-direction:column;align-items:flex-start}
      .header-right{text-align:left}
      .dash-metrics{grid-template-columns:repeat(2,1fr)}
      .grid2,.grid3{grid-template-columns:1fr}
      .console-globals{margin-left:0}
    }
  </style>
</head>
<body>
<div class="page">
  <header class="header">
    <div class="brand">
      <div class="brand-logo">
        <img src="/logo_3.png" alt="ONEBit">
      </div>
      <div>
        <div class="brand-main">ONEBit Engenharia</div>
        <div class="brand-sub">Interface ArtNet & DMX</div>
      </div>
    </div>
    <div class="header-right">
      <div>ONEBit Core &nbsp;<span id="dot"></span></div>
      <div id="hdr-ip">IP: <b>—</b></div>
      <div id="hdr-artnet">Net:<b>0</b> Sub:<b>0</b> Uni:<b>0</b> &nbsp;|&nbsp; UDP:<b>6454</b></div>
    </div>
  </header>
)HTML";


// ─────────────────────────────────────────────────────────────
// BODY
// ─────────────────────────────────────────────────────────────
static const char HTML_BODY[] PROGMEM = R"HTML(
  <!-- ══ TABS ══ -->
  <div class="tabs">
    <div class="tab" data-tab="status" onclick="showTab('status')">&#9679; Status</div>
    <div class="tab" data-tab="canais" onclick="showTab('canais')">&#9636; Canais</div>
    <div class="tab" data-tab="config" onclick="showTab('config')">&#9881; Config</div>
    <div class="tab" data-tab="ota"    onclick="showTab('ota')"   >&#8679; Firmware</div>
  </div>

  <!-- ══════════════════════════════════════════
       PANE: STATUS + MESA DE CONTROLE
  ══════════════════════════════════════════ -->
  <section id="pane-status" class="pane">

    <!-- Recepção ArtNet -->
    <div class="card">
      <h2>Recepção ArtNet</h2>
      <div style="display:flex;align-items:flex-start;gap:12px;flex-wrap:wrap">
        <div>
          <div style="font-size:.78em;color:#8a9bb0;margin-bottom:6px">Estado do stream</div>
          <div id="rx-badge" class="status-badge err">
            <span class="badge-dot"></span>Aguardando
          </div>
        </div>
        <div class="dash-metrics" style="flex:1;margin-bottom:0">
          <div class="metric">
            <div class="metric-label">Último pacote</div>
            <div class="metric-value" id="m-ago">—</div>
            <div class="metric-unit">atrás</div>
          </div>
          <div class="metric">
            <div class="metric-label">Aceitos</div>
            <div class="metric-value ok" id="m-ok">0</div>
            <div class="metric-unit">pacotes</div>
          </div>
          <div class="metric">
            <div class="metric-label">Filtrados</div>
            <div class="metric-value warn" id="m-filt">0</div>
            <div class="metric-unit">pacotes</div>
          </div>
          <div class="metric">
            <div class="metric-label">Intervalo</div>
            <div class="metric-value" id="m-interval">—</div>
            <div class="metric-unit">reenvio</div>
          </div>
        </div>
      </div>
      <div style="margin-top:14px">
        <div class="lbl" style="margin-bottom:6px">Nível — Canais 1 / 2 / 3</div>
        <div class="ch-bars">
          <div class="ch-bar-item">
            <div class="ch-bar-label"><span>Ch 1</span><span id="bar-val-1">0</span></div>
            <div class="ch-bar-track"><div class="ch-bar-fill" id="bar-fill-1" style="width:0%"></div></div>
          </div>
          <div class="ch-bar-item">
            <div class="ch-bar-label"><span>Ch 2</span><span id="bar-val-2">0</span></div>
            <div class="ch-bar-track"><div class="ch-bar-fill" id="bar-fill-2" style="width:0%"></div></div>
          </div>
          <div class="ch-bar-item">
            <div class="ch-bar-label"><span>Ch 3</span><span id="bar-val-3">0</span></div>
            <div class="ch-bar-track"><div class="ch-bar-fill" id="bar-fill-3" style="width:0%"></div></div>
          </div>
        </div>
      </div>
    </div>

    <!-- Rede & Dispositivo -->
    <div class="card">
      <h2>Rede & Dispositivo</h2>
      <div class="info-row">
        <span class="lk">Status WiFi</span>
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
      <div class="info-row">
        <span class="lk">ArtNet — Net / Sub / Uni</span>
        <span id="st-artnet" class="vl">—</span>
      </div>
      <div class="info-row">
        <span class="lk">Porta UDP</span>
        <span class="vl">6454</span>
      </div>
    </div>

    <!-- Mesa de Controle DMX -->
    <div class="card">
      <h2>&#127914; Mesa de Controle DMX</h2>
      <div class="console-top">
        <div>
          <div class="lbl">Canal inicial (1–497)</div>
          <input class="console-ch-input" type="number" id="con-start"
                 min="1" max="497" value="1" oninput="consoleRebuild()">
        </div>
        <div class="console-globals">
          <button class="btn-mini full" onclick="consoleFill(255)">FULL</button>
          <button class="btn-mini half" onclick="consoleFill(128)">HALF</button>
          <button class="btn-mini zero" onclick="consoleFill(0)">ZERO</button>
        </div>
      </div>
      <div class="faders-wrap" id="faders-wrap"></div>
      <div style="margin-top:12px;font-size:.72em;color:#4a6080;text-align:center">
        Scroll / drag / touch nos faders &nbsp;·&nbsp; Cada fader envia DMX ao soltar
      </div>
    </div>

  </section>

  <!-- ══════════════════════════════════════════
       PANE: CANAIS — selecionar universo
  ══════════════════════════════════════════ -->
  <section id="pane-canais" class="pane">
    <div class="card">
      <h2 id="card-ch-title">Canais DMX — Universo 0</h2>

      <!-- Seletor de universo -->
      <div class="uni-selector">
        <span class="lbl">Universo&nbsp;(0–15):</span>
        <div class="uni-tabs" id="uni-tabs">
          <!-- gerado pelo JS -->
        </div>
      </div>

      <div class="uni-info" id="uni-info">
        Exibindo canais 1–512 &nbsp;·&nbsp; Universo 0
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

        <div class="section-title" style="margin-top:16px">DMX avançado</div>
        <div class="grid2">
          <div>
            <div class="lbl">Intervalo de reenvio (ms, 0=MAX)</div>
            <input type="number" name="dmx_interval" min="0" max="10000" value="0">
          </div>
          <div>
            <div class="lbl">Timeout sem pacote (s)</div>
            <input type="number" name="dmx_timeout" min="1" max="300" value="10">
          </div>
        </div>

        <div class="section-title">Failsafe / Hold</div>
        <div class="grid2">
          <div>
            <div class="lbl">Ao perder sinal</div>
            <select name="failsafe">
              <option value="0">Manter último frame</option>
              <option value="1">Zerar saída (blackout)</option>
            </select>
          </div>
          <div style="display:flex;align-items:flex-end;padding-bottom:2px">
            <label style="display:flex;align-items:center;gap:8px;font-size:.83em;cursor:pointer">
              <input type="checkbox" name="hold" value="1" style="width:auto">
              Hold: travar no último frame
            </label>
          </div>
        </div>

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
          <div class="lbl">Senha</div>
          <div style="position:relative">
            <input type="password" id="wifi-pass" style="padding-right:32px">
            <span onclick="togglePass()"
                  style="position:absolute;right:9px;top:7px;cursor:pointer;
                         font-size:1.05em;user-select:none">&#128065;</span>
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
      <h2>Como atualizar o firmware</h2>
      <ol class="ota-steps">
        <li>No PlatformIO, compile o projeto.
            O arquivo <code>firmware.bin</code> fica em
            <code>.pio/build/nodemcuv2/</code>.</li>
        <li>Clique na área abaixo ou arraste o arquivo <code>.bin</code>.</li>
        <li>Clique em <b>Enviar Firmware</b> e aguarde a barra chegar a 100%.</li>
        <li>O dispositivo reiniciará automaticamente.</li>
        <li>Não desligue a energia durante o processo.</li>
      </ol>
    </div>

    <div class="card">
      <h2>Upload do Firmware</h2>
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

    <div class="card" style="border-color:#3d2600">
      <h2 style="color:#ffb74d">&#9888; Avisos importantes</h2>
      <ul style="font-size:.82em;color:#b0bec5;padding-left:18px;line-height:1.7;margin-top:4px">
        <li>Use somente firmwares gerados para este equipamento.</li>
        <li>Um firmware incorreto pode exigir reprogramação via USB.</li>
        <li>Mantenha a energia estável durante todo o processo.</li>
        <li>Não feche esta aba enquanto o upload estiver em andamento.</li>
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
  if(id==='config') wifiStatusUpdate();
}

// ═══════════════════════════════════════
//  BOOT
// ═══════════════════════════════════════
var updTimer   = null;
var scanPollTimer = null;
var otaFile    = null;
var selUni     = 0;   // universo selecionado na aba Canais (0–15)

document.addEventListener('DOMContentLoaded', function(){
  var t = 'status';
  try{ t = localStorage.getItem('tab') || 'status'; }catch(e){}

  uniTabsBuild();   // monta os botões de universo
  showTab(t);
  consoleRebuild();
  wifiStatusUpdate();
  setInterval(wifiStatusUpdate, 10000);
  setInterval(upd, 1000);
  otaInit();
});

// ═══════════════════════════════════════
//  SELETOR DE UNIVERSO (aba Canais)
// ═══════════════════════════════════════
function uniTabsBuild(){
  var wrap = document.getElementById('uni-tabs');
  var html = '';
  for(var u = 0; u < 16; u++){
    html +=
      '<div class="uni-tab'+(u===selUni?' active':'')+
      '" onclick="uniSelect('+u+')" id="ut-'+u+'">'+u+'</div>';
  }
  wrap.innerHTML = html;
}

function uniSelect(u){
  selUni = u;
  // atualiza visual dos botões
  for(var i = 0; i < 16; i++){
    var el = document.getElementById('ut-'+i);
    if(el) el.classList.toggle('active', i===u);
  }
  // atualiza título e info
  document.getElementById('card-ch-title').textContent =
    'Canais DMX — Universo ' + u;
  document.getElementById('uni-info').textContent =
    'Exibindo canais 1–512  ·  Universo ' + u;
  // força atualização imediata
  schedUpd();
}

// ═══════════════════════════════════════
//  POLLING PRINCIPAL
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
  // A aba Canais sempre pede os 512 canais do universo selecionado
  fetch('/data?uni='+selUni+'&start=1&count=512')
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

      /* ── barras ch 1/2/3 ── */
      ['1','2','3'].forEach(function(n,i){
        var v = [d.s1, d.s2, d.s3][i] || 0;
        document.getElementById('bar-fill-'+n).style.width = Math.round(v/255*100)+'%';
        document.getElementById('bar-val-'+n).textContent  = v;
      });

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

      /* ── grid 512 canais ── */
      var grid = document.getElementById('ch-grid');
      var html = '';
      var chArr  = d.ch     || [];
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

    })
    .catch(function(){});
}

// ═══════════════════════════════════════
//  MESA DE CONTROLE DMX
// ═══════════════════════════════════════
var conValues   = new Array(16).fill(0);
var conDragging = -1;
var conDragStartY   = 0;
var conDragStartVal = 0;

function consoleGetStart(){
  var s = parseInt(document.getElementById('con-start').value) || 1;
  if(s <   1) s =   1;
  if(s > 497) s = 497;
  return s;
}

function consoleRebuild(){
  var wrap  = document.getElementById('faders-wrap');
  var start = consoleGetStart();
  var html  = '';
  for(var i = 0; i < 16; i++){
    var ch  = start + i;
    var v   = conValues[i];
    var pct = Math.round(v/255*100);
    html +=
      '<div class="fader-col">'+
        '<div class="fader-ch-lbl">'+ch+'</div>'+
        '<div class="fader-track" data-idx="'+i+'" '+
             'onmousedown="faderMouseDown(event,'+i+')" '+
             'ontouchstart="faderTouchStart(event,'+i+')" '+
             'onwheel="faderWheel(event,'+i+')" >'+
          '<div class="fader-fill"  id="ff-'+i+'" style="height:'+pct+'%"></div>'+
          '<div class="fader-thumb" id="ft-'+i+'" style="bottom:calc('+pct+'% - 7px)"></div>'+
        '</div>'+
        '<div class="fader-val-lbl" id="fv-'+i+'">'+v+'</div>'+
      '</div>';
  }
  wrap.innerHTML = html;
}

function faderSetValue(idx, val){
  val = Math.max(0, Math.min(255, Math.round(val)));
  conValues[idx] = val;
  var pct = Math.round(val/255*100);
  var ff  = document.getElementById('ff-'+idx);
  var ft  = document.getElementById('ft-'+idx);
  var fv  = document.getElementById('fv-'+idx);
  if(ff) ff.style.height  = pct+'%';
  if(ft) ft.style.bottom  = 'calc('+pct+'% - 7px)';
  if(fv) fv.textContent   = val;
}

function faderSend(idx){
  var ch  = consoleGetStart() + idx;
  var val = conValues[idx];
  fetch('/dmx-set?ch='+ch+'&val='+val).catch(function(){});
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
}
function faderMouseUp(){
  if(conDragging >= 0){ faderSend(conDragging); conDragging = -1; }
  document.removeEventListener('mousemove', faderMouseMove);
  document.removeEventListener('mouseup',   faderMouseUp);
}

/* Touch */
function faderTouchStart(e, idx){
  e.preventDefault();
  conDragging    = idx;
  conDragStartY  = e.touches[0].clientY;
  conDragStartVal= conValues[idx];
  document.addEventListener('touchmove', faderTouchMove, {passive:false});
  document.addEventListener('touchend',  faderTouchEnd);
}
function faderTouchMove(e){
  e.preventDefault();
  if(conDragging < 0) return;
  var delta = Math.round((conDragStartY - e.touches[0].clientY) / 160 * 255);
  faderSetValue(conDragging, conDragStartVal + delta);
}
function faderTouchEnd(){
  if(conDragging >= 0){ faderSend(conDragging); conDragging = -1; }
  document.removeEventListener('touchmove', faderTouchMove);
  document.removeEventListener('touchend',  faderTouchEnd);
}

/* Scroll */
function faderWheel(e, idx){
  e.preventDefault();
  faderSetValue(idx, conValues[idx] + (e.deltaY < 0 ? 5 : -5));
  faderSend(idx);
}

/* Controles globais */
function consoleFill(val){
  for(var i = 0; i < 16; i++) faderSetValue(i, val);
  var start  = consoleGetStart();
  var params = '';
  for(var i = 0; i < 16; i++)
    params += '&ch'+(i+1)+'='+(start+i)+'&val'+(i+1)+'='+val;
  fetch('/dmx-set-bulk?n=16'+params).catch(function(){
    for(var i = 0; i < 16; i++) faderSend(i);
  });
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
    .catch(function(){});
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
    .catch(function(){ btn.disabled = false; });
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
          '<span>'+(n.secured?'&#128274; ':'')+n.ssid+'</span>'+
          '<span class="wifi-bars">'+bars[n.strength]+' '+n.rssi+'dBm</span>'+
          '</div>';
      }
      list.innerHTML = html;
    })
    .catch(function(){});
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
  .catch(function(){ msg.textContent='Erro de conexão.'; msg.style.color='#ef5350'; });
}

function wifiForget(){
  if(!confirm('Apagar credenciais WiFi?\nO dispositivo irá reiniciar em modo AP.')) return;
  fetch('/wifi-forget').then(function(){ showReboot(); }).catch(function(){});
}

// ═══════════════════════════════════════
//  OTA
// ═══════════════════════════════════════
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
  otaFile = null; otaMsg('','');
  var fn = document.getElementById('ota-fname');
  if(!f.name.toLowerCase().endsWith('.bin')){
    otaMsg('Arquivo inválido. Selecione um .bin gerado pelo PlatformIO.','err');
    fn.textContent = 'Nenhum arquivo selecionado'; return;
  }
  if(f.size < 1024)   { otaMsg('Arquivo muito pequeno (< 1 KB).','err'); return; }
  if(f.size > 1048576){ otaMsg('Arquivo muito grande (> 1 MB).','err');  return; }
  otaFile = f;
  fn.textContent = f.name+' ('+Math.round(f.size/1024)+' KB)';
  document.getElementById('ota-btn').disabled = false;
  otaMsg('Arquivo validado. Clique em "Enviar Firmware" para iniciar.','info');
}

function otaMsg(txt, cls){
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