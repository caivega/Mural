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
#include "Image.h"

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
    typedef struct { GLenum source; GLenum destination; float alphaFactor; } CompositeOperationFunc;
    extern const CompositeOperationFunc CompositeOperationFuncs[];

    struct CanvasState {
        CompositeOperation globalCompositeOperation = CompositeOperation::kCompositeOperationSourceOver;
        ColorA fillStyle = Color::black();
        std::string strokeStyleStr = "#000000";
        ColorA strokeStyle = Color::black();
        std::string fillStyleStr = "#000000";
        float globalAlpha = 1.0f;

        float lineWidth = 1.0f;
        LineCap lineCap = LineCap::kLineCapButt;
        LineJoin lineJoin = LineJoin::kLineJoinMiter;
        float miterLimit = 10.0f;

        Font font = Font::getDefault();

        MatrixAffine2f transform = MatrixAffine2f::identity();

        void operator=(const CanvasState& other)
        {
            globalCompositeOperation = other.globalCompositeOperation;
            fillStyle = other.fillStyle;
            strokeStyle = other.strokeStyle;
            strokeStyleStr = other.strokeStyleStr;
            globalAlpha = other.globalAlpha;

            lineWidth = other.lineWidth;
            lineCap = other.lineCap;
            lineJoin = other.lineJoin;
            miterLimit = other.miterLimit;

            font = other.font;

            transform = other.transform;
        }
    };

    class JavaScriptView;
    class BindingCanvas;
    class CanvasContext : public Renderable
    {
        int width, height;

        int stateIndex;
        CanvasState stateStack[CANVAS_STATE_STACK_SIZE];
        CanvasState *state;

        std::vector<Path2d> paths;

        gl::Fbo renderingBuffer;
        gl::TextureRef texture;
        CameraOrtho renderingCam;

        JavaScriptView *scriptView;
        friend JavaScriptView;
    public:
        BindingCanvas *canvas;

        CanvasContext(bool isScreenContext = false);
        ~CanvasContext();

        void save();
        void restore();

        void beginPath();
        void closePath();

        void moveTo(float x, float y);
        void lineTo(float x, float y);
        void bezierCurveTo(float x1, float y1, float x2, float y2, float x3, float y3);
        void quadraticCurveTo(float x1, float y1, float x2, float y2);
        void arcTo(float x1, float y1, float x2, float y2, float radius);

        void rect(float x, float y, float w, float h);
        void arc(float x, float y, float radius, float startRadians, float endRadians, bool antiClockwise = true);

        void strokeRect(float x, float y, float w, float h);
        void fillRect(float x, float y, float w, float h);

        void strokeText(const std::string& text, float x, float y);
        void fillText(const std::string& text, float x, float y);

        void stroke();
        void fill();

        void drawImage(Renderable *img, float dx, float dy);
        void drawImage(Renderable *img, float dx, float dy, float dw, float dh);
        void drawImage(Renderable *img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);

        void translate(float x, float y);
        void rotate(float radians);
        void scale(float x, float y);
        void transform(float m11, float m12, float m21, float m22, float dx, float dy);
        void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);

        void clearRect(float x, float y, float w, float h);

        void prepare();
        void present();

        gl::TextureRef getTexture() override;

        void setLineWidth(float width);
        float getLineWidth();
        void setStrokeStyle(const std::string& color);
        void setStrokeStyle(float r, float g, float b, float a = 1.0f);
        std::string getStrokeStyle();
        void setFillStyle(const std::string& color);
        void setFillStyle(float r, float g, float b, float a = 1.0f);
        std::string getFillStyle();
        void setGlobalAlpha(float a);
        float getGlobalAlpha();
        void setGlobalCompositeOperation(const std::string& op);
        std::string getGlobalCompositeOperation();
        void setFont(const std::string& fontName);
        std::string getFont();

        void resize(int width = -1, int height = -1);
        int getWidth() { return width; }
        int getHeight() { return height; }
    };
}

#endif /* defined(__CinderCanvas__CanvasContext__) */
