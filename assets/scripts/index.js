(function() { 'use strict';

    var canvas = document.getElementById('canvas'),
        context = canvas.getContext('2d');

    context.fillStyle = '#808';
    context.fillRect(0, 0, 100, 100);

    // context.translate(50, 50);
    context.fillStyle = '#088';
    context.fillRect(0, 0, 50, 50);

})();
