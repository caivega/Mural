//
//  KeyMap.h
//  Mural
//
//  Created by Sean on 12/1/14.
//
//

#ifndef Mural_KeyMap_h
#define Mural_KeyMap_h

#include <map>
#include <string>

static std::map<int, int> KeyCodeMap;
static std::map<int, std::string> CodeMap;

void initKeyCodeMap()
{
    // Digit
    for (int i = 48; i < 48 + 10; ++i) {
        KeyCodeMap[i] = i;
        CodeMap[i] = "Digit"; CodeMap[i] += i;
    }

    // a-z
    for (int i = 97; i < 97 + 26; ++i) {
        KeyCodeMap[i] = i - 32;
        CodeMap[i] = "Key"; CodeMap[i] += (i + ('A' - 'a'));
    }
}

#endif
