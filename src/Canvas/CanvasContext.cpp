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

        float aa = 0.0f, bb = 0.0f, cc = 0.0f, dd = 0.0f;
        stringToColorRGBA("#abc", aa, bb, cc, dd);
        printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
        stringToColorRGBA("#abcdef", aa, bb, cc, dd);
        printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
        stringToColorRGBA("rgb(0, 255, 0)", aa, bb, cc, dd);
        printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
        stringToColorRGBA("rgba(120, 60, 30, 0.6)", aa, bb, cc, dd);
        printf("color: %f, %f, %f, %f\n", aa, bb, cc, dd);
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
    }
}
