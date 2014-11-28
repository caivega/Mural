#include "AppViewController.h"

using namespace ci;
using namespace mural;

class CinderCanvasApp : public app::AppNative
{
public:
    void prepareSettings(Settings *settings);

    void setup();

    void mouseDown(app::MouseEvent event);
    void mouseUp(app::MouseEvent event);
    void mouseMove(app::MouseEvent event);

    void keyDown(app::KeyEvent event);
    void keyUp(app::KeyEvent event);

	void draw();
};

void CinderCanvasApp::prepareSettings(Settings *settings)
{
    settings->setTitle("Mural");
//    settings->setResizable(false);
}

void CinderCanvasApp::setup()
{
    theAppController.initWithScript("scripts/index.js");
}

void CinderCanvasApp::mouseDown(app::MouseEvent event)
{
    if (theAppController.view && theAppController.booted) {
        theAppController.view->mouseEvent("mousedown", event);
    }
}
void CinderCanvasApp::mouseUp(app::MouseEvent event)
{
    if (theAppController.view && theAppController.booted) {
        theAppController.view->mouseEvent("mouseup", event);
    }
}
void CinderCanvasApp::mouseMove(app::MouseEvent event)
{
    if (theAppController.view && theAppController.booted) {
        theAppController.view->mouseEvent("mousemove", event);
    }
}

void CinderCanvasApp::keyDown(app::KeyEvent event)
{
    if (theAppController.view && theAppController.booted) {
        theAppController.view->keyEvent("keydown", event);
    }
}
void CinderCanvasApp::keyUp(app::KeyEvent event)
{
    if (theAppController.view && theAppController.booted) {
        theAppController.view->keyEvent("keyup", event);
    }
}

void CinderCanvasApp::draw()
{
    theAppController.averageFPS = getAverageFps();

    if (theAppController.view) {
        theAppController.tickAndDraw();
    }
}

CINDER_APP_NATIVE(CinderCanvasApp, app::RendererGl)
