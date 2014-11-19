window.canvas = document.createElement('canvas');


var canvas = document.getElementById('canvas'),
    context = canvas.getContext('2d');

var DRAW_SIZE = Math.min(canvas.width, canvas.height),
    FONT_HEIGHT = 15,
    MARGIN = 35,
    HAND_TRUNCATION = DRAW_SIZE / 25,
    HOUR_HAND_TRUNCATION = DRAW_SIZE / 10,
    NUMERAL_SPACING = 20,
    RADIUS = DRAW_SIZE / 2 - MARGIN,
    HAND_RADIUS = RADIUS + NUMERAL_SPACING;

context.lineWidth = 2;

// Functions.....................................................

function drawCircle() {
   context.beginPath();
   context.arc(DRAW_SIZE / 2, DRAW_SIZE / 2,
               RADIUS, 0, Math.PI * 2, true);
   context.stroke();
}

function drawNumerals() {
   var numerals = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
       angle = 0,
       numeralWidth = 0;

   numerals.forEach(function(numeral) {
      angle = Math.PI / 6 * (numeral - 3);
      // numeralWidth = context.measureText(numeral).width;
      numeralWidth = 20;
      context.fillText(numeral,
         DRAW_SIZE / 2  + Math.cos(angle) * (HAND_RADIUS) - numeralWidth / 2,
         DRAW_SIZE / 2 + Math.sin(angle) * (HAND_RADIUS) + FONT_HEIGHT / 3);
   });
}

function drawCenter() {
   context.beginPath();
   context.arc(DRAW_SIZE / 2, DRAW_SIZE / 2, 5, 0, Math.PI * 2, true);
   context.fill();
}

function drawHand(loc, isHour) {
   var angle = (Math.PI * 2) * (loc / 60) - Math.PI / 2,
       handRadius = isHour ? RADIUS - HAND_TRUNCATION - HOUR_HAND_TRUNCATION
                           : RADIUS - HAND_TRUNCATION;

   context.moveTo(DRAW_SIZE / 2, DRAW_SIZE / 2);
   context.lineTo(DRAW_SIZE / 2  + Math.cos(angle) * handRadius,
                  DRAW_SIZE / 2 + Math.sin(angle) * handRadius);
   context.stroke();
}

function drawHands() {
   var date = new Date,
       hour = date.getHours();
   hour = hour > 12 ? hour - 12 : hour;
   drawHand(hour * 5 + (date.getMinutes() / 60) * 5, true, 0.5);
   drawHand(date.getMinutes(), false, 0.5);
   drawHand(date.getSeconds(), false, 0.2);
}

function drawClock() {
   context.clearRect(0, 0, DRAW_SIZE, DRAW_SIZE);

   drawCircle();
   drawCenter();
   drawHands();
   drawNumerals();
}

// Initialization................................................

// context.font = FONT_HEIGHT + 'px Arial';
var loop = setInterval(drawClock, 1000);