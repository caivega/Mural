//
//  Renderable.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef CinderCanvas_Renderable_h
#define CinderCanvas_Renderable_h

namespace mural
{
    struct Renderable
    {
        virtual ci::gl::TextureRef getTexture() = 0;
        virtual bool isRenderable() { return true; }
    };
}

#endif
