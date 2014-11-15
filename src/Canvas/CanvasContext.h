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
        CompositeOperation globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        Color fillStyle = Color::black();
        Color strokeStyle = Color::black();
        float globalAlpha = 1.0f;

        float lineWidth = 1.0f;
        LineCap lineCap = LineCap::kLineCapButt;
        LineJoin lineJoin = LineJoin::kLineJoinMiter;
        float miterLimit = 10.0f;

        Font font = Font::getDefault();

        std::vector<Path2d> paths;

        void operator=(const CanvasState& other)
        {
            globalCompositeOperation = other.globalCompositeOperation;
            fillStyle = other.fillStyle;
            strokeStyle = other.strokeStyle;
            globalAlpha = other.globalAlpha;

            lineWidth = other.lineWidth;
            lineCap = other.lineCap;
            lineJoin = other.lineJoin;
            miterLimit = other.miterLimit;

            font = other.font;

            paths.push_back(Path2d());
        }
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

        void strokeText(const std::string& text, float x, float y);
        void fillText(const std::string& text, float x, float y);

        void stroke();
        void fill();

        void translate(float x, float y);
        void rotate(float radians);
        void scale(float x, float y);

        void clearRect(float x, float y, float w, float h);

        void setLineWidth(float width);
        void setStrokeStyle(float r, float g, float b);
        void setFillStyle(float r, float g, float b);
        void setGlobalAlpha(float a);
        float getGlobalAlpha();
    };

    void stringToColorRGBA(const std::string& color, float& r, float& g, float& b, float& a);
    void colorHSLAToColorRGBA(float h, float s, float l, float a, float& rr, float& gg, float& bb, float& aa);
}

#endif /* defined(__CinderCanvas__CanvasContext__) */
