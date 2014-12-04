//
//  LocalStorage.h
//  Mural
//
//  Created by Sean on 12/4/14.
//
//

#ifndef __Mural__LocalStorage__
#define __Mural__LocalStorage__

#include <string>
#include "JavaScript/JavaScript.h"

namespace mural
{
    typedef std::string String;
    class LocalStorage
    {
        String storageFile;
        String data;
    public:
        LocalStorage();
        ~LocalStorage() {}

        const String getData();
        void setData(const String& value);
        void clear();
    };

    // Binding
    int w_LocalStorage_constructor(duk_context *ctx);
    int w_LocalStorage_prototype_getItem(duk_context *ctx);
    int w_LocalStorage_prototype_setItem(duk_context *ctx);
    int w_LocalStorage_prototype_removeItem(duk_context *ctx);
    int w_LocalStorage_prototype_clear(duk_context *ctx);
    int w_LocalStorage_prototype_key(duk_context *ctx);
    
    duk_ret_t js_register_LocalStorage(duk_context *ctx);
}

#endif /* defined(__Mural__LocalStorage__) */
