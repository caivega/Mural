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
        
        state->globalAlpha = 1;
        state->globalCompositeOperation = kCompositeOperationSourceOver;
        state->transform = MatrixAffine2f::identity();
        state->lineWidth = 1;
        state->lineCap = kLineCapButt;
        state->lineJoin = kLineJoinMiter;
        state->miterLimit = 10;
        state->paths.push_back(Path2d());
    }

    CanvasContext::~CanvasContext()
    {
    }
    
    void CanvasContext::save()
    {
        if (stateIndex == CANVAS_STATE_STACK_SIZE-1) {
            printf("Warning: CANVAS_STATE_STACK_SIZE (%d) reached", CANVAS_STATE_STACK_SIZE);
            return;
        }
        
        stateStack[stateIndex + 1] = stateStack[stateIndex];
        stateIndex++;
        state = &stateStack[stateIndex];
    }
    
    void CanvasContext::restore()
    {
        if (stateIndex == 0) { return; }

        // Load state from stack
        stateIndex--;
        state = &stateStack[stateIndex];
    }
    
    void CanvasContext::beginPath()
    {
        state->paths.push_back(Path2d());
    }
    
    void CanvasContext::closePath()
    {
        if (!state->paths.empty()) {
            state->paths.back().close();
        }
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
    
    void CanvasContext::stroke()
    {
        gl::color(state->strokeColor);
        gl::lineWidth(state->lineWidth);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::draw(*it);
            }
        }
    }
    
    void CanvasContext::fill()
    {
        gl::color(state->fillColor);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::drawSolid(*it);
            }
        }
    }
    
    void CanvasContext::clearRect(float x, float y, float w, float h)
    {
        gl::color(1.0f, 1.0f, 1.0f);
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
    
    void CanvasContext::setLineWidth(float width)
    {
        state->lineWidth = width;
    }
    
    void CanvasContext::setStrokeColor(const Color &c)
    {
        state->strokeColor = c;
    }
    
    void CanvasContext::setFillColor(const Color &c)
    {
        state->fillColor = c;
    }
}
