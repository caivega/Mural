//
//  UtilFunctions.h
//  Mural
//
//  Created by Sean on 11/20/14.
//
//

#ifndef Mural_UtilFunctions_h
#define Mural_UtilFunctions_h

#include "AppViewController.h"

int w_Utils_function_getAverageFPS(duk_context *ctx)
{
    duk_push_number(ctx, (double)(theAppController.averageFPS));
    return 1;
}

duk_ret_t js_register_Utils(duk_context *ctx)
{
    duk_push_global_object(ctx); // global
    duk_get_prop_string(ctx, -1, "__MURAL__"); // global, __MURAL__
    duk_push_c_function(ctx, w_Utils_function_getAverageFPS, 0); // global, __MURAL__, function
    duk_put_prop_string(ctx, -2, "getAverageFPS");

    return 0;
}

#endif
