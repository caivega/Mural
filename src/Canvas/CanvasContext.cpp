//
//  CanvasContext.cpp
//  CinderCanvas
//
//  Created by Sean on 11/11/14.
//
//

#include "CanvasContext.h"

namespace mural
{
    CanvasContext::CanvasContext()
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

        state->paths.push_back(Path2d());
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

        gl::pushMatrices();
    }

    void CanvasContext::restore()
    {
        if (stateIndex == 0) { return; }

        // Load state from stack
        stateIndex--;
        state = &stateStack[stateIndex];

        gl::popMatrices();
    }

    void CanvasContext::beginPath()
    {
        state->paths.clear();
        state->paths.push_back(Path2d());
    }

    void CanvasContext::closePath()
    {
        if (!state->paths.empty()) {
            state->paths.back().close();
        }
        state->paths.clear();
        state->paths.push_back(Path2d());
    }

    void CanvasContext::moveTo(float x, float y)
    {
        Path2d p;
        p.moveTo(x, y);
        state->paths.push_back(p);
    }

    void CanvasContext::lineTo(float x, float y)
    {
        state->paths.back().lineTo(x, y);
    }

    void CanvasContext::arc(float x, float y, float radius, float startRadians, float endRadians, bool antiClockwise)
    {
        state->paths.back().arc(x, y, radius, startRadians, endRadians, !antiClockwise);
    }

    void CanvasContext::stroke()
    {
        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->globalAlpha);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::draw(*it);
            }
        }
    }

    void CanvasContext::fill()
    {
        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->globalAlpha);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::drawSolid(*it);
            }
        }
    }

    void CanvasContext::translate(float x, float y)
    {
        gl::translate(x, y);
    }

    void CanvasContext::rotate(float radians)
    {
        gl::rotate(toDegrees(radians));
    }

    void CanvasContext::scale(float x, float y)
    {
        gl::scale(x, y);
    }

    void CanvasContext::clearRect(float x, float y, float w, float h)
    {
        gl::color(1.0f, 1.0f, 1.0f, 1.0f);
        gl::drawSolidRect(Rectf(x, y, w, h));
    }

    void CanvasContext::strokeRect(float x, float y, float w, float h)
    {
        gl::drawStrokedRect(Rectf(x, y, x + w, y + h));
    }

    void CanvasContext::fillRect(float x, float y, float w, float h)
    {
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));
    }

    void CanvasContext::strokeText(const std::string &text, float x, float y)
    {
        gl::drawString(text, Vec2f(x, y), state->strokeStyle, state->font);
    }

    void CanvasContext::fillText(const std::string &text, float x, float y)
    {
        gl::drawString(text, Vec2f(x, y), state->fillStyle, state->font);
    }

    void CanvasContext::setLineWidth(float width)
    {
        state->lineWidth = width;
        gl::lineWidth(state->lineWidth);
    }

    void CanvasContext::setStrokeStyle(float r, float g, float b)
    {
        state->strokeStyle.set(r, g, b);
    }

    void CanvasContext::setFillStyle(float r, float g, float b)
    {
        state->fillStyle.set(r, g, b);
    }

    void CanvasContext::setGlobalAlpha(float a)
    {
        state->globalAlpha = a;
    }

    float CanvasContext::getGlobalAlpha()
    {
        return state->globalAlpha;
    }
}
