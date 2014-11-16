//
//  JavaScriptView.cpp
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#include "JavaScriptView.h"

// Modules
#include "BindingImage.h"
#include "Canvas/BindingCanvasContext.h"

// Tests
#include "Tests/BasicClock.h"
#include "Tests/AsyncImageLoader.h"
#include "Tests/ColorUtil.h"
#include "Tests/LoadImage.h"

#if defined(WIN32)
#  define OS_NAME "Windows"
#  define OS_AGENT "(Windows; OS ?)"
#elif defined(__APPLE__)
#  define OS_NAME "MacOS X"
#  define OS_AGENT "(MacOS X; OS 10.10)"
#elif defined(__linux__)
#  define OS_NAME "Linux"
#  define OS_AGENT "(Linux; OS ?)"
#endif

namespace mural
{
    JavaScriptView::JavaScriptView(int width, int height):
        jsGlobalContext(nullptr),
        lang("en"),
        width(width),
        height(height)
    {
        // Create the global JS context
        this->jsGlobalContext = duk_create_heap_default();

        // Setup global namespace for Mural built-in
        duk_push_global_object(this->jsGlobalContext); /* global */
        duk_push_object(this->jsGlobalContext);
        duk_put_prop_string(this->jsGlobalContext, -2, MURAL_JS_NAMESPACE);
        duk_pop(this->jsGlobalContext);

        // To make JavaScript objects accessible in C++
        jsRefSetup(this->jsGlobalContext);

        // Load shim for duktape
        duk_eval_file_noresult(this->jsGlobalContext, app::AppBasic::getResourcePath(MURAL_SHIM_JS).c_str());

        this->defineProperties();

        // Setup OpenGL context

        // Setup event callbacks

        // Register built-in
        js_register_Image(this->jsGlobalContext);
        js_register_CanvasContext(this->jsGlobalContext);

        // Load boot script
        duk_eval_file_noresult(this->jsGlobalContext, app::AppBasic::getResourcePath(MURAL_BOOT_JS).c_str());
    }

    JavaScriptView::~JavaScriptView()
    {
        duk_destroy_heap(this->jsGlobalContext);
    }

    void JavaScriptView::loadScriptAtPath(const String& path)
    {
        this->scriptPath = path;
    }

    void JavaScriptView::boot()
    {
        gl::enableAlphaBlending();
        gl::clear(ColorA::white(), false);

        if (this->scriptPath.length() > 0) {
            duk_eval_file_noresult(this->jsGlobalContext, this->scriptPath.c_str());
        }

        // [Tests]
//        BasicClock();
//        AsyncImageLoader();
//        ColorUtil();
        LoadImage();
    }

    void JavaScriptView::tickAndDraw()
    {
        // Block operations
        OperationQueue::defaultQueue().doBlockOperations();

        // RAF
        duk_push_global_object(this->jsGlobalContext);
        duk_get_prop_string(this->jsGlobalContext, -1, MURAL_JS_NAMESPACE);
        duk_get_prop_string(this->jsGlobalContext, -1, "tickAnimFrame");
        duk_call(this->jsGlobalContext, 0);
        duk_pop_n(this->jsGlobalContext, 3);
    }

    void JavaScriptView::defineProperties()
    {
        // Set properties to __MURAL__
        duk_push_global_object(this->jsGlobalContext);
        duk_get_prop_string(this->jsGlobalContext, -1, MURAL_JS_NAMESPACE); /* __MURAL__ */

        // - screenWidth
        duk_push_int(this->jsGlobalContext, width);
        duk_put_prop_string(this->jsGlobalContext, -2, "screenWidth");
        // - screenHeight
        duk_push_int(this->jsGlobalContext, height);
        duk_put_prop_string(this->jsGlobalContext, -2, "screenHeight");

        // - language
        duk_push_string(this->jsGlobalContext, this->lang.c_str());
        duk_put_prop_string(this->jsGlobalContext, -2, "language");
        // - userAgent
        std::string userAgent("Ejecta/");
        userAgent += MURAL_VERSION;
        userAgent += OS_AGENT;
        duk_push_string(this->jsGlobalContext, userAgent.c_str());
        duk_put_prop_string(this->jsGlobalContext, -2, "userAgent");
        // - app version
        duk_push_string(this->jsGlobalContext, "0.1.0");
        duk_put_prop_string(this->jsGlobalContext, -2, "appVersion");
        // - platform
        duk_push_string(this->jsGlobalContext, OS_NAME);
        duk_put_prop_string(this->jsGlobalContext, -2, "platform");

        // Leave global scope
        duk_pop_2(this->jsGlobalContext);
    }
}
