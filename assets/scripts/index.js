(function() { 'use strict';

    var canvas = document.getElementById('canvas'),
        context = canvas.getContext('2d');

    print('default font: ' + context.font);
    context.font = '32pt Arial';
    print('default font: ' + context.font);

    context.fillStyle = '#808';
    context.fillText('Font: Arial', 200, 200);

})();
