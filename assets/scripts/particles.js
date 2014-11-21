window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

// Shims
context.canvas = canvas;

// Functions
drawGrid(context, '#d3d3d3', 10, 10);

context.lineWidth = 0.5;
// context.font = '32pt Ariel';
var circles = [];

for (var i = 0; i < 100; ++i) {
   circles[i] = {
        x: 100,
        y: 100,
        velocityX: 3*Math.random(),
        velocityY: 3*Math.random(),
        radius: 50*Math.random(),
        color: 'rgba(' +
            (Math.random()*255).toFixed(0) + ', ' +
            (Math.random()*255).toFixed(0) + ', ' +
            (Math.random()*255).toFixed(0) + ', 1.0)'
    };
}

var paused = true;
document.onmousedown = function(e) {
    e.preventDefault();
    e.stopPropagation();

    paused = !paused;
};

function animate() {
    context.clearRect(0, 0, context.canvas.width, context.canvas.height);
    drawGrid(context, '#d3d3d3', 10, 10);

    if (!paused) {
        context.fillStyle = '#000';
        context.fillText('Click to pause!', 32, 32);

        circles.forEach(function(circle) {
            context.beginPath();
            context.arc(circle.x, circle.y, circle.radius, 0, Math.PI*2, false);
            context.fillStyle = circle.color;
            context.fill();
            adjustPosition(circle);
        });
    }
    else {
        context.fillStyle = '#000';
        context.fillText('Click to start!', 32, 32);
    }

    context.fillStyle = '#f00';
    context.fillText(window.getAverageFPS().toFixed(2), 600, 12);

    requestAnimationFrame(animate);
};

function adjustPosition(circle) {
    if (circle.x + circle.velocityX + circle.radius > context.canvas.width ||
        circle.x + circle.velocityX - circle.radius < 0)
    {
        circle.velocityX = -circle.velocityX;
    }

    if (circle.y + circle.velocityY + circle.radius > context.canvas.height ||
        circle.y + circle.velocityY - circle.radius  < 0)
    {
        circle.velocityY= -circle.velocityY;
    }

    circle.x += circle.velocityX;
    circle.y += circle.velocityY;
}

function drawGrid(context, color, stepx, stepy) {
    context.strokeStyle = color;
    context.lineWidth = 0.5;

   for (var i = stepx + 0.5; i < context.canvas.width; i += stepx) {
        context.beginPath();
        context.moveTo(i, 0);
        context.lineTo(i, context.canvas.height);
        context.stroke();
    }

    for (var i = stepy + 0.5; i < context.canvas.height; i += stepy) {
        context.beginPath();
        context.moveTo(0, i);
        context.lineTo(context.canvas.width, i);
        context.stroke();
    }
}

animate();
