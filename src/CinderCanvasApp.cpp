#include "AppViewController.h"

using namespace ci;
using namespace mural;

class CinderCanvasApp : public app::AppNative
{
public:
    void prepareSettings(Settings *settings);
	void setup();
    void mouseDown(app::MouseEvent event);
	void draw();
};

void CinderCanvasApp::prepareSettings(Settings *settings)
{
    settings->setTitle("Mural");
}

void CinderCanvasApp::setup()
{
    theAppController.initWithScript("scripts/index.js");
}

void CinderCanvasApp::mouseDown(app::MouseEvent event)
{
}

void CinderCanvasApp::draw()
{
    theAppController.tickAndDraw();
}

CINDER_APP_NATIVE(CinderCanvasApp, app::RendererGl)
