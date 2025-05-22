// minimal front‑end helper for smart‑bulb controller

const $ = id => document.getElementById(id);

const host  = location.hash.slice(1) || 'bulb.local:8080';
const query = path => fetch(`http://${host}${path}`).catch(() => {});

$('on').onclick  = () => query('/api/on');
$('off').onclick = () => query('/api/off');
$('br').oninput  = e => query(`/api/brightness?v=${e.target.value}`);

const status = $('status');
setInterval(() => {
  query('/')
    .then(() => { status.textContent = 'online'; })
    .catch(() => { status.textContent = 'offline'; });
}, 3000);
