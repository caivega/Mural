//
//  CanvasContext.cpp
//  CinderCanvas
//
//  Created by Sean on 11/11/14.
//
//

#include "CanvasContext.h"
#include "BindingCanvas.h"
#include "AppViewController.h"
#include "../Utils/Color.h"
#include "../Utils/FileUtil.h"

namespace mural
{
    const CompositeOperationFunc CompositeOperationFuncs[] = {
        [kCompositeOperationSourceOver] = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA, 1 },
        [kCompositeOperationLighter] = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA, 0 },
        [kCompositeOperationDarker] = { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, 1 },
        [kCompositeOperationDestinationOut] = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA, 1 },
        [kCompositeOperationDestinationOver] = { GL_ONE_MINUS_DST_ALPHA, GL_ONE, 1 },
        [kCompositeOperationSourceAtop] = { GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, 1 },
        [kCompositeOperationXOR] = { GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, 1 },
        [kCompositeOperationCopy] = { GL_ONE, GL_ZERO, 1 },
        [kCompositeOperationSourceIn] = { GL_DST_ALPHA, GL_ZERO, 1 },
        [kCompositeOperationDestinationIn] = { GL_ZERO, GL_SRC_ALPHA, 1 },
        [kCompositeOperationSourceOut] = { GL_ONE_MINUS_DST_ALPHA, GL_ZERO, 1 },
        [kCompositeOperationDestinationAtop] = { GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA, 1 }
    };
    const std::map<const std::string, CompositeOperation> OpMap = {
        { "source-over", kCompositeOperationSourceOver },
        { "lighter", kCompositeOperationLighter },
        { "darker", kCompositeOperationDarker },
        { "destination-out", kCompositeOperationDestinationOut },
        { "destination-over", kCompositeOperationDestinationOver },
        { "source-atop", kCompositeOperationSourceAtop },
        { "xor", kCompositeOperationXOR },
        { "copy", kCompositeOperationCopy },
        { "source-in", kCompositeOperationSourceIn },
        { "destination-in", kCompositeOperationDestinationIn },
        { "source-out", kCompositeOperationSourceOut },
        { "destination-atop", kCompositeOperationDestinationAtop }
    };

    CanvasContext::CanvasContext(bool isScreenContext):
        canvas(nullptr)
    {
        memset(stateStack, 0, sizeof(stateStack));
        stateIndex = 0;
        state = &stateStack[stateIndex];

        state->globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        state->fillStyle = ColorA(0.0f, 0.0f, 0.0f, 1.0f);
        state->strokeStyle = ColorA(0.0f, 0.0f, 0.0f, 1.0f);
        state->globalAlpha = 1.0f;

        state->lineWidth = 1.0f;
        state->lineCap = LineCap::kLineCapButt;
        state->lineJoin = LineJoin::kLineJoinMiter;
        state->miterLimit = 10.0f;

        state->font = Font::getDefault();
        state->textAlign = TextAlign::kTextAlignLeft;

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
        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->strokeStyle.a * state->globalAlpha);
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
        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->fillStyle.a * state->globalAlpha);
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

    void CanvasContext::transform(float m11, float m12, float m21, float m22, float dx, float dy)
    {
        MatrixAffine2f m(m11, m12, m21, m22, dx, dy);
        state->transform *= m;
        gl::multModelView(Matrix44f(m));
    }

    void CanvasContext::setTransform(float m11, float m12, float m21, float m22, float dx, float dy)
    {
        gl::multModelView(Matrix44f(state->transform.invertCopy()));
        state->transform.set(m11, m12, m21, m22, dx, dy);
        gl::multModelView(Matrix44f(state->transform));
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

        gl::SaveColorState saveColor;
        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->strokeStyle.a * state->globalAlpha);
        gl::drawStrokedRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::fillRect(float x, float y, float w, float h)
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->fillStyle.a * state->globalAlpha);
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::strokeText(const std::string &text, float x, float y)
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->strokeStyle.a * state->globalAlpha);

        if (state->textAlign == TextAlign::kTextAlignLeft) {
            gl::drawString(text, Vec2f(x, y), state->strokeStyle, state->font);
        }
        else if (state->textAlign == TextAlign::kTextAlignCenter) {
            gl::drawStringCentered(text, Vec2f(x, y), state->strokeStyle, state->font);
        }
        else if (state->textAlign == TextAlign::kTextAlignRight) {
            gl::drawStringRight(text, Vec2f(x, y), state->strokeStyle, state->font);
        }

        present();
    }

    void CanvasContext::fillText(const std::string &text, float x, float y)
    {
        prepare();

        gl::SaveColorState saveColor;
        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->fillStyle.a * state->globalAlpha);

        if (state->textAlign == TextAlign::kTextAlignLeft) {
            gl::drawString(text, Vec2f(x, y), state->fillStyle, state->font);
        }
        else if (state->textAlign == TextAlign::kTextAlignCenter) {
            gl::drawStringCentered(text, Vec2f(x, y), state->fillStyle, state->font);
        }
        else if (state->textAlign == TextAlign::kTextAlignRight) {
            gl::drawStringRight(text, Vec2f(x, y), state->fillStyle, state->font);
        }

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
        gl::enableAlphaBlending();

        glBlendFunc(CompositeOperationFuncs[state->globalCompositeOperation].source, CompositeOperationFuncs[state->globalCompositeOperation].destination);
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

    Surface CanvasContext::getImageData(int sx, int sy, int sw, int sh)
    {
        prepare();

        Surface s(sw, sh, true);

        glFlush();
        glReadPixels(sx, sy, sw, sh, GL_RGBA, GL_UNSIGNED_BYTE, s.getData());

        present();

        return s;
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
        stringToColorRGBA(c, state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->strokeStyle.a);
        state->strokeStyleStr = c;
    }

    void CanvasContext::setStrokeStyle(float r, float g, float b, float a)
    {
        state->strokeStyle.set(r, g, b, a);
        state->strokeStyleStr = colorRGBAToString(r, g, b, a);
    }

    std::string CanvasContext::getStrokeStyle()
    {
        return state->strokeStyleStr;
    }

    void CanvasContext::setFillStyle(const std::string& c)
    {
        stringToColorRGBA(c, state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->fillStyle.a);
        state->fillStyleStr = c;
    }

    void CanvasContext::setFillStyle(float r, float g, float b, float a)
    {
        state->fillStyle.set(r, g, b, a);
        state->fillStyleStr = colorRGBAToString(r, g, b, a);
    }

    std::string CanvasContext::getFillStyle()
    {
        return state->fillStyleStr;
    }

    void CanvasContext::setGlobalAlpha(float a)
    {
        state->globalAlpha = a;
    }

    float CanvasContext::getGlobalAlpha()
    {
        return state->globalAlpha;
    }

    void CanvasContext::setGlobalCompositeOperation(const std::string &op)
    {
        if (OpMap.find(op) != OpMap.end()) {
            state->globalCompositeOperation = OpMap.at(op);
        }
    }

    std::string CanvasContext::getGlobalCompositeOperation()
    {
        for (auto k = OpMap.begin(); k != OpMap.end(); ++k) {
            if (k->second == state->globalCompositeOperation) {
                return k->first;
            }
        }
        return "source-over";
    }

    void CanvasContext::setFont(const std::string &fontName)
    {
        float fontSize = 10.0f;
        std::string font = "sans-serif";

        StringList parts = splitString(fontName, " ");
        if (parts.size() < 1) {
            return;
        }

        // First param is font size?
        if (parts[0].find("px") != std::string::npos || parts[0].find("pt") != std::string::npos) {
            fontSize = (float)std::stoi(parts[0].substr(0, parts[0].size() - 2));
        }
        font = (parts.size() > 1 ? parts[1] : parts[0]);

        try {
            state->font = Font(font, fontSize);
        } catch (ci::FontInvalidNameExc e) {
            state->font = Font::getDefault();
        }
    }

    std::string CanvasContext::getFont()
    {
        return state->font.getName();
    }

    void CanvasContext::setTextAlign(const std::string &textAlign)
    {
        if (textAlign == "left" || textAlign == "start") {
            state->textAlign = TextAlign::kTextAlignLeft;
        }
        else if (textAlign == "center") {
            state->textAlign = TextAlign::kTextAlignCenter;
        }
        else if (textAlign == "right" || textAlign == "end") {
            state->textAlign = TextAlign::kTextAlignRight;
        }
    }

    std::string CanvasContext::getTextAlign()
    {
        switch (state->textAlign) {
            case TextAlign::kTextAlignLeft:
                return "left";
                break;
            case TextAlign::kTextAlignCenter:
                return "center";
                break;
            case TextAlign::kTextAlignRight:
                return "right";
                break;
            default:
                return "left";
        }
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
