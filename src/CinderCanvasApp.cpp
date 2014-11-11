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
    theAppController.initWithScript(getResourcePath("scripts/index.js").c_str());
}

void CinderCanvasApp::setup()
{
}

void CinderCanvasApp::mouseDown(app::MouseEvent event)
{
}

void CinderCanvasApp::draw()
{
    theAppController.tickAndDraw();
}

CINDER_APP_NATIVE(CinderCanvasApp, app::RendererGl)
