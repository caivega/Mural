window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

context.lineWidth = 2;

// Functions
function roundedRect(cornerX, cornerY, width, height, cornerRadius) {
   if (width > 0) context.moveTo(cornerX + cornerRadius, cornerY);
   else           context.moveTo(cornerX - cornerRadius, cornerY);

   context.arcTo(cornerX + width, cornerY,
                 cornerX + width, cornerY + height,
                 cornerRadius);

   context.arcTo(cornerX + width, cornerY + height,
                 cornerX, cornerY + height,
                 cornerRadius);

   context.arcTo(cornerX, cornerY + height,
                 cornerX, cornerY,
                 cornerRadius);

   if (width > 0) {
      context.arcTo(cornerX, cornerY,
                    cornerX + cornerRadius, cornerY,
                    cornerRadius);
   }
   else {
      context.arcTo(cornerX, cornerY,
                    cornerX - cornerRadius, cornerY,
                    cornerRadius);
   }
}

function drawRoundedRect(strokeStyle, fillStyle, cornerX, cornerY, width, height, cornerRadius) {
   context.beginPath();

   roundedRect(cornerX, cornerY, width, height, cornerRadius);

   context.strokeStyle = strokeStyle;
   context.fillStyle = fillStyle;

   context.stroke();
   context.fill();
}

drawRoundedRect('#00f',  '#ff0',   50,  40,  100,  100, 10);
drawRoundedRect('#808',  '#0f0',  275,  40, -100,  100, 20);
drawRoundedRect('#f00',  '#fff',  300, 140,  100, -100, 30);
drawRoundedRect('#fff',  '#00f',  525, 140, -100, -100, 40);
