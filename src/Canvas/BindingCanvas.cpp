//
//  BindingCanvas.cpp
//  CinderCanvas
//
//  Created by Sean on 11/17/14.
//
//

#include "BindingCanvas.h"
#include "BindingCanvasStyle.h"
#include "BindingCanvasContext.h"
#include "AppViewController.h"

namespace mural
{
    BindingCanvas::BindingCanvas():
        jsObjectRef(0),
        ctxJsObjectRef(0),
        renderingContext(nullptr),
        contextMode(kCanvasContextModeInvalid),
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

            width = scriptView->getWidth();
            height = scriptView->getHeight();

            printf("Canvas is screen canvas\n");
        }
        else {
            printf("Canvas is texture canvas\n");
        }
    }

    BindingCanvas::~BindingCanvas() {}

    int BindingCanvas::getStyleWidth()
    {
        return scriptView->getWidth();
    }
    void BindingCanvas::setStyleWidth(int width)
    {
        scriptView->setWidth(width);
    }
    int BindingCanvas::getStyleHeight()
    {
        return scriptView->getHeight();
    }
    void BindingCanvas::setStyleHeight(int height)
    {
        scriptView->setHeight(height);
    }

    const duk_number_list_entry numbers_of_Canvas[] = {
        { NULL, 0.0 }
    };
    const duk_function_list_entry methods_of_Canvas[] = {
        { "getContext", w_Canvas_prototype_getContext, 1 },
        { NULL, NULL, 0 }
    };

    int w_Canvas_constructor(duk_context *ctx)
    {
        auto inst = new BindingCanvas();
        setNativePointer(ctx, inst);

        duk_push_this(ctx); // canvas
        duk_peval_string(ctx, "new __MURAL__.CanvasStyle()"); // canvas, style

        // Create a style object and bind to self
        auto styleInst = getNativePointerOfObjAt<BindingCanvasStyle>(ctx, -1); // canvas, style
        styleInst->binding = inst;

        // Set style as property
        duk_put_prop_string(ctx, -2, "style"); // canvas

        duk_pop(ctx);

        return 1;
    }

    int w_Canvas_prototype_get_nodeName(duk_context *ctx)
    {
        duk_push_string(ctx, "CANVAS");
        return 1;
    }

    int w_Canvas_prototype_get_width(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvas>(ctx);
        duk_push_int(ctx, inst->width);

        return 1;
    }
    int w_Canvas_prototype_set_width(duk_context *ctx)
    {
        int value = duk_require_int(ctx, 0);
        auto inst = getNativePointer<BindingCanvas>(ctx);
        if (inst->renderingContext) {
            inst->renderingContext->resize(value, -1);
            inst->width = inst->renderingContext->getWidth();
        }
        else {
            inst->width = value;
        }

        return 0;
    }
    int w_Canvas_prototype_get_height(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvas>(ctx);
        duk_push_int(ctx, inst->height);

        return 1;
    }
    int w_Canvas_prototype_set_height(duk_context *ctx)
    {
        int value = duk_require_int(ctx, 0);
        auto inst = getNativePointer<BindingCanvas>(ctx);
        if (inst->renderingContext) {
            inst->renderingContext->resize(-1, value);
            inst->height = inst->renderingContext->getHeight();
        }
        else {
            inst->height = value;
        }
        return 0;
    }

    int w_Canvas_prototype_getContext(duk_context *ctx)
    {
        int args = duk_get_top(ctx);
        if (args < 1) {
            duk_push_null(ctx);
            return 1;
        }

        CanvasContextMode mode = CanvasContextMode::kCanvasContextModeInvalid;
        std::string type = duk_require_string(ctx, 0);
        if (type == "2d") {
            mode = CanvasContextMode::kCanvasContextMode2D;
        }
        else if (type.find("webgl") != std::string::npos) {
            mode = CanvasContextMode::kCanvasContextModeWebGL;

            printf("Warning: WebGL is not supported currently.\n");

            duk_push_null(ctx);
            return 1;
        }

        auto inst = getNativePointer<BindingCanvas>(ctx);

        // Context already created?
        if (inst->contextMode != CanvasContextMode::kCanvasContextModeInvalid) {
            if (inst->contextMode == mode) {
                // push the existing context object and return
                jsPushRef(ctx, inst->ctxJsObjectRef);
                return 1;
            }
            else {
                printf("Warning: CanvasContext already created. Can't change 2d/webgl mode.\n");
            }
        }

        // Create a new context
        inst->scriptView->currRenderingContext = nullptr;

        // 2D screen or texture
        if (mode == CanvasContextMode::kCanvasContextMode2D) {
            duk_push_this(ctx); // canvas
            if (inst->isScreenCanvas) {
                // Create a texture CanvasContext instance
                duk_peval_string(ctx, "new __MURAL__.CanvasContext(true)"); // canvas, context
            }
            else {
                // Create a screen CanvasContext instance
                duk_peval_string(ctx, "new __MURAL__.CanvasContext(false)"); // canvas, context
            }
            // Setup canvas, context and save context JavaScript object reference
            auto contextInst = getNativePointerOfObjAt<CanvasContext>(ctx, -1); // canvas, context
            inst->renderingContext = contextInst;
            contextInst->resize(inst->width, inst->height);
            inst->ctxJsObjectRef = jsRef(ctx); // canvas, context
            duk_pop_2(ctx); // ...

            // Save to context pool so that it won't be delete by GC
            duk_peval_string(ctx, "__MURAL__.contextPool"); // contextPool
            duk_push_string(ctx, "push"); // contextPool, "push"
            jsPushRef(ctx, inst->ctxJsObjectRef); // contextPool, "push", context
            duk_call_prop(ctx, -3, 1); // contextPool, returnValue
            duk_pop_2(ctx); // ...

            // Return newly created context
            jsPushRef(ctx, inst->ctxJsObjectRef); // context
            return 1;
        }
        else if (mode == CanvasContextMode::kCanvasContextModeWebGL) {
            printf("Warning: WebGL is not supported currently.\n");
            duk_push_null(ctx);
            return 1;
        }

        // Should never go that far
        duk_push_null(ctx);
        return 1;
    }

    duk_ret_t js_register_Canvas(duk_context *ctx)
    {
        MU_START_BINDING(Canvas);

        MU_BIND_METHODS_AND_NUMBERS(Canvas);

        MU_BIND_GET(Canvas, nodeName);
        MU_BIND_SET_GET(Canvas, width);
        MU_BIND_SET_GET(Canvas, height);

        MU_FINISH_BINDING(Canvas);

        return 0;
    }
}
