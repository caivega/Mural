//
//  JavaScriptView.h
//  CinderCanvas
//
//  Created by Sean on 11/9/14.
//
//

#ifndef __CinderCanvas__JavaScriptView__
#define __CinderCanvas__JavaScriptView__

#include "Global.h"

#define MURAL_VERSION "0.1"
#define MURAL_SHIM_JS "scripts/shim.js"
#define MURAL_BOOT_JS "scripts/mural.js"

namespace mural
{

    class JavaScriptView
    {
        duk_context *jsGlobalContext;

    public:
        int width, height;
        
        String lang;
        
        JavaScriptView(int width, int height, const String& title);
        ~JavaScriptView();
        
        // Methods
        void loadScriptAtPath(const String& path);
        void boot();

        // Event callbacks

    private:
        void defineProperties();
    };

}

#endif /* defined(__CinderCanvas__JavaScriptView__) */
