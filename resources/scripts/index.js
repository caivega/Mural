window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

var img = new Image();
img.onload = function() {
    context.translate(100, 100);

    context.strokeStyle = '#000';
    context.beginPath();
    context.moveTo(0, 0);
    context.lineTo(20, 0);
    context.lineTo(20, 20);
    context.lineTo(0, 20);
    context.closePath();
    context.stroke();

    context.save();
    context.scale(2, 2);
    context.drawImage(img, 0, 0);
    context.restore();

    context.drawImage(img, 0, 0);
};
img.src = 'media/heart-full.png';
