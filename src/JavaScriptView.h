//
//  JavaScriptView.h
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#ifndef __CinderCanvas__JavaScriptView__
#define __CinderCanvas__JavaScriptView__

#include "Global.h"

#define MURAL_VERSION "0.1"
#define MURAL_SHIM_JS "scripts/shim.js"
#define MURAL_BOOT_JS "scripts/mural.js"

namespace mural
{
    class CanvasContext;
    class JavaScriptView
    {
        duk_context *jsGlobalContext;

        std::string scriptPath;

        int width, height;
        String lang;

        // input properties
        bool altDown;
        bool ctrlDown;
        bool metaDown;
        bool shiftDown;

        ci::Vec2i lastPosOnMouseMove;
    public:
        bool hasScreenCanvas;

        CanvasContext *currRenderingContext;
        CanvasContext *screenRenderingContext;

        JavaScriptView(int width, int height);
        ~JavaScriptView();

        int getWidth() const;
        void setWidth(int width);
        int getHeight() const;
        void setHeight(int height);

        // Methods
        void loadScriptAtPath(const String& path);
        void boot();
        void tickAndDraw();

        // Event callbacks
        void mouseEvent(const char *type, ci::app::MouseEvent event);
        void keyEvent(const char *type, ci::app::KeyEvent event);

    private:
        void defineProperties();
        void registerModule(duk_c_function registerFunc, const char *moduleName);
    };
}

#endif /* defined(__CinderCanvas__JavaScriptView__) */
