window.canvas = document.createElement('canvas');

var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

// Functions
console.log('canvas.style.width: ' + canvas.style.width);
console.log('canvas.style.height: ' + canvas.style.height);

canvas.style.width = canvas.style.height = '320px';

console.log('canvas.style.width: ' + canvas.style.width);
console.log('canvas.style.height: ' + canvas.style.height);
