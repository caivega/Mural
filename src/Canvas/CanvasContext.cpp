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
//        state->transform = CGAffineTransformIdentity;
        state->lineWidth = 1;
        state->lineCap = kLineCapButt;
        state->lineJoin = kLineJoinMiter;
        state->miterLimit = 10;
        state->clipPath = nullptr;
        
        path = new Path2d();
    }
    
    CanvasContext::~CanvasContext()
    {
        for (int i = 0; i < stateIndex + 1; ++i) {
            delete stateStack[i].clipPath;
        }
        
        delete path;
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
        if( stateIndex == 0 ) {	return; }
        
        CompositeOperation oldCompositeOp = state->globalCompositeOperation;
        Path2d *oldClipPath = state->clipPath;
        
        // Clean up current state
        if (state->clipPath && state->clipPath != stateStack[stateIndex-1].clipPath) {
            resetClip();
        }
        state->clipPath = nullptr;
        
        // Load state from stack
        stateIndex--;
        state = &stateStack[stateIndex];
        
//        path->transform = state->transform;
        
        // Set Composite op, if different
        if (state->globalCompositeOperation != oldCompositeOp) {
            globalCompositeOperation = state->globalCompositeOperation;
        }
        
        // Render clip path, if present and different
        if (state->clipPath && state->clipPath != oldClipPath) {
            gl::draw(*(state->clipPath));
        }
    }
    
    void CanvasContext::beginPath()
    {
        path->clear();
    }
    
    void CanvasContext::closePath()
    {
        path->close();
    }
    
    void CanvasContext::moveTo(float x, float y)
    {
        // FIXME: Create a new path if current one is already used
        path->moveTo(x, y);
    }
    
    void CanvasContext::lineTo(float x, float y)
    {
        path->lineTo(x, y);
    }
    
    void CanvasContext::stroke()
    {
        gl::color(state->strokeColor);
        gl::lineWidth(state->lineWidth);
        gl::draw(*path);
    }
    
    void CanvasContext::fill()
    {
        gl::color(state->fillColor);
        gl::drawSolid(*path);
    }
    
    void CanvasContext::clearRect(float x, float y, float w, float h)
    {
    }
    
    void CanvasContext::strokeRect(float x, float y, float w, float h)
    {
        gl::drawStrokedRect(Rectf(x, y, x + w, y + h));
    }
    
    void CanvasContext::fillRect(float x, float y, float w, float h)
    {
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));
    }
    
    void CanvasContext::resetClip()
    {
        if (state->clipPath) {
//            [self flushBuffers];
            state->clipPath = nullptr;
            
//            glDepthMask(GL_TRUE);
//            glClear(GL_DEPTH_BUFFER_BIT);
//            glDepthMask(GL_FALSE);
//            glDepthFunc(GL_ALWAYS);
        }
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
