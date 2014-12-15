/**
 * Rotating example from MDN:
 * https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Transformations
 */
(function() { 'use strict';

    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');

    ctx.fillStyle = '#f0f';
    ctx.font = '48px Verdana';

    ctx.textAlign = 'left';
    ctx.fillText('Align to left', canvas.width * 0.5, 120);
    ctx.textAlign = 'center';
    ctx.fillText('Align to center', canvas.width * 0.5, 240);
    ctx.textAlign = 'right';
    ctx.fillText('Align to right', canvas.width * 0.5, 360);

    var data = ctx.createImageData(8, 4);
    print(data.data.length);

})();
