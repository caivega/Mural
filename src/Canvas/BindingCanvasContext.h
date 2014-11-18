//
//  BindingCanvasContext.h
//  CinderCanvas
//
//  Created by Sean on 11/15/14.
//
//

#ifndef __CinderCanvas__BindingCanvasContext__
#define __CinderCanvas__BindingCanvasContext__

#include "CanvasContext.h"

namespace mural
{
    int w_CanvasContext_constructor(duk_context *ctx);

    int w_CanvasContext_prototype_save(duk_context *ctx);
    int w_CanvasContext_prototype_restore(duk_context *ctx);

    int w_CanvasContext_prototype_beginPath(duk_context *ctx);
    int w_CanvasContext_prototype_closePath(duk_context *ctx);

    int w_CanvasContext_prototype_moveTo(duk_context *ctx);
    int w_CanvasContext_prototype_lineTo(duk_context *ctx);
    int w_CanvasContext_prototype_rect(duk_context *ctx);
    int w_CanvasContext_prototype_arc(duk_context *ctx);

    int w_CanvasContext_prototype_strokeRect(duk_context *ctx);
    int w_CanvasContext_prototype_fillRect(duk_context *ctx);

    int w_CanvasContext_prototype_strokeText(duk_context *ctx);
    int w_CanvasContext_prototype_fillText(duk_context *ctx);

    int w_CanvasContext_prototype_stroke(duk_context *ctx);
    int w_CanvasContext_prototype_fill(duk_context *ctx);

    int w_CanvasContext_prototype_drawImage(duk_context *ctx);

    int w_CanvasContext_prototype_translate(duk_context *ctx);
    int w_CanvasContext_prototype_rotate(duk_context *ctx);
    int w_CanvasContext_prototype_scale(duk_context *ctx);

    int w_CanvasContext_prototype_clearRect(duk_context *ctx);

    int w_CanvasContext_prototype_set_lineWidth(duk_context *ctx);
    int w_CanvasContext_prototype_get_lineWidth(duk_context *ctx);
    int w_CanvasContext_prototype_set_strokeStyle(duk_context *ctx);
    int w_CanvasContext_prototype_get_strokeStyle(duk_context *ctx);
    int w_CanvasContext_prototype_set_fillStyle(duk_context *ctx);
    int w_CanvasContext_prototype_get_fillStyle(duk_context *ctx);
    int w_CanvasContext_prototype_set_globalAlpha(duk_context *ctx);
    int w_CanvasContext_prototype_get_globalAlpha(duk_context *ctx);

    duk_ret_t js_register_CanvasContext(duk_context *ctx);
}

#endif /* defined(__CinderCanvas__BindingCanvasContext__) */
