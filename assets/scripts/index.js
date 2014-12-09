/**
 * Rotating example from MDN:
 * https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API/Tutorial/Transformations
 */
(function() { 'use strict';

    var context = document.getElementById('canvas').getContext('2d');

    context.fillStyle = '#0f0';
    context.beginPath();
    context.arc(130, 100, 40, 0, Math.PI * 2, true);
    context.fill();

    context.fillStyle = '#f00';
    context.beginPath();
    context.arc(100, 150, 40, 0, Math.PI * 2, true);
    context.fill();

    context.fillStyle = '#00f';
    context.beginPath();
    context.arc(160, 150, 40, 0, Math.PI * 2, true);
    context.fill();

})();
