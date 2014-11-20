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
img.onerror = function() {
    print('failed to load img');
};
img.src = 'media/heart-full.png';

document.addEventListener('mousedown', function(evt) {
    print('mouse which: ' + evt.which);
});
document.onmousedown = function(evt) {
    print('mouse: (' + evt.clientX + ', ' + evt.clientY + ')');
};
