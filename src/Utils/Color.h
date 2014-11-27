//
//  Color.h
//  Mural
//
//  Created by Sean on 11/27/14.
//
//

#ifndef Mural_Color_h
#define Mural_Color_h

namespace mural
{
    void colorHSLAToColorRGBA(float H, float S, float L, float A, float& rr, float& gg, float& bb, float& aa);
    void stringToColorRGBA(const std::string& color, float& r, float& g, float& b, float& a);
    std::string colorRGBAToString(float r, float g, float b);
}

#endif
