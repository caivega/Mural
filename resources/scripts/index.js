print('Script start');

window.CanvasContext = __MURAL__.CanvasContext;

//var context = new CanvasContext();

//context.strokeStyle = '#0ff';
//context.arc(32, 32, 32, 0, Math.PI * 2, true);
//context.stroke();

var img = new Image();
img.onload = function() {
//    print('player.png loaded!');
    // This will draw to canvas
//    context.drawImage(img, 100, 40, 60, 40);
//    context.drawImage(img, 0, 0, 75, 100, 100, 100, 75, 100);
};
img.src = 'media/player.png';
// This will not draw to canvas
//context.drawImage(img, 200, 200);

//var context2 = new CanvasContext();
//context2.fillStyle = '#f0f';
//context2.arc(100, 100, 50, 0, Math.PI * 2, true);
//context2.fill();

//context.drawImage(context2, 0, 0);
