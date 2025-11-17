const canvas = document.getElementById('particles');
const ctx = canvas.getContext('2d');

let particlesArray;

const mouse = {
  x: null,
  y: null,
  radius: 150
};

window.addEventListener('mousemove', function(event) {
  mouse.x = event.x;
  mouse.y = event.y;
});

function init() {
  particlesArray = [];
  const numberOfParticles = 100;
  for (let i = 0; i < numberOfParticles; i++) {
    const size = Math.random() * 2 + 1;
    const x = Math.random() * innerWidth;
    const y = Math.random() * innerHeight;
    const directionX = (Math.random() - 0.5) * 0.8;
    const directionY = (Math.random() - 0.5) * 0.8;
    const color = '#00c4ff';
    particlesArray.push({ x, y, directionX, directionY, size, color });
  }
}

function animate() {
  requestAnimationFrame(animate);
  ctx.clearRect(0, 0, innerWidth, innerHeight);

  particlesArray.forEach(p => {
    ctx.beginPath();
    ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2, false);
    ctx.fillStyle = p.color;
    ctx.shadowBlur = 15;
    ctx.shadowColor = p.color;
    ctx.fill();
    p.x += p.directionX;
    p.y += p.directionY;

    // rebater nas bordas
    if (p.x < 0 || p.x > innerWidth) p.directionX *= -1;
    if (p.y < 0 || p.y > innerHeight) p.directionY *= -1;

    // ligação entre partículas
    particlesArray.forEach(other => {
      const dx = p.x - other.x;
      const dy = p.y - other.y;
      const distance = Math.sqrt(dx * dx + dy * dy);
      if (distance < 100) {
        ctx.beginPath();
        ctx.strokeStyle = `rgba(0,196,255,${1 - distance / 100})`;
        ctx.lineWidth = 0.5;
        ctx.moveTo(p.x, p.y);
        ctx.lineTo(other.x, other.y);
        ctx.stroke();
      }
    });
  });
}

window.addEventListener('resize', () => {
  canvas.width = innerWidth;
  canvas.height = innerHeight;
  init();
});

canvas.width = innerWidth;
canvas.height = innerHeight;
init();
animate();
function toggleTheme() {
  document.body.classList.toggle('dark');
}
