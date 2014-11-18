window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

var img = new Image();
img.onload = function() {
    context.translate(100, 100);

    context.strokeStyle = '#000';
    context.strokeRect(0, 0, 100, 100);

    context.save();
    context.scale(2, 2);
    context.drawImage(img, 0, 0);
    context.restore();

    context.drawImage(img, 0, 0);
};
img.src = 'media/heart-full.png';
