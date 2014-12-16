//
//  ImageData.h
//  Mural
//
//  Created by Sean on 12/16/14.
//
//

#ifndef __Mural__ImageData__
#define __Mural__ImageData__

#include "JavaScript/JavaScript.h"

namespace mural
{
    struct ImageData
    {
        int width, height;
        ci::Surface pixels;
    };
}

#endif /* defined(__Mural__ImageData__) */
