//
//  AppViewController.cpp
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#include "AppViewController.h"

using namespace ci;

namespace mural
{
    AppViewController::~AppViewController()
    {
        delete view;
    }
    void AppViewController::initWithScript(const String& path, int width, int height, const String& title)
    {
        view = new JavaScriptView(width, height, title);
        view->loadScriptAtPath(path);
    }
    void AppViewController::initWithScripts(const StringList& paths, int width, int height, const String& title)
    {
        view = new JavaScriptView(width, height, title);
        for (auto it = paths.begin(); it != paths.end(); ++it) {
            view->loadScriptAtPath(it->c_str());
        }
    }
    void AppViewController::tickAndDraw()
    {
        if (booted) {
            view->tickAndDraw();
        }
        else {
            view->boot();
            booted = true;
        }
    }
}
