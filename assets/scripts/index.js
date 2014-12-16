/**
 * Rotating example from MDN:
 * https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Transformations
 */
(function() { 'use strict';

    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');

    ctx.fillStyle = '#f0f';
    ctx.fillRect(0, 0, 1, 1);

    var data = ctx.getImageData(0, 0, 2, 2);
    for (var i = 0; i < data.data.length; i++) {
        print(data.data[i]);
    }

})();
