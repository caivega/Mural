//
//  LoadImage.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef CinderCanvas_LoadImage_h
#define CinderCanvas_LoadImage_h

#include "Image.h"

void LoadImage()
{
    auto img = new mural::Image();

    img->setSrc("media/title.png");
    img->loadCallback = [=] {
        printf("img loaded!");

        gl::draw(img->texture);
    };
}

#endif
