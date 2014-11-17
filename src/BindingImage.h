//
//  BindingImage.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef __CinderCanvas__BindingImage__
#define __CinderCanvas__BindingImage__

#include "Image.h"

namespace mural
{
    int w_Image_constructor(duk_context *ctx);

    int w_Image_prototype_get_width(duk_context *ctx);
    int w_Image_prototype_get_height(duk_context *ctx);
    int w_Image_prototype_get_complete(duk_context *ctx);
    int w_Image_prototype_get_src(duk_context *ctx);
    int w_Image_prototype_set_src(duk_context *ctx);

    duk_ret_t js_register_Image(duk_context *ctx);
}

#endif /* defined(__CinderCanvas__BindingImage__) */
