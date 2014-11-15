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
        MatrixAffine2f transform;

        CompositeOperation globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        Color fillStyle = Color(0.0f, 0.0f, 0.0f);
        Color strokeStyle = Color(0.0f, 0.0f, 0.0f);
        float globalAlpha = 1.0f;

        float lineWidth;
        LineCap lineCap = LineCap::kLineCapButt;
        LineJoin lineJoin = LineJoin::kLineJoinMiter;
        float miterLimit = 10.0f;

        std::vector<Path2d> paths;
    };

    class CanvasContext
    {
        int stateIndex;
        CanvasState stateStack[CANVAS_STATE_STACK_SIZE];
        CanvasState *state;
    public:
        CanvasContext();
        ~CanvasContext();

        void save();
        void restore();
        void beginPath();
        void closePath();
        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void strokeRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);
        void stroke();
        void fill();
        void clearRect(float x, float y, float w, float h);

        void setLineWidth(float width);
        void setStrokeColor(const Color& c);
        void setFillColor(const Color& c);
    };

}

#endif /* defined(__CinderCanvas__CanvasContext__) */
