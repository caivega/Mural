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
        virtual bool isRenderable() { return true; }
    };
}

#endif
