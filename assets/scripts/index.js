window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

document.addEventListener('keydown', function(e) {
    print('e.keyCode: ' + e.keyCode);
    print('e.code: ' + e.code);
});
