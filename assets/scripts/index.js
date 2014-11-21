window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

// Shims
context.canvas = canvas;

// Functions
var img = new Image();
img.ready = false;
img.onload = function() {
    img.ready = true;
};
img.src = 'media/rect.png';

function animate() {
    context.clearRect(0, 0, canvas.width, canvas.height);

    if (img.ready) {
        context.save();
            context.rotate(Math.PI / 4);

            context.beginPath();
            context.moveTo(0, 0);
            context.lineTo(64, 0);
            context.lineTo(64, 64);
            context.lineTo(0, 64);
            context.closePath();
            context.stroke();
        context.restore();

        context.drawImage(img, 0, 0);
        context.drawImage(img, 300, 0);
        context.drawImage(img, 0, 300);
        context.drawImage(img, 300, 300);
    }

    // Draw FPS
    context.fillStyle = '#f00';
    context.fillText(window.getAverageFPS().toFixed(2), 600, 12);

    requestAnimationFrame(animate);
}

animate();
