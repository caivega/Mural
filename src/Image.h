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
#include "Renderable.h"

namespace mural
{
    class Image : public Renderable
    {
        std::string path;

        bool loading;
        bool loadCompleted;

        ci::gl::TextureRef texture;
    public:
        int jsObjectRef;
        std::function<void()> loadCallback;

        ci::Surface data;

        Image();
        ~Image();

        ci::gl::TextureRef getTexture() override;

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
