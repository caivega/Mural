//
//  BindingCanvasStyle.cpp
//  CinderCanvas
//
//  Created by Sean on 11/17/14.
//
//

#include "BindingCanvasStyle.h"
#include "BindingCanvas.h"

namespace mural
{
#define MU_BIND_SET_GET_STYLE(CLASS, NAME) \
    duk_eval_string(ctx, "__MURAL__.__defineAccessor__"); \
    duk_get_prop_string(ctx, -2, "prototype"); \
    duk_push_string(ctx, #NAME); \
    duk_push_c_function(ctx, w_##CLASS##_prototype_set_##NAME, 1); \
    duk_push_c_function(ctx, w_##CLASS##_prototype_get_##NAME, 0); \
    duk_call(ctx, 4); \
    duk_pop(ctx);

    int w_CanvasStyle_constructor(duk_context *ctx)
    {
        auto inst = new BindingCanvasStyle();
        inst->binding = new BindingCanvas();

        setNativePointer(ctx, inst);

        return 1;
    }

    const duk_number_list_entry numbers_of_CanvasStyle[] = {
        { NULL, 0.0 }
    };
    const duk_function_list_entry methods_of_CanvasStyle[] = {
        { NULL, NULL, 0 }
    };

    int w_CanvasStyle_prototype_set_width(duk_context *ctx)
    {
        std::string valueStr = duk_get_string(ctx, 0);

        auto inst = getNativePointer<BindingCanvasStyle>(ctx);
        // style value format is "%fpx"
        inst->binding->setStyleWidth(std::stof(valueStr.substr(0, valueStr.size() - 2)));

        return 0;
    }
    int w_CanvasStyle_prototype_get_width(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvasStyle>(ctx);

        std::string result = std::to_string((int)(inst->binding->getStyleWidth()));
        result += "px";

        duk_push_string(ctx, result.c_str());

        return 1;
    }

    int w_CanvasStyle_prototype_set_height(duk_context *ctx)
    {
        std::string valueStr = duk_get_string(ctx, 0);

        auto inst = getNativePointer<BindingCanvasStyle>(ctx);
        // style value format is "%fpx"
        inst->binding->setStyleHeight(std::stof(valueStr.substr(0, valueStr.size() - 2)));

        return 0;
    }
    int w_CanvasStyle_prototype_get_height(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvasStyle>(ctx);

        std::string result = std::to_string((int)(inst->binding->getStyleHeight()));
        result += "px";

        duk_push_string(ctx, result.c_str());
        
        return 1;
    }

    int w_CanvasStyle_prototype_set_left(duk_context *ctx)
    {
        std::string valueStr = duk_get_string(ctx, 0);

        auto inst = getNativePointer<BindingCanvasStyle>(ctx);
        // style value format is "%fpx"
        inst->binding->setStyleLeft(std::stof(valueStr.substr(0, valueStr.size() - 2)));

        return 0;
    }
    int w_CanvasStyle_prototype_get_left(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvasStyle>(ctx);

        std::string result = std::to_string((int)(inst->binding->getStyleLeft()));
        result += "px";

        duk_push_string(ctx, result.c_str());
        
        return 1;
    }

    int w_CanvasStyle_prototype_set_top(duk_context *ctx)
    {
        std::string valueStr = duk_get_string(ctx, 0);

        auto inst = getNativePointer<BindingCanvasStyle>(ctx);
        // style value format is "%fpx"
        inst->binding->setStyleTop(std::stof(valueStr.substr(0, valueStr.size() - 2)));

        return 0;
    }
    int w_CanvasStyle_prototype_get_top(duk_context *ctx)
    {
        auto inst = getNativePointer<BindingCanvasStyle>(ctx);

        std::string result = std::to_string((int)(inst->binding->getStyleTop()));
        result += "px";

        duk_push_string(ctx, result.c_str());
        
        return 1;
    }

    void js_register_CanvasStyle(duk_context *ctx)
    {
        MU_START_BINDING(CanvasStyle);

        MU_BIND_METHODS_AND_NUMBERS(CanvasStyle);

        MU_BIND_SET_GET(CanvasStyle, width);
        MU_BIND_SET_GET(CanvasStyle, height);
        MU_BIND_SET_GET(CanvasStyle, left);
        MU_BIND_SET_GET(CanvasStyle, top);

        MU_FINISH_BINDING(CanvasStyle);
    }
}
