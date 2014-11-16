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
        path(""),
        loading(false),
        loadCompleted(false),
        jsObjectRef(0),
        loadCallback(nullptr)
    {}

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

        this->path += "../Resources/";
        this->path += path;

        printf("resolved path is %s\n", this->path.c_str());

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
            path,
            [](DataSourceRef dataSourceRef) {
                ImageSourceRef imageSource = loadImage(dataSourceRef);
                return imageSource;
            },
            [&](ImageSourceRef imgSourceRef) {
                this->data = Surface(imgSourceRef);
                this->texture = gl::Texture::create(this->data);

                this->loading = false;
                this->loadCompleted = true;

                OperationQueue::defaultQueue().addBlockOperation(this->loadCallback);
            },
            opts
        );
    }
}
