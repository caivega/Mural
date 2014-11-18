window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

context.strokeStyle = '##ff0';
context.rect(0, 0, 100, 100);
context.save();
context.strokeStyle = '#f0f';
context.rect(50, 50, 100, 100);
context.restore();
context.strokeStyle = '#0ff';
context.rect(100, 100, 100, 100);

context.stroke();
