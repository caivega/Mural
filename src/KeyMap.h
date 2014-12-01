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

static std::map<int, int> CiToKeyCodeMap = {
    { 44, 188 }, // Comma
    { 46, 190 }, // Period
    { 59, 186 }, // Semicolon
    { 39, 222 }, // Quote
    { 91, 219 }, // BracketLeft
    { 93, 221 }, // BracketRight
    { 96, 192 }, // Backquote
    { 92, 220 }, // Backslash
    { 45, 189 }, // Minuse
    { 61, 187 }, // Equal
};
static std::map<int, std::string> CiToCodeMap = {
    { 44, "Comma" },
    { 46, "Period" },
    { 59, "Semicolon" },
    { 39, "Quote" },
    { 91, "BracketLeft" },
    { 93, "BracketRight" },
    { 96, "Backquote" },
    { 92, "Backslash" },
    { 45, "Minuse" },
    { 61, "Equal" },
};

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
