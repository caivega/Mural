//
//  Color.cpp
//  Mural
//
//  Created by Sean on 11/27/14.
//
//

#include <sstream>

namespace mural
{
    /* Macros for min/max. */
#ifndef MIN
#define MIN(a, b) (((a)<(b))?(a):(b))
#endif /* MIN */
#ifndef MAX
#define MAX(a, b) (((a)>(b))?(a):(b))
#endif /* MAX */

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
}
