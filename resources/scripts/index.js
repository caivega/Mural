print('Script start');

window.CanvasContext = __MURAL__.CanvasContext;

var context = new CanvasContext();

context.strokeStyle = '#0ff';
context.arc(32, 32, 32, 0, Math.PI * 2, true);
context.stroke();
