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

    img->setSrc("media/coin.png");
    img->loadCallback = [=] {
        printf("img loaded!");

        // Reset color so that the texture draws correctly
        gl::color(1, 1, 1);
        gl::draw(img->texture);
    };
}

#endif
