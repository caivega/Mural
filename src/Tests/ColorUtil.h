//
//  ColorUtil.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef CinderCanvas_ColorUtil_h
#define CinderCanvas_ColorUtil_h

#include "../Canvas/CanvasContext.h"

void ColorUtil()
{
    float aa = 0.0f, bb = 0.0f, cc = 0.0f, dd = 0.0f;
    mural::stringToColorRGBA("#abc", aa, bb, cc, dd);
    printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
    mural::stringToColorRGBA("#80ff00", aa, bb, cc, dd);
    printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
    mural::stringToColorRGBA("rgb(0, 255, 0)", aa, bb, cc, dd);
    printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
    mural::stringToColorRGBA("rgba(120, 60, 30, 0.6)", aa, bb, cc, dd);
    printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
    mural::stringToColorRGBA("hsla(90, 100%, 50%, 1)", aa, bb, cc, dd);
    printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);

    printf("color string: %s", mural::colorRGBAToString(1.0f, 0.0f, 1.0f).c_str());
}

#endif
