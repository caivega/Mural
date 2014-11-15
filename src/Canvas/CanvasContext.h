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
        MatrixAffine2f transform = MatrixAffine2f::identity();

        CompositeOperation globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        Color fillStyle = Color(0.0f, 0.0f, 0.0f);
        Color strokeStyle = Color(0.0f, 0.0f, 0.0f);
        float globalAlpha = 1.0f;

        float lineWidth = 1.0f;
        LineCap lineCap = LineCap::kLineCapButt;
        LineJoin lineJoin = LineJoin::kLineJoinMiter;
        float miterLimit = 10.0f;

        Font font = Font::getDefault();

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
        void arc(float x, float y, float radius, float startRadians, float endRadians, bool antiClockwise = true);

        void strokeRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);

        void stroke();
        void fill();

        void clearRect(float x, float y, float w, float h);

        void setLineWidth(float width);
        void setStrokeStyle(const Color& c);
        void setFillStyle(const Color& c);
    };

}

#endif /* defined(__CinderCanvas__CanvasContext__) */
