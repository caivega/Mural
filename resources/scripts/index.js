window.canvas = document.createElement('canvas');


print('Script start');

var canvas = document.getElementById('canvas');
var context = canvas.getContext('2d');

context.strokeStyle = '#0ff';
context.arc(32, 32, 32, 0, Math.PI * 2, true);
context.stroke();

var img = new Image();
img.onload = function() {
   print('player.png loaded!');

   context.drawImage(img, 100, 40, 60, 40);
   context.drawImage(img, 0, 0, 75, 100, 100, 100, 75, 100);
};
img.src = 'media/player.png';

var canvas2 = document.createElement('canvas');
var context2 = canvas2.getContext('2d');
context2.fillStyle = '#f0f';
context2.arc(100, 100, 100, 0, Math.PI * 2, true);
context2.fill();

context.drawImage(context2, 0, 0);
