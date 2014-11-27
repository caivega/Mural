//
//  CanvasContext.cpp
//  CinderCanvas
//
//  Created by Sean on 11/11/14.
//
//

#include "CanvasContext.h"
#include "AppViewController.h"
#include "../Utils/Color.h"

namespace mural
{
    CanvasContext::CanvasContext(bool isScreenContext)
    {
        memset(stateStack, 0, sizeof(stateStack));
        stateIndex = 0;
        state = &stateStack[stateIndex];

        state->globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        state->fillStyle = Color::black();
        state->strokeStyle = Color::black();
        state->globalAlpha = 1.0f;

        state->lineWidth = 1.0f;
        state->lineCap = LineCap::kLineCapButt;
        state->lineJoin = LineJoin::kLineJoinMiter;
        state->miterLimit = 10.0f;

        state->font = Font::getDefault();

        state->transform = MatrixAffine2f::identity();
        paths.push_back(Path2d());

        this->scriptView = theAppController.view;

        // Set as current rendering context
        this->scriptView->currRenderingContext = this;
        // Set as default rendering context if no one exists
        if (isScreenContext) {
            this->scriptView->screenRenderingContext = this;

            // Set size to view size
            width = scriptView->getWidth();
            height = scriptView->getHeight();
        }
        else {
            // Set to default size
            width = 300;
            height = 150;
        }

        // Create rendering buffer
        resize(width, height);
    }

    CanvasContext::~CanvasContext()
    {
    }

    void CanvasContext::save()
    {
        if (stateIndex == CANVAS_STATE_STACK_SIZE - 1) {
            printf("Warning: CANVAS_STATE_STACK_SIZE (%d) reached", CANVAS_STATE_STACK_SIZE);
            return;
        }

        stateStack[stateIndex + 1] = stateStack[stateIndex];
        stateIndex++;
        state = &stateStack[stateIndex];

        glPushMatrix();
    }

    void CanvasContext::restore()
    {
        if (stateIndex == 0) { return; }

        // Load state from stack
        stateIndex--;
        state = &stateStack[stateIndex];

        glPopMatrix();
    }

    void CanvasContext::beginPath()
    {
        paths.clear();
        paths.push_back(Path2d());
    }

    void CanvasContext::closePath()
    {
        if (!paths.empty()) {
            paths.back().close();
        }
        paths.push_back(Path2d());
    }

    void CanvasContext::moveTo(float x, float y)
    {
        Path2d p;
        p.moveTo(x, y);
        paths.push_back(p);
    }

    void CanvasContext::lineTo(float x, float y)
    {
        if (paths.empty()) {
            return;
        }
        paths.back().lineTo(x, y);
    }

    void CanvasContext::bezierCurveTo(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        if (paths.empty()) {
            return;
        }
        paths.back().curveTo(x1, y1, x2, y2, x3, y3);
    }

    void CanvasContext::quadraticCurveTo(float x1, float y1, float x2, float y2)
    {
        if (paths.empty()) {
            return;
        }
        paths.back().quadTo(x1, y1, x2, y2);
    }

    void CanvasContext::arcTo(float x1, float y1, float x2, float y2, float radius)
    {
        if (paths.empty()) {
            return;
        }
        paths.back().arcTo(x2, y2, x1, y1, radius);
    }

    void CanvasContext::rect(float x, float y, float w, float h)
    {
        Path2d p;
        p.moveTo(x, y);
        p.lineTo(x, y + h);
        p.lineTo(x + w, y + h);
        p.lineTo(x + w, y);
        p.close();

        paths.push_back(p);
    }

    void CanvasContext::arc(float x, float y, float radius, float startRadians, float endRadians, bool antiClockwise)
    {
        paths.back().arc(x, y, radius, startRadians, endRadians, !antiClockwise);
    }

