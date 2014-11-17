//
//  CanvasContext.cpp
//  CinderCanvas
//
//  Created by Sean on 11/11/14.
//
//

#include "CanvasContext.h"
#include "AppViewController.h"
#include <sstream>

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

        this->scriptView = theAppController.view;

        // Set as current rendering context
        this->scriptView->currRenderingContext = this;
        // Set as default rendering context if no one exists
        if (!this->scriptView->hasScreenCanvas) {
            this->scriptView->renderingContext = this;
            this->scriptView->hasScreenCanvas = true;

            // Set size to view size
            width = scriptView->width;
            height = scriptView->height;
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
        prepare();

        gl::color(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, state->globalAlpha);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::draw(*it);
            }
        }

        present();
    }

    void CanvasContext::fill()
    {
        prepare();

        gl::color(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, state->globalAlpha);
        for (auto it = state->paths.begin(); it != state->paths.end(); ++it) {
            if (!it->empty()) {
                gl::drawSolid(*it);
            }
        }

        present();
    }

    void CanvasContext::drawRenderable(mural::Renderable *img, float dx, float dy)
    {
        Image *image = dynamic_cast<Image *>(img);
        if (image) {
            drawImage(image, dx, dy);
        }
        else {
            drawCanvas(dynamic_cast<CanvasContext *>(img), dx, dy);
        }
    }

    void CanvasContext::drawRenderable(mural::Renderable *img, float dx, float dy, float dw, float dh)
    {
        Image *image = dynamic_cast<Image *>(img);
        if (image) {
            drawImage(image, dx, dy, dw, dh);
        }
        else {
            drawCanvas(dynamic_cast<CanvasContext *>(img), dx, dy, dw, dh);
        }
    }

    void CanvasContext::drawRenderable(mural::Renderable *img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
    {
        Image *image = dynamic_cast<Image *>(img);
        if (image) {
            drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh);
        }
        else {
            drawCanvas(dynamic_cast<CanvasContext *>(img), sx, sy, sw, sh, dx, dy, dw, dh);
        }
    }

    void CanvasContext::drawImage(Image *img, float dx, float dy)
    {
        prepare();

        // Clear color first
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getComplete()) {
            gl::draw(img->texture, Vec2f(dx, dy));
        }

        present();
    }

    void CanvasContext::drawImage(Image *img, float dx, float dy, float dw, float dh)
    {
        prepare();

        // Clear color first
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getComplete()) {
            gl::draw(img->texture, Rectf(dx, dy, dx + dw, dy + dh));
        }

        present();
    }

    void CanvasContext::drawImage(Image *img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
    {
        prepare();

        // Clear color first
        gl::color(1.0f, 1.0f, 1.0f);
        if (img->getComplete()) {
            gl::draw(img->texture, Area(sx, sy, sx + sw, sy + sh), Rectf(dx, dy, dx + dw, dy + dh));
        }

        present();
    }

    void CanvasContext::drawCanvas(CanvasContext *img, float dx, float dy)
    {
        prepare();

        gl::color(1.0f, 1.0f, 1.0f);
        gl::Texture t = img->renderingBuffer.getTexture();
        t.setFlipped();

        gl::draw(t, Vec2f(dx, dy));

        present();
    }

    void CanvasContext::drawCanvas(CanvasContext *img, float dx, float dy, float dw, float dh)
    {
        prepare();

        gl::color(1.0f, 1.0f, 1.0f);
        gl::Texture t = img->renderingBuffer.getTexture();
        t.setFlipped();

        gl::draw(t, Rectf(dx, dy, dx + dw, dy + dh));

        present();
    }

    void CanvasContext::drawCanvas(CanvasContext *img, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
    {
        prepare();

        gl::color(1.0f, 1.0f, 1.0f);
        gl::Texture t = img->renderingBuffer.getTexture();
        t.setFlipped();

        gl::draw(t, Area(sx, sy, sx + sw, sy + sh), Rectf(dx, dy, dx + dw, dy + dh));

        present();
    }

    void CanvasContext::translate(float x, float y)
    {
        prepare();

        gl::translate(x, y);

        present();
    }

    void CanvasContext::rotate(float radians)
    {
        prepare();

        gl::rotate(toDegrees(radians));

        present();
    }

    void CanvasContext::scale(float x, float y)
    {
        prepare();

        gl::scale(x, y);

        present();
    }

    void CanvasContext::clearRect(float x, float y, float w, float h)
    {
        prepare();

        // Clear paths
        state->paths.clear();

        gl::color(1.0f, 1.0f, 1.0f, 1.0f);
        gl::drawSolidRect(Rectf(x, y, w, h));

        present();
    }

    void CanvasContext::strokeRect(float x, float y, float w, float h)
    {
        prepare();

        gl::color(state->strokeStyle);
        gl::drawStrokedRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::fillRect(float x, float y, float w, float h)
    {
        prepare();

        gl::color(state->fillStyle);
        gl::drawSolidRect(Rectf(x, y, x + w, y + h));

        present();
    }

    void CanvasContext::strokeText(const std::string &text, float x, float y)
    {
        prepare();

        gl::drawString(text, Vec2f(x, y), state->strokeStyle, state->font);

        present();
    }

    void CanvasContext::fillText(const std::string &text, float x, float y)
    {
        prepare();

        gl::drawString(text, Vec2f(x, y), state->fillStyle, state->font);

        present();
    }

    void CanvasContext::prepare()
    {
        renderingBuffer.bindFramebuffer();

        gl::setViewport(renderingBuffer.getBounds());
        gl::setMatrices(renderingCam);
    }

    void CanvasContext::present()
    {
        renderingBuffer.unbindFramebuffer();
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
        float a = 1.0f;
        stringToColorRGBA(c, state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b, a);
    }

    void CanvasContext::setStrokeStyle(float r, float g, float b)
    {
        state->strokeStyle.set(r, g, b);
    }

    std::string CanvasContext::getStrokeStyle()
    {
        return colorRGBAToString(state->strokeStyle.r, state->strokeStyle.g, state->strokeStyle.b);
    }

    void CanvasContext::setFillStyle(const std::string& c)
    {
        float a = 1.0f;
        stringToColorRGBA(c, state->fillStyle.r, state->fillStyle.g, state->fillStyle.b, a);
    }

    void CanvasContext::setFillStyle(float r, float g, float b)
    {
        state->fillStyle.set(r, g, b);
    }

    std::string CanvasContext::getFillStyle()
    {
        return colorRGBAToString(state->fillStyle.r, state->fillStyle.g, state->fillStyle.b);
    }

    void CanvasContext::setGlobalAlpha(float a)
    {
        state->globalAlpha = a;
    }

    float CanvasContext::getGlobalAlpha()
    {
        return state->globalAlpha;
    }

    void CanvasContext::resize(int width, int height)
    {
        this->width = width;
        this->height = height;

        this->renderingBuffer = gl::Fbo(width, height);
        this->renderingCam.setOrtho(0, width, height, 0, 0, 1);

        renderingBuffer.bindFramebuffer();
        gl::clear(ColorA(1.0f, 1.0f, 1.0f, 0.0f));
        renderingBuffer.unbindFramebuffer();
    }

    void stringToColorRGBA(const std::string& color, float& r, float& g, float& b, float& a)
    {
        int length = color.size();
        if (length < 3) {
            r = g = b = 0.0f;
            a = 1.0f;
            return;
        }

        std::string str = "ffffff";
        float components[] = { 0.0f, 0.0f, 0.0f };

        // #f0f format
        if (color[0] == '#' && length == 4) {
            str[0] = str[1] = color[1];
            str[2] = str[3] = color[2];
            str[4] = str[5] = color[3];

            r = std::stoi(str.substr(0, 2), 0, 16) / 255.0f;
            g = std::stoi(str.substr(2, 2), 0, 16) / 255.0f;
            b = std::stoi(str.substr(4, 2), 0, 16) / 255.0f;
            a = 1.0f;
        }

        // #ff00ff format
        else if (color[0] == '#' && length == 7) {
            str = color.substr(1, 6);

            r = std::stoi(str.substr(0, 2), 0, 16) / 255.0f;
            g = std::stoi(str.substr(2, 2), 0, 16) / 255.0f;
            b = std::stoi(str.substr(4, 2), 0, 16) / 255.0f;
            a = 1.0f;
        }

        // rgb(255,0,255) or rgba(255,0,255,0.5) format
        else if ((color[0] == 'r' || color[0] == 'R') && (color[1] == 'g' || color[1] == 'G')) {
            int component = 0;
            for (int i = 4; i < length - 1 && component < 4; i++) {
                if (component == 3) {
                    // If we have an alpha component, copy the rest of the wide
                    // string into a char array and use atof() to parse it.
                    char alpha[8] = { 0,0,0,0, 0,0,0,0 };
                    for (int j = 0; i + j < length - 1 && j < 7; j++) {
                        alpha[j] = color[i + j];
                    }
                    a = atof(alpha);
                    component++;
                }
                else if (isdigit(color[i])) {
                    components[component] = components[component] * 10 + (color[i] - '0');
                }
                else if (color[i] == ',' || color[i] == ')') {
                    component++;
                }
            }

            r = components[0] / 255.0f;
            g = components[1] / 255.0f;
            b = components[2] / 255.0f;
        }

        // hsl(120,100%,50%) or hsla(120,100%,50%,0.5) format
        else if( (color[0] == 'h' || color[0] == 'H') && (color[1] == 's' || color[1] == 'S') ) {
            bool skipDigits = false;
            float hsla[4] = { 0, 0, 0, 1 };
            int component = 0;
            for (int i = 4; i < length - 1 && component < 4; i++) {
                if (component == 3) {
                    // If we have an alpha component, copy the rest of the wide
                    // string into a char array and use atof() to parse it.
                    char alpha[8] = { 0,0,0,0, 0,0,0,0 };
                    for (int j = 0; i + j < length - 1 && j < 7; j++) {
                        alpha[j] = color[i + j];
                    }
                    hsla[component] = atof(alpha);
                    component++;
                }
                else if (isdigit(color[i]) && !skipDigits) {
                    hsla[component] = hsla[component] * 10 + (color[i] - '0');
                }
                else if(color[i] == '.') {
                    skipDigits = true;
                }
                else if (color[i] == ',' || color[i] == ')') {
                    skipDigits = false;
                    component++;
                }
            }
            colorHSLAToColorRGBA(hsla[0] / 360.0f, hsla[1] / 100.0f, hsla[2] / 100.0f, hsla[3], r, g, b, a);
        }
    }

    std::string colorRGBAToString(float r, float g, float b)
    {
        std::stringstream stream;

        stream << std::setfill ('0') << std::setw(2) << std::hex << (int)(r * 255.0f);
        stream << std::setfill ('0') << std::setw(2) << std::hex << (int)(g * 255.0f);
        stream << std::setfill ('0') << std::setw(2) << std::hex << (int)(b * 255.0f);

        std::string result("0x");

        return result += stream.str();
    }

    void colorHSLAToColorRGBA(float H, float S, float L, float A, float& rr, float& gg, float& bb, float& aa)
    {
        H = fmodf(H, 1); // wrap around
        S = MAX(0, MIN(S, 1));
        L = MAX(0, MIN(L, 1));
        A = MAX(0, MIN(A, 1));

        float r = L; // default to gray
        float g = L;
        float b = L;
        float v = (L <= 0.5) ? (L * (1.0 + S)) : (L + S - L * S);

        if (v > 0) {
            float m = L + L - v;
            float sv = (v - m) / v;
            H *= 6.0;
            int sextant = (int)H;
            float fract = H - sextant;
            float vsf = v * sv * fract;
            float mid1 = m + vsf;
            float mid2 = v - vsf;

            switch (sextant) {
                case 0: r = v; g = mid1; b = m; break;
                case 1: r = mid2; g = v; b = m; break;
                case 2: r = m; g = v; b = mid1; break;
                case 3: r = m; g = mid2; b = v; break;
                case 4: r = mid1; g = m; b = v; break;
                case 5: r = v; g = m; b = mid2; break;
            }
        }

        rr = r;
        gg = g;
        bb = b;
        aa = A;
    }
}
