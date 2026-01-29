const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
    :root {
        --bg-paper: #d2c5b3;
        --tag-brown: #9b7653;
        --sketch-black: #1a1a1a;
        --mumei-white: #ffffff;
    }

    body { 
        background-color: var(--bg-paper); 
        color: var(--sketch-black);
        font-family: "Comic Relief", "Comic Sans MS", cursive;
        margin: 0; padding: 15px;
        background-image: radial-gradient(#b5a896 1px, transparent 1px);
        background-size: 20px 20px;
    }

    /* Tab Bar theo kiểu thẻ tag đính kèm */
    .tab-bar {
        display: flex;
        justify-content: space-around;
        margin-bottom: -5px; /* Ép sát vào card bên dưới */
        z-index: 10;
        position: relative;
    }

    .tab-item {
        background: var(--tag-brown);
        color: white;
        padding: 8px 15px;
        border: 3px solid var(--sketch-black);
        border-bottom: none;
        border-radius: 15px 15px 0 0;
        cursor: pointer;
        font-size: 13px;
        font-weight: bold;
        transform: translateY(5px);
        transition: 0.2s;
    }

    .tab-item.active {
        background: var(--mumei-white);
        color: var(--sketch-black);
        transform: translateY(0px);
        padding-top: 12px;
    }

    .sketch-card {
        background: var(--mumei-white);
        border: 4px solid var(--sketch-black);
        border-radius: 0 0 35px 35px; /* Chỉ bo góc dưới */
        padding: 20px;
        min-height: 250px;
        box-shadow: 8px 8px 0px var(--tag-brown);
    }

    /* Nội dung các tab */
    .tab-content { display: none; }
    .tab-content.active { display: block; animation: fadeIn 0.3s; }

    @keyframes fadeIn { from { opacity: 0; } to { opacity: 1; } }

    /* List SSID kiểu sketch */
    .ssid-list { text-align: left; margin-top: 10px; }
    .ssid-item {
        border-bottom: 2px dashed #ccc;
        padding: 10px;
        display: flex;
        justify-content: space-between;
    }

    .btn {
        width: 100%;
        background: var(--mumei-white);
        border: 3px solid var(--sketch-black);
        padding: 15px;
        margin: 10px 0;
        border-radius: 20px;
        font-family: inherit;
        font-weight: bold;
        cursor: pointer;
        box-shadow: 4px 4px 0px var(--sketch-black);
    }

    .btn:active { transform: translate(2px, 2px); box-shadow: none; }
    
    #console {
        margin-top: 20px;
        background: rgba(255,255,255,0.4);
        border: 2px dashed var(--sketch-black);
        height: 80px; padding: 10px; font-size: 11px;
        overflow-y: auto; border-radius: 15px;
    }
</style>
</head>
<body>

<div class="tab-bar">
    <div class="tab-item active" onclick="openTab(event, 'tab-ssid')">SSID</div>
    <div class="tab-item" onclick="openTab(event, 'tab-deauth')">DEAUTH</div>
    <div class="tab-item" onclick="openTab(event, 'tab-attack')">ATTACK</div>
</div>

<div class="sketch-card">
    <div id="tab-ssid" class="tab-content active">
        <button class="btn" onclick="api('scan')">✎ SCAN NETWORKS</button>
        <div class="ssid-list">
            <div class="ssid-item"><span>Target_01</span> <span>-65dBm</span></div>
            <div class="ssid-item"><span>Target_02</span> <span>-72dBm</span></div>
        </div>
    </div>

    <div id="tab-deauth" class="tab-content">
        <h3 style="text-align:center">SETTINGS</h3>
        <label><input type="checkbox" checked disabled> AUTOSAVE ENABLED</label><br><br>
        <button class="btn" onclick="api('fan')">🌀 TOGGLE FAN</button>
        <p style="font-size: 12px; color: #666;">*AutoSave sẽ tự động thực hiện mỗi khi toggle.</p>
    </div>

    <div id="tab-attack" class="tab-content">
        <div style="text-align:center; padding: 20px;">
            <div style="font-size: 40px;">☠</div>
            <p>WARNING: Civilized mode is OFF</p>
            <button class="btn" style="color:red; border-color:red" onclick="api('attack')">EXECUTE ATTACK</button>
        </div>
    </div>
</div>

<div id="console">
    <div>> Initializing Tabs...</div>
</div>

<script>
    function openTab(evt, tabId) {
        var i, content, tabs;
        content = document.getElementsByClassName("tab-content");
        for (i = 0; i < content.length; i++) { content[i].classList.remove("active"); }
        tabs = document.getElementsByClassName("tab-item");
        for (i = 0; i < tabs.length; i++) { tabs[i].classList.remove("active"); }
        document.getElementById(tabId).classList.add("active");
        evt.currentTarget.classList.add("active");
        addLog("Switched to " + tabId.replace('tab-', '').toUpperCase());
    }

    function addLog(m) {
        const c = document.getElementById('console');
        c.innerHTML += `<div>> ${m}</div>`;
        c.scrollTop = c.scrollHeight;
    }

    function api(cmd) {
        addLog("Executing: " + cmd);
        if(cmd === 'attack') {
            document.body.style.backgroundColor = '#f4d3d3';
            setTimeout(()=>document.body.style.backgroundColor = '#d2c5b3', 500);
        }
        // Giả lập AutoSave
        setTimeout(() => addLog("AutoSave: Memory updated."), 600);
    }
</script>

</body>
</html>
)=====";
