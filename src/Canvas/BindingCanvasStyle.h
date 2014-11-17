//
//  BindingCanvasStyle.h
//  CinderCanvas
//
//  Created by Sean on 11/17/14.
//
//

#ifndef __CinderCanvas__BindingCanvasStyle__
#define __CinderCanvas__BindingCanvasStyle__

#include "Global.h"

namespace mural
{
    class BindingCanvas;
    class BindingCanvasStyle
    {
    public:
        BindingCanvas *binding;
        int jsObjectRef;
    };

    int w_CanvasStyle_constructor(duk_context *ctx);

    int w_CanvasStyle_prototype_set_width(duk_context *ctx);
    int w_CanvasStyle_prototype_get_width(duk_context *ctx);
    int w_CanvasStyle_prototype_set_height(duk_context *ctx);
    int w_CanvasStyle_prototype_get_height(duk_context *ctx);
    int w_CanvasStyle_prototype_set_left(duk_context *ctx);
    int w_CanvasStyle_prototype_get_left(duk_context *ctx);
    int w_CanvasStyle_prototype_set_top(duk_context *ctx);
    int w_CanvasStyle_prototype_get_top(duk_context *ctx);

    void js_register_CanvasStyle(duk_context *ctx);
}

#endif /* defined(__CinderCanvas__BindingCanvasStyle__) */
