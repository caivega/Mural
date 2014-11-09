#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;

class CinderCanvasApp : public app::AppNative
{
public:
	void setup();
    void mouseDown(app::MouseEvent event);
	void update();
	void draw();
};

void CinderCanvasApp::setup()
{
}

void CinderCanvasApp::mouseDown(app::MouseEvent event)
{
}

void CinderCanvasApp::update()
{
}

void CinderCanvasApp::draw()
{
	// clear out the window with black
    gl::clear(Color(0, 0, 0));
}

CINDER_APP_NATIVE(CinderCanvasApp, app::RendererGl)
