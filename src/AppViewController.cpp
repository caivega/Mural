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
    void AppViewController::initWithScript(const String& path, int width, int height)
    {
        view = new JavaScriptView(width, height);
        view->loadScriptAtPath(path);
    }
    void AppViewController::tickAndDraw()
    {
        if (view) {
            if (booted) {
                view->tickAndDraw();
            }
            else {
                view->boot();
                booted = true;
            }
        }
    }
    int AppViewController::getWidth() const
    {
        return appInst->getWindowWidth();
    }
    void AppViewController::setWidth(int w)
    {
        appInst->setWindowSize(w, appInst->getWindowHeight());
    }
    int AppViewController::getHeight() const
    {
        return appInst->getWindowHeight();
    }
    void AppViewController::setHeight(int h)
    {
        appInst->setWindowSize(appInst->getWindowWidth(), h);
    }
    std::string AppViewController::getTitle() const
    {
        return appInst->getWindow()->getTitle();
    }
}
