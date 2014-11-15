//
//  BasicClock.h
//  CinderCanvas
//
//  Created by Sean on 11/15/14.
//
//

#ifndef CinderCanvas_BasicClock_h
#define CinderCanvas_BasicClock_h

void BasicClock()
{
    const float PI = 4 * std::atan(1);

    const int CANVAS_WIDTH = 480;
    const int CANVAS_HEIGHT = 480;

    const float FONT_HEIGHT = 15;
    const float MARGIN = 35;
    const float HAND_TRUNCATION = CANVAS_WIDTH / 25;
    const float HOUR_HAND_TRUNCATION = CANVAS_WIDTH / 10;
    const float NUMERAL_SPACING = 20;
    const float RADIUS = CANVAS_WIDTH / 2 - MARGIN;
    const float HAND_RADIUS = RADIUS + NUMERAL_SPACING;

    auto ctx = new mural::CanvasContext();

    ctx->setLineWidth(2);

    auto drawCircle = [&] {
        ctx->beginPath();
        ctx->arc(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, RADIUS, 0, PI * 2, true);
        ctx->stroke();
    };
    auto drawCenter = [&] {
        ctx->beginPath();
        ctx->arc(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 5, 0, PI * 2, true);
        ctx->fill();
    };
    auto drawHand = [&](float loc, bool isHour) {
        float angle = (PI * 2) * (loc / 60) - PI / 2;
        float handRadius = isHour ?
            RADIUS - HAND_TRUNCATION - HOUR_HAND_TRUNCATION :
            RADIUS - HAND_TRUNCATION;
        ctx->moveTo(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);
        ctx->lineTo(CANVAS_WIDTH / 2  + cos(angle) * handRadius,
                       CANVAS_HEIGHT / 2 + sin(angle) * handRadius);
        ctx->stroke();
    };
    auto drawHands = [&] {
        int hour = 1;
        int minute = 16;
        int second = 38;

        drawHand(hour * 5 + (minute / 60) * 5, true);
        drawHand(minute, false);
        drawHand(second, false);
    };
    auto drawClock = [&] {
        drawCircle();
        drawCenter();
        drawHands();
    };

    drawClock();
}

#endif