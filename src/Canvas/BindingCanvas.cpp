//
//  BindingCanvas.cpp
//  CinderCanvas
//
//  Created by Sean on 11/17/14.
//
//

#include "BindingCanvas.h"
#include "BindingCanvasStyle.h"
#include "AppViewController.h"

namespace mural
{
    BindingCanvas::BindingCanvas():
        jsObjectRef(0),
        ctxJsObjectRef(0),
        renderingContext(nullptr),
        contextMode(kCanvasContextMode2D),
        width(CANVAS_DEFAULT_WIDTH),
        height(CANVAS_DEFAULT_HEIGHT),
        isScreenCanvas(false),
        useRetinaResolution(false),
        msaaEnabled(false),
        msaaSamples(2),
        style(Rectf(0, 0, CANVAS_DEFAULT_WIDTH, CANVAS_DEFAULT_HEIGHT))
    {
        scriptView = theAppController.view;

        if (!scriptView->hasScreenCanvas) {
            this->isScreenCanvas = true;
            scriptView->hasScreenCanvas = true;
        }
    }

    BindingCanvas::~BindingCanvas() {}

    const duk_number_list_entry numbers_of_Canvas[] = {
        { NULL, 0.0 }
    };
    const duk_function_list_entry methods_of_Canvas[] = {
        { NULL, NULL, 0 }
    };

    int w_Canvas_constructor(duk_context *ctx)
    {
        auto inst = new BindingCanvas();
        setNativePointer(ctx, inst);

        duk_push_this(ctx); // canvas
        duk_eval_string(ctx, "new __MURAL__.CanvasStyle()"); // canvas, style

        // Create a style object and bind to self
        auto styleInst = getNativePointerOfObjAt<BindingCanvasStyle>(ctx, -1); // canvas, style
        styleInst->binding = inst;

        // Set style as property
        duk_put_prop_string(ctx, -2, "style"); // canvas

        duk_pop(ctx);

        return 1;
    }

    void js_register_Canvas(duk_context *ctx)
    {
        MU_START_BINDING(Canvas);

        MU_BIND_METHODS_AND_NUMBERS(Canvas);

        MU_FINISH_BINDING(Canvas);
    }
}
