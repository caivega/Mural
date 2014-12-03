(function() { 'use strict';

    window.canvas = document.createElement('canvas');

    var canvas = document.getElementById('canvas'),
        context = canvas.getContext('2d');

    var lastCode = 'NONE';
    document.addEventListener('keydown', function(e) {
        lastCode = e.code;
    });

    context.fillStyle = '#808';
    (function animate() {
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.fillText(getAverageFPS().toFixed(2), canvas.width - 80, 20);

        context.fillText('KEY: ' + lastCode, canvas.width * 0.5 - 60, canvas.height * 0.5);

        requestAnimationFrame(animate);
    })();

})();
