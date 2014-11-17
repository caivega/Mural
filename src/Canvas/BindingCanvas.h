//
//  BindingCanvas.h
//  CinderCanvas
//
//  Created by Sean on 11/17/14.
//
//

#ifndef __CinderCanvas__BindingCanvas__
#define __CinderCanvas__BindingCanvas__

#include "CanvasContext.h"

namespace mural
{
    enum CanvasContextMode {
        kCanvasContextModeInvalid,
        kCanvasContextMode2D,
        kCanvasContextModeWebGL
    };

    class BindingCanvas
    {
    public:
        int jsObjectRef;
        /**
         * JavaScript object reference of context object
         */
        int ctxJsObjectRef;

        CanvasContext *renderingContext;
        CanvasContextMode contextMode;
        short width, height;

        Rectf style;

        bool isScreenCanvas;
        bool useRetinaResolution;

        bool msaaEnabled;
        int msaaSamples;

        BindingCanvas();
        ~BindingCanvas();

        float getStyleLeft() { return 10; }
        void setStyleLeft(float left) { style.x1 = left; }
        float getStyleTop() { return style.y1; }
        void setStyleTop(float top) { style.y1 = top; }
        float getStyleWidth() { return style.x2 - style.x1; }
        void setStyleWidth(float width) { style.x2 = style.x1 + width; }
        float getStyleHeight() { return style.y2 - style.y1; }
        void setStyleHeight(float height) { style.y2 = style.y1 + height; }
    };
}

#endif /* defined(__CinderCanvas__BindingCanvas__) */
