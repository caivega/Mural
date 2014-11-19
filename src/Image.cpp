//
//  Image.cpp
//  CinderCanvas
//
//  Created by Sean on 11/16/14.
//
//

#include "Image.h"

using namespace ci;

namespace mural
{
    Image::Image():
        loading(false),
        loadCompleted(false),
        jsObjectRef(0),
        loadCallback(nullptr)
    {}

    gl::TextureRef Image::getTexture()
    {
        return texture;
    }

    Image::~Image()
    {
        loadCallback = nullptr;
    }

    int Image::getWidth()
    {
        if (!this->loadCompleted) {
            return 0;
        }
        return data.getWidth();
    }

    int Image::getHeight()
    {
        if (!this->loadCompleted) {
            return 0;
        }
        return data.getHeight();
    }

    bool Image::getComplete()
    {
        return loadCompleted;
    }

    void Image::setSrc(const std::string &path)
    {
        if (this->loading) {
            return;
        }

        this->path = path;

        this->beginLoad();
    }

    std::string Image::getSrc()
    {
        return this->path;
    }

    void Image::beginLoad()
    {
        this->loading = true;

        AssetManager::Options opts;
        opts.watch(false).asynchronous(true);

        AssetManager::load<ImageSourceRef>(
            this->path,
            [](DataSourceRef dataSourceRef) {
                ImageSourceRef imageSource = loadImage(dataSourceRef);
                return imageSource;
            },
            [&](ImageSourceRef imgSourceRef) {
                this->data = Surface(imgSourceRef);
                this->texture = gl::Texture::create(this->data);

                this->loading = false;
                this->loadCompleted = true;

                if (this->loadCallback) {
                    this->loadCallback();
                }
            },
            opts
        );
    }
}
