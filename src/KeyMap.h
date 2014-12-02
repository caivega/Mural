//
//  KeyMap.h
//  Mural
//
//  Created by Sean on 12/1/14.
//
//

#ifndef Mural_KeyMap_h
#define Mural_KeyMap_h

#include "cinder/app/KeyEvent.h"

#include <map>
#include <string>

using namespace ci::app;

static std::map<int, int> CiToKeyCodeMap = {
    { KeyEvent::KEY_COMMA, 188 }, // Comma
    { KeyEvent::KEY_PERIOD, 190 }, // Period
    { KeyEvent::KEY_SEMICOLON, 186 }, // Semicolon
    { KeyEvent::KEY_QUOTE, 222 }, // Quote
    { KeyEvent::KEY_LEFTBRACKET, 219 }, // BracketLeft
    { KeyEvent::KEY_RIGHTBRACKET, 221 }, // BracketRight
    { KeyEvent::KEY_BACKQUOTE, 192 }, // Backquote
    { KeyEvent::KEY_BACKSLASH, 220 }, // Backslash
    { KeyEvent::KEY_MINUS, 189 }, // Minuse
    { KeyEvent::KEY_KP_MINUS, 189 }, // Minuse
    { KeyEvent::KEY_EQUALS, 187 }, // Equal
    { KeyEvent::KEY_LALT, 18 }, // AltLeft
    { KeyEvent::KEY_RALT, 18 }, // AltRight
    { KeyEvent::KEY_CAPSLOCK, 20 }, // CapsLock
    { KeyEvent::KEY_LCTRL, 17 }, // ControlLeft
    { KeyEvent::KEY_RCTRL, 17 }, // ControlRight
    { KeyEvent::KEY_LMETA, 91 }, // OSLeft
    { KeyEvent::KEY_RMETA, 92 }, // OSRight
    { KeyEvent::KEY_LSHIFT, 16 }, // ShiftLeft
    { KeyEvent::KEY_RSHIFT, 16 }, // ShiftRight
    { KeyEvent::KEY_RETURN, 13 }, // Enter
    { KeyEvent::KEY_SPACE, 32 }, // Space
    { KeyEvent::KEY_TAB, 9}, // Tab
    { KeyEvent::KEY_DELETE, 46 }, // Delete
    { KeyEvent::KEY_END, 35 }, // End
    { KeyEvent::KEY_HELP, 45 }, // Help
    { KeyEvent::KEY_HOME, 36 }, // Home
    { KeyEvent::KEY_INSERT, 45 }, // Insert
    { KeyEvent::KEY_PAGEDOWN, 34 }, // PageDown
    { KeyEvent::KEY_PAGEUP, 33 }, // PageUp
    { KeyEvent::KEY_DOWN, 40 }, // ArrowDown
    { KeyEvent::KEY_LEFT, 37 }, // ArrowLeft
    { KeyEvent::KEY_RIGHT, 39 }, // ArrowRight
    { KeyEvent::KEY_UP, 38 }, // ArrowUp
    { KeyEvent::KEY_ESCAPE, 27 }, // Escape
    { KeyEvent::KEY_PRINT, 44, }, // PrintScreen
    { KeyEvent::KEY_SCROLLOCK, 145 }, // ScrollLock
    { KeyEvent::KEY_PAUSE, 19 }, // Pause
    { KeyEvent::KEY_BACKSPACE, 8 }, // Backspace
    { KeyEvent::KEY_SLASH, 191 }, // Slash
};
static std::map<int, std::string> CiToCodeMap = {
    { KeyEvent::KEY_COMMA, "Comma" },
    { KeyEvent::KEY_PERIOD, "Period" },
    { KeyEvent::KEY_SEMICOLON, "Semicolon" },
    { KeyEvent::KEY_QUOTE, "Quote" },
    { KeyEvent::KEY_LEFTBRACKET, "BracketLeft" },
    { KeyEvent::KEY_RIGHTBRACKET, "BracketRight" },
    { KeyEvent::KEY_BACKQUOTE, "Backquote" },
    { KeyEvent::KEY_BACKSLASH, "Backslash" },
    { KeyEvent::KEY_MINUS, "Minuse" },
    { KeyEvent::KEY_KP_MINUS, "Minuse" },
    { KeyEvent::KEY_EQUALS, "Equal" },
    { KeyEvent::KEY_LALT, "AltLeft" },
    { KeyEvent::KEY_RALT, "AltRight" },
    { KeyEvent::KEY_CAPSLOCK, "CapsLock" },
    { KeyEvent::KEY_LCTRL, "ControlLeft" },
    { KeyEvent::KEY_RCTRL, "ControlRight" },
    { KeyEvent::KEY_LMETA, "OSLeft" },
    { KeyEvent::KEY_RMETA, "OSRight" },
    { KeyEvent::KEY_LSHIFT, "ShiftLeft" },
    { KeyEvent::KEY_RSHIFT, "ShiftRight" },
    { KeyEvent::KEY_RETURN, "Enter" },
    { KeyEvent::KEY_SPACE, "Space" },
    { KeyEvent::KEY_TAB, "Tab" },
    { KeyEvent::KEY_DELETE, "Delete" },
    { KeyEvent::KEY_END, "End" },
    { KeyEvent::KEY_HELP, "Help" },
    { KeyEvent::KEY_HOME, "Home" },
    { KeyEvent::KEY_INSERT, "Insert" },
    { KeyEvent::KEY_PAGEDOWN, "PageDown" },
    { KeyEvent::KEY_PAGEUP, "PageUp" },
    { KeyEvent::KEY_DOWN, "ArrowDown" },
    { KeyEvent::KEY_LEFT, "ArrowLeft" },
    { KeyEvent::KEY_RIGHT, "ArrowRight" },
    { KeyEvent::KEY_UP, "ArrowUp" },
    { KeyEvent::KEY_ESCAPE, "Escape" },
    { KeyEvent::KEY_PRINT, "PrintScreen" },
    { KeyEvent::KEY_SCROLLOCK, "ScrollLock" },
    { KeyEvent::KEY_PAUSE, "Pause" },
    { KeyEvent::KEY_BACKSPACE, "Backspace" },
    { KeyEvent::KEY_SLASH, "Slash" },
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

    // F1-F24
    for (int i = 282; i < 297; ++i) {
        CiToKeyCodeMap[i] = i - 170;
        CiToCodeMap[i] = "F"; CiToCodeMap[i] += std::to_string(i - 281);
    }
}

#endif
