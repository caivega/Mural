//
//  CanvasContext.h
//  CinderCanvas
//
//  Created by Sean on 11/11/14.
//
//

#ifndef __CinderCanvas__CanvasContext__
#define __CinderCanvas__CanvasContext__

#include "Global.h"

using namespace ci;

#define CANVAS_STATE_STACK_SIZE 16

namespace mural
{
    typedef enum {
        kLineCapButt,
        kLineCapRound,
        kLineCapSquare
    } LineCap;
    
    typedef enum {
        kLineJoinMiter,
        kLineJoinBevel,
        kLineJoinRound
    } LineJoin;

    typedef enum {
        kCompositeOperationSourceOver,
        kCompositeOperationLighter,
        kCompositeOperationDarker,
        kCompositeOperationDestinationOut,
        kCompositeOperationDestinationOver,
        kCompositeOperationSourceAtop,
        kCompositeOperationXOR,
        kCompositeOperationCopy,
        kCompositeOperationSourceIn,
        kCompositeOperationDestinationIn,
        kCompositeOperationSourceOut,
        kCompositeOperationDestinationAtop
    } CompositeOperation;

    struct CanvasState {
        CGAffineTransform transform;
        
        CompositeOperation globalCompositeOperation;
        Color fillColor;
//        NSObject<EJFillable> *fillObject;
        Color strokeColor;
        float globalAlpha;
        
        float lineWidth;
        LineCap lineCap;
        LineJoin lineJoin;
        float miterLimit;
        
//        EJTextAlign textAlign;
//        EJTextBaseline textBaseline;
//        EJFontDescriptor *font;
        
        Path2d *clipPath;
    };
    
    class CanvasContext
    {
        Path2d *path;
        
        int stateIndex;
        CanvasState stateStack[CANVAS_STATE_STACK_SIZE];
        CanvasState *state;
    public:
        CanvasContext();
        ~CanvasContext();
        
        void beginPath();
        void closePath();
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void strokeRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);
        void stroke();
        void fill();
    };

}

#endif /* defined(__CinderCanvas__CanvasContext__) */
