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
    auto ctx = new mural::CanvasContext();

    img->setSrc("media/coin.png");
    img->loadCallback = [=] {
        printf("img loaded!");

        ctx->drawImage(img, 32, 32);
        ctx->drawImage(img, 32, 120, 40, 40);
        ctx->drawImage(img, 0, 0, 36, 36, 32, 240, 36, 36);
    };
}

#endif
