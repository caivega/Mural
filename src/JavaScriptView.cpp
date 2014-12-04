//
//  JavaScriptView.cpp
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#include "JavaScriptView.h"
#include "JavaScript/JavaScript.h"

// Modules
#include "BindingImage.h"
#include "Canvas/BindingCanvasStyle.h"
#include "Canvas/BindingCanvas.h"
#include "Canvas/BindingCanvasContext.h"
#include "Utils/UtilFunctions.h"
#include "LocalStorage.h"

#include "KeyMap.h"

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
        altDown(false),
        ctrlDown(false),
        metaDown(false),
        shiftDown(false),
        lastPosOnMouseMove(Vec2i(0, 0)),
        width(width), height(height),
        lang("en"),
        currRenderingContext(nullptr),
        screenRenderingContext(nullptr),
        hasScreenCanvas(false)
    {
        // Setup event callbacks
        initKeyCodeMap();

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
        duk_peval_file_noresult(this->jsGlobalContext, app::getAssetPath(MURAL_SHIM_JS).generic_string().c_str());

        // Register built-in
        registerModule(js_register_Image, "Image");
        registerModule(js_register_CanvasStyle, "CanvasStyle");
        registerModule(js_register_Canvas, "Canvas");
        registerModule(js_register_CanvasContext, "CanvasContext");
        registerModule(js_register_Utils, "Utils");
        registerModule(js_register_LocalStorage, "LocalStorage");
    }

    JavaScriptView::~JavaScriptView()
    {
        duk_destroy_heap(this->jsGlobalContext);
    }

    int JavaScriptView::getWidth() const
    {
        return this->width;
    }
    void JavaScriptView::setWidth(int width)
    {
        if (width <= 0) {
            return;
        }
        this->width = width;
//        theAppController.setWidth(width);
        printf("set canvas width\n");
    }
    int JavaScriptView::getHeight() const
    {
        return this->height;
    }
    void JavaScriptView::setHeight(int height)
    {
        if (height <= 0) {
            return;
        }
        this->height = height;
//        theAppController.setHeight(height);
        printf("set canvas height\n");
    }

    int JavaScriptView::getWindowWidth() const
    {
        return theAppController.getWidth();
    }
    void JavaScriptView::setWindowWidth(int width)
    {
        if (width <= 0) {
            return;
        }
        theAppController.setWidth(width);
    }
    int JavaScriptView::getWindowHeight() const
    {
        return theAppController.getHeight();
    }
    void JavaScriptView::setWindowHeight(int height)
    {
        if (height <= 0) {
            return;
        }
        theAppController.setHeight(height);
    }

    void JavaScriptView::loadScriptAtPath(const String& path)
    {
        this->scriptPath = path;
    }

    void JavaScriptView::boot()
    {
        // Set app properties to __MURAL__
        this->defineProperties();

        // Load boot script
        if (duk_peval_file(this->jsGlobalContext, app::getAssetPath(MURAL_BOOT_JS).generic_string().c_str()) != 0) {
            printf("%s\n", duk_safe_to_string(this->jsGlobalContext, -1));
        }
        duk_pop(this->jsGlobalContext);

        // Save JavaScript callback indexes for later use.
        // Calling functions directly is much faster than eval or access from global object
        duk_push_global_object(this->jsGlobalContext);
        duk_get_prop_string(this->jsGlobalContext, -1, MURAL_JS_NAMESPACE); // global, __MURAL__

        duk_get_prop_string(this->jsGlobalContext, -1, "tickAnimFrame");
        this->jsTickFunction = jsRef(this->jsGlobalContext);
        duk_pop(this->jsGlobalContext);

        duk_pop_2(this->jsGlobalContext); // Cleanup

        // Load app script
        if (this->scriptPath.length() > 0) {
            if (duk_peval_file(this->jsGlobalContext, app::getAssetPath(this->scriptPath).generic_string().c_str()) != 0) {
                printf("%s\n", duk_safe_to_string(this->jsGlobalContext, -1));
            }
            duk_pop(this->jsGlobalContext);
        }

        // Setup OpenGL for drawing
        gl::setViewport(Area(0, 0, width, height));
        glDisable(GL_DEPTH_TEST);
        gl::enableAlphaBlending();
        gl::clear(ColorA::white(), false);

        // [Tests]
//        BasicClock();
//        AsyncImageLoader();
//        ColorUtil();
//        LoadImage();
    }

    void JavaScriptView::update()
    {
        // RAF
        jsPushRef(this->jsGlobalContext, this->jsTickFunction);
        duk_call(this->jsGlobalContext, 0);
        duk_pop(this->jsGlobalContext);
    }

    void JavaScriptView::draw()
    {
        // Draw to screen
        if (this->screenRenderingContext) {
            gl::setViewport(ci::app::getWindowBounds());
            gl::clear(this->screenRenderingContext->canvas->backgroundColor, false);
            gl::draw(screenRenderingContext->getTexture(), ci::app::getWindowBounds());
        }
    }

    void JavaScriptView::mouseEvent(const char *type, ci::app::MouseEvent event)
    {
        // Calculate event properties
        int which = event.isLeft() ? 1 : (event.isMiddle() ? 2 : (event.isRight() ? 3 : 0));
        int buttons = 0;
        buttons |= (event.isLeftDown() ? 1 : 0);
        buttons |= (event.isRightDown() ? 2 : 0);
        buttons |= (event.isMiddleDown() ? 4 : 0);

        int x = event.getX(), y = event.getY();

        int movementX = x - lastPosOnMouseMove.x;
        int movementY = y - lastPosOnMouseMove.y;
        lastPosOnMouseMove.set(x, y);

        // Dispatch a MouseEvent
        duk_push_global_object(jsGlobalContext);
        duk_get_prop_string(jsGlobalContext, -1, "document"); // window, document
        duk_push_string(jsGlobalContext, "dispatchMouseEvent"); // window, document, dispatchMouseEvent

        duk_push_string(jsGlobalContext, type);
        duk_push_int(jsGlobalContext, which);
        duk_push_int(jsGlobalContext, buttons);
        duk_push_boolean(jsGlobalContext, altDown);
        duk_push_boolean(jsGlobalContext, ctrlDown);
        duk_push_boolean(jsGlobalContext, metaDown);
        duk_push_boolean(jsGlobalContext, shiftDown);
        duk_push_int(jsGlobalContext, x);
        duk_push_int(jsGlobalContext, y);
        duk_push_int(jsGlobalContext, movementX);
        duk_push_int(jsGlobalContext, movementY);

        duk_pcall_prop(jsGlobalContext, -13, 11);

        duk_pop_3(jsGlobalContext);
    }
    void JavaScriptView::keyEvent(const char *type, ci::app::KeyEvent event)
    {
        this->altDown = event.isAltDown();
        this->ctrlDown = event.isControlDown();
        this->metaDown = event.isMetaDown();
        this->shiftDown = event.isShiftDown();

        duk_push_global_object(jsGlobalContext);
        duk_get_prop_string(jsGlobalContext, -1, "document"); // window, document
        duk_push_string(jsGlobalContext, "dispatchKeyEvent"); // window, document, dispatchKeyEvent

        duk_push_string(jsGlobalContext, type); // ... type
        duk_push_int(jsGlobalContext, CiToKeyCodeMap[event.getCode()]); // ... keyCode
        duk_push_string(jsGlobalContext, CiToCodeMap[event.getCode()].c_str()); // ... code
        duk_push_boolean(jsGlobalContext, false); // ... meta

        duk_pcall_prop(jsGlobalContext, -6, 4);

        duk_pop_3(jsGlobalContext);
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

    void JavaScriptView::registerModule(duk_c_function registerFunc, const char *moduleName)
    {
        if (duk_safe_call(this->jsGlobalContext, registerFunc, 0, 1) != 0) {
            printf("[Module: %s] %s\n", moduleName, duk_safe_to_string(this->jsGlobalContext, -1));
        }
    }
}
