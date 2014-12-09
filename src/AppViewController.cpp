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
    void AppViewController::update()
    {
        if (view) {
            if (booted) {
                view->update();
            }
            else {
                view->boot();
                booted = true;
            }
        }
    }
    void AppViewController::draw()
    {
        if (view && booted) {
            view->draw();
        }
    }
    int AppViewController::getWidth() const
    {
        return ci::app::getWindowWidth();
    }
    void AppViewController::setWidth(int w)
    {
        ci::app::setWindowSize(w, ci::app::getWindowHeight());
    }
    int AppViewController::getHeight() const
    {
        return ci::app::getWindowHeight();
    }
    void AppViewController::setHeight(int h)
    {
        ci::app::setWindowSize(ci::app::getWindowWidth(), h);
    }
    std::string AppViewController::getTitle() const
    {
        return ci::app::getWindow()->getTitle();
    }
}
