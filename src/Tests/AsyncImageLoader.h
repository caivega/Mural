//
//  AsyncImageLoader.h
//  CinderCanvas
//
//  Created by Sean on 11/15/14.
//
//

#ifndef CinderCanvas_AsyncImageLoader_h
#define CinderCanvas_AsyncImageLoader_h

void AsyncImageLoader()
{
    // Load the image in a separated thread and returns the ImageSourceRef
    auto asyncLoad = [](DataSourceRef dataSource) {
        ImageSourceRef imageSource = loadImage(dataSource);
        return imageSource;
    };

    // The second callback is executed in the main thread so any OpenGL resources can be created here.
    auto textureCreation = [&](ImageSourceRef imageSource) {
        printf("img loaded\n");
        gl::draw(imageSource, Vec2f(0, 0));
    };

    AssetManager::load<ImageSourceRef>("../Resources/media/title.png", asyncLoad, textureCreation);
}

#endif
