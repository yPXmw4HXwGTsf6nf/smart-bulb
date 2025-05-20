const host = location.hash.slice(1) || 'bulb.local:8080';
const q = p => fetch(`http://${host}${p}`).catch(()=>{});
document.getElementById('on').onclick = ()=>q('/api/on');
document.getElementById('off').onclick = ()=>q('/api/off');
document.getElementById('br').oninput = e=>q('/api/brightness?v='+e.target.value);
const status = document.getElementById('status');
setInterval(()=>q('/').then(r=>status.textContent='online').catch(()=>status.textContent='offline'),3000);
