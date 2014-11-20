//
//  AppViewController.h
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#ifndef CinderCanvas_AppViewController_h
#define CinderCanvas_AppViewController_h

#include "Global.h"
#include "JavaScriptView.h"

namespace mural
{

    class AppViewController
    {
    public:
        bool booted;
        JavaScriptView *view;

        float averageFPS;

    public:
        void initWithScript(const String& path, int width = 640, int height = 480);

        void tickAndDraw();

        static AppViewController& getInstance()
        {
            static AppViewController instance;
            return instance;
        }

    private:
        AppViewController(): booted(false), view(nullptr), averageFPS(0.0f) {}
        AppViewController(AppViewController const&) {}
        void operator=(AppViewController const&) {}

        ~AppViewController();
    };

}

#define theAppController mural::AppViewController::getInstance()

#endif /* defined(__CinderCanvas__AppViewController__) */