    void CanvasContext::stroke()
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->globalAlpha);
        for (auto it = paths.begin(); it != paths.end(); ++it) {
            if (!it->empty()) {
                gl::draw(*it);
            }
        }

        present();
    }

    void CanvasContext::fill()
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->globalAlpha);
        for (auto it = paths.begin(); it != paths.end(); ++it) {
            if (!it->empty()) {
                gl::drawSolid(*it);
            }
        }

        present();
    }

    void CanvasContext::drawImage(Renderable *img, float dx, float dy)
    {
        prepare();

        // Clear color first
        gl::SaveColorState saveColor;
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getTexture()) {
            gl::draw(img->getTexture(), Vec2f(dx, dy));
        }

        present();
    }

    void CanvasContext::drawImage(Renderable *img, float dx, float dy, float dw, float dh)
    {
        prepare();

        // Clear color first
        gl::SaveColorState saveColor;
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getTexture()) {
            gl::draw(img->getTexture(), Rectf(dx, dy, dx + dw, dy + dh));
        }

        present();
    }

    void CanvasContext::drawImage(Renderable *img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
    {
        prepare();

        // Clear color first
        gl::SaveColorState saveColor;
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getTexture()) {
            gl::draw(img->getTexture(), Area(sx, sy, sx + sw, sy + sh), Rectf(dx, dy, dx + dw, dy + dh));
        }

        present();
    }

    void CanvasContext::translate(float x, float y)
    {
        Vec2f t = Vec2f(x, y);
        state->transform.translate(t);
        gl::translate(t);
    }

    void CanvasContext::rotate(float radians)
    {
        state->transform.rotate(radians);
        gl::rotate(toDegrees(radians));
    }

    void CanvasContext::scale(float x, float y)
    {
        Vec2f s(x, y);
        state->transform.scale(s);
        gl::scale(s);
    }

    void CanvasContext::clearRect(float x, float y, float w, float h)
    {
        // Clear paths
        paths.clear();

        prepare();

        gl::SaveColorState saveColor;
        gl::color(ColorA::white());
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::strokeRect(float x, float y, float w, float h)
    {
        prepare();

        gl::multModelView(Matrix44f(state->transform));

        gl::SaveColorState saveColor;
        gl::color(state->strokeStyle);
        gl::drawStrokedRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::fillRect(float x, float y, float w, float h)
    {
        prepare();

        gl::multModelView(Matrix44f(state->transform));

        gl::SaveColorState saveColor;
        gl::color(state->fillStyle);
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::strokeText(const std::string &text, float x, float y)
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->strokeStyle);
        gl::drawString(text, Vec2f(x, y), state->strokeStyle, state->font);

        present();
    }

    void CanvasContext::fillText(const std::string &text, float x, float y)
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->fillStyle);
        gl::drawString(text, Vec2f(x, y), state->fillStyle, state->font);

        present();
    }

    void CanvasContext::prepare()
    {
//        gl::SaveFramebufferBinding saveFbo;
        renderingBuffer.bindFramebuffer();

        // ONLY set matrix when not already
        if (scriptView->currRenderingContext != this) {
            scriptView->currRenderingContext = this;
            gl::setViewport(renderingBuffer.getBounds());
            gl::setMatrices(renderingCam);
        }
    }

    void CanvasContext::present()
    {
        renderingBuffer.unbindFramebuffer();
    }

    gl::TextureRef CanvasContext::getTexture()
    {
        texture = std::make_shared<gl::Texture>(renderingBuffer.getTexture());
        texture->setFlipped(true);

        return texture;
    }

    void CanvasContext::setLineWidth(float width)
    {
        prepare();

        state->lineWidth = width;
        gl::lineWidth(state->lineWidth);

        present();
    }

    float CanvasContext::getLineWidth()
    {
        return state->lineWidth;
    }

    void CanvasContext::setStrokeStyle(const std::string& c)
    {
        float a = 1.0f;
        stringToColorRGBA(c, state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, a);
    }

    void CanvasContext::setStrokeStyle(float r, float g, float b)
    {
        state->strokeStyle.set(r, g, b);
    }

    std::string CanvasContext::getStrokeStyle()
    {
        return colorRGBAToString(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b);
    }

    void CanvasContext::setFillStyle(const std::string& c)
    {
        float a = 1.0f;
        stringToColorRGBA(c, state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, a);
    }

    void CanvasContext::setFillStyle(float r, float g, float b)
    {
        state->fillStyle.set(r, g, b);
    }

    std::string CanvasContext::getFillStyle()
    {
        return colorRGBAToString(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b);
    }

    void CanvasContext::setGlobalAlpha(float a)
    {
        state->globalAlpha = a;
    }

    float CanvasContext::getGlobalAlpha()
    {
        return state->globalAlpha;
    }

    void CanvasContext::resize(int width, int height)
    {
        if (width > 0) {
            this->width = width;
        }
        if (height > 0) {
            this->height = height;
        }

        this->renderingBuffer = gl::Fbo(this->width, this->height);
        this->renderingCam.setOrtho(0, this->width, this->height, 0, -1, 1);

        prepare();
        gl::clear(ColorA(1.0f, 1.0f, 1.0f, 0.0f));
        present();
    }
}
