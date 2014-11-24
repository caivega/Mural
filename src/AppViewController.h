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
        ci::app::App *appInst;
    public:

        bool booted;
        JavaScriptView *view;

        float averageFPS;

    public:
        void initWithScript(const String& path, int width = 640, int height = 480);

        void tickAndDraw();

        int getWidth() const;
        void setWidth(int w);
        int getHeight() const;
        void setHeight(int h);
        std::string getTitle() const;
        void setTitle(const std::string& title);

        static AppViewController& getInstance()
        {
            static AppViewController instance;
            return instance;
        }
        void setupWithAppInstance(ci::app::App *inst)
        {
            this->appInst = inst;
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
