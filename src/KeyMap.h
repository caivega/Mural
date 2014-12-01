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

static std::map<int, int> CiToKeyCodeMap;
static std::map<int, std::string> CiToCodeMap;

void initKeyCodeMap()
{
    // Digit
    for (int i = 48; i < 48 + 10; ++i) {
        CiToKeyCodeMap[i] = i;
        CiToCodeMap[i] = "Digit"; CiToCodeMap[i] += i;
    }

    // a-z
    for (int i = 97; i < 97 + 26; ++i) {
        CiToKeyCodeMap[i] = i - 32;
        CiToCodeMap[i] = "Key"; CiToCodeMap[i] += (i + ('A' - 'a'));
    }
}

#endif
