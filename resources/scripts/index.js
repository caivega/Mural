print('Script start');

var tickCound = 0;
 (function animate() {
     if ((tickCound++) > 60) {
         tickCound = 0;
         console.log('RAF');
     }
     requestAnimationFrame(animate);
 })();

var count = 0;
setInterval(function() {
    count++;
    console.log('count: ' + count);
}, 1000);
