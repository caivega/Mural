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
    }
    
    CanvasContext::~CanvasContext()
    {
        for (int i = 0; i < stateIndex + 1; ++i) {
            delete stateStack[i].clipPath;
        }
        
        delete path;
    }
    
    void CanvasContext::moveTo(float x, float y)
    {
        
    }
    
    void CanvasContext::lineTo(float x, float y)
    {
        
    }
    
    void CanvasContext::stroke()
    {
        
    }
    
    void CanvasContext::fill()
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
}
