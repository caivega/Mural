//
//  BindingCanvasContext.cpp
//  CinderCanvas
//
//  Created by Sean on 11/15/14.
//
//

#include "BindingCanvasContext.h"

namespace mural
{
    const duk_number_list_entry numbers_of_CanvasContext[] = {
        { NULL, 0.0 }
    };
    const duk_function_list_entry methods_of_CanvasContext[] = {
        { "save",       w_CanvasContext_prototype_save,         0 },
        { "restore",    w_CanvasContext_prototype_restore,      0 },
        { "beginPath",  w_CanvasContext_prototype_beginPath,    0 },
        { "closePath",  w_CanvasContext_prototype_closePath,    0 },
        { "moveTo",     w_CanvasContext_prototype_moveTo,       2 },
        { "lineTo",     w_CanvasContext_prototype_lineTo,       2 },
        { "arc",        w_CanvasContext_prototype_arc,          6 },
        { "strokeRect", w_CanvasContext_prototype_strokeRect,   4 },
        { "fillRect",   w_CanvasContext_prototype_fillRect,     4 },
        { "strokeText", w_CanvasContext_prototype_strokeText,   3 },
        { "fillText",   w_CanvasContext_prototype_fillText,     3 },
        { "stroke",     w_CanvasContext_prototype_stroke,       0 },
        { "fill",       w_CanvasContext_prototype_fill,         0 },
        { "translate",  w_CanvasContext_prototype_translate,    2 },
        { "rotate",     w_CanvasContext_prototype_rotate,       1 },
        { "scale",      w_CanvasContext_prototype_scale,        2 },
        { "clearRect",  w_CanvasContext_prototype_clearRect,    0 },
        { NULL, NULL, 0 }
    };

    int w_CanvasContext_constructor(duk_context *ctx)
    {
        auto *inst = new CanvasContext();
        setNativePointer(ctx, inst);

        return 1;
    }

    int w_CanvasContext_prototype_save(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->save();

        return 0;
    }
    int w_CanvasContext_prototype_restore(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->restore();

        return 0;
    }

    int w_CanvasContext_prototype_beginPath(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->beginPath();

        return 0;
    }
    int w_CanvasContext_prototype_closePath(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->closePath();

        return 0;
    }

    int w_CanvasContext_prototype_moveTo(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->moveTo(x, y);

        return 0;
    }
    int w_CanvasContext_prototype_lineTo(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->lineTo(x, y);

        return 0;
    }
    int w_CanvasContext_prototype_arc(duk_context *ctx)
    {
        int args = duk_get_top(ctx);

        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        double radius = duk_to_number(ctx, 2);
        double startRadians = duk_to_number(ctx, 3);
        double endRadians = duk_to_number(ctx, 4);
        bool antiClockwise = true;
        if (args > 5) {
            antiClockwise = duk_to_boolean(ctx, 5);
        }

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->arc(x, y, radius, startRadians, endRadians, antiClockwise);

        return 0;
    }

    int w_CanvasContext_prototype_strokeRect(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        double w = duk_to_number(ctx, 2);
        double h = duk_to_number(ctx, 3);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->strokeRect(x, y, w, h);

        return 0;
    }
    int w_CanvasContext_prototype_fillRect(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        double w = duk_to_number(ctx, 2);
        double h = duk_to_number(ctx, 3);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->fillRect(x, y, w, h);

        return 0;
    }

    int w_CanvasContext_prototype_strokeText(duk_context *ctx)
    {
        std::string text = duk_to_string(ctx, 0);
        double x = duk_to_number(ctx, 1);
        double y = duk_to_number(ctx, 2);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->strokeText(text, x, y);

        return 0;
    }
    int w_CanvasContext_prototype_fillText(duk_context *ctx)
    {
        std::string text = duk_to_string(ctx, 0);
        double x = duk_to_number(ctx, 1);
        double y = duk_to_number(ctx, 2);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->fillText(text, x, y);

        return 0;
    }

    int w_CanvasContext_prototype_stroke(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->stroke();

        return 0;
    }
    int w_CanvasContext_prototype_fill(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->fill();

        return 0;
    }

    int w_CanvasContext_prototype_translate(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->translate(x, y);

        return 0;
    }
    int w_CanvasContext_prototype_rotate(duk_context *ctx)
    {
        double radians = duk_to_number(ctx, 0);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->rotate(radians);

        return 0;
    }
    int w_CanvasContext_prototype_scale(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->scale(x, y);

        return 0;
    }

    int w_CanvasContext_prototype_clearRect(duk_context *ctx)
    {
        double x = duk_to_number(ctx, 0);
        double y = duk_to_number(ctx, 1);
        double w = duk_to_number(ctx, 2);
        double h = duk_to_number(ctx, 3);

        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->clearRect(x, y, w, h);

        return 0;
    }

    int w_CanvasContext_prototype_set_lineWidth(duk_context *ctx)
    {
        double width = duk_to_number(ctx, 0);
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->setLineWidth(width);

        return 0;
    }
    int w_CanvasContext_prototype_get_lineWidth(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        duk_push_number(ctx, (double)(inst->getLineWidth()));

        return 1;
    }
    int w_CanvasContext_prototype_set_strokeStyle(duk_context *ctx)
    {
        const char *c = duk_to_string(ctx, 0);
        auto inst = getNativePointer<CanvasContext>(ctx);
        float r, g, b, a;
        stringToColorRGBA(c, r, g, b, a);
        inst->setStrokeStyle(r, g, b);

        return 0;
    }
    int w_CanvasContext_prototype_get_strokeStyle(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        duk_push_string(ctx, inst->getStrokeStyle().c_str());

        return 1;
    }
    int w_CanvasContext_prototype_set_fillStyle(duk_context *ctx)
    {
        const char *c = duk_to_string(ctx, 0);
        auto inst = getNativePointer<CanvasContext>(ctx);
        float r, g, b, a;
        stringToColorRGBA(c, r, g, b, a);
        inst->setFillStyle(r, g, b);

        return 0;
    }
    int w_CanvasContext_prototype_get_fillStyle(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        duk_push_string(ctx, inst->getFillStyle().c_str());

        return 1;
    }
    int w_CanvasContext_prototype_set_globalAlpha(duk_context *ctx)
    {
        double alpha = duk_to_number(ctx, 0);
        auto inst = getNativePointer<CanvasContext>(ctx);
        inst->setGlobalAlpha(alpha);

        return 0;
    }
    int w_CanvasContext_prototype_get_globalAlpha(duk_context *ctx)
    {
        auto inst = getNativePointer<CanvasContext>(ctx);
        duk_push_number(ctx, inst->getGlobalAlpha());

        return 1;
    }

    void js_register_CanvasContext(duk_context *ctx)
    {
        MU_START_BINDING(CanvasContext);

        MU_BIND_METHODS_AND_NUMBERS(CanvasContext);

        MU_BIND_SET_GET(CanvasContext, lineWidth);
        MU_BIND_SET_GET(CanvasContext, strokeStyle);
        MU_BIND_SET_GET(CanvasContext, fillStyle);
        MU_BIND_SET_GET(CanvasContext, globalAlpha);

        MU_FINISH_BINDING(CanvasContext);
    }
}