//
//  Image.h
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#ifndef __CinderCanvas__Image__
#define __CinderCanvas__Image__

#include "Global.h"

namespace mural
{
    class Image
    {
        std::string path;

        bool loading;
        bool loadCompleted;
    public:
        Image();
        ~Image();

        int jsObjectRef;
        std::function<void()> loadCallback;

        ci::Surface data;
        ci::gl::TextureRef texture;

        int getWidth();
        int getHeight();
        bool getComplete();

        /**
         * Set image source and load (async).
         * The path is based at app bundle "Resources" folder
         */
        void setSrc(const std::string& path);
        std::string getSrc();

    private:
        void beginLoad();
    };
}

#endif /* defined(__CinderCanvas__Image__) */
