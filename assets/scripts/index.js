/**
 * Rotating example from MDN:
 * https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Transformations
 */
(function() { 'use strict';

    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');

    ctx.globalCompositeOperation = 'xor';

    ctx.fillStyle = '#00f';
    ctx.fillRect(10, 10, 100, 100);

    ctx.fillStyle = '#f00';
    ctx.fillRect(50, 50, 100, 100);

})();
