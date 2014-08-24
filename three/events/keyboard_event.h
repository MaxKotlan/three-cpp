#ifndef THREE_EVENTS_KEYBOARD_EVENT_H
#define THREE_EVENTS_KEYBOARD_EVENT_H

#include <three/common.h>
#include <three/events/input_event.h>

namespace three {

#define KEY_SCANCODE_MASK (1<<30)
#define KEY_SCANCODE_TO_KEYCODE(X)  (X | KEY_SCANCODE_MASK)

typedef enum {
    KEY_UNKNOWN = 0,

    KEY_RETURN = '\r',
    KEY_ESCAPE = '\033',
    KEY_BACKSPACE = '\b',
    KEY_TAB = '\t',
    KEY_SPACE = ' ',
    KEY_EXCLAIM = '!',
    KEY_QUOTEDBL = '"',
    KEY_HASH = '#',
    KEY_PERCENT = '%',
    KEY_DOLLAR = '$',
    KEY_AMPERSAND = '&',
    KEY_QUOTE = '\'',
    KEY_LEFTPAREN = '(',
    KEY_RIGHTPAREN = ')',
    KEY_ASTERISK = '*',
    KEY_PLUS = '+',
    KEY_COMMA = ',',
    KEY_MINUS = '-',
    KEY_PERIOD = '.',
    KEY_SLASH = '/',
    KEY_0 = '0',
    KEY_1 = '1',
    KEY_2 = '2',
    KEY_3 = '3',
    KEY_4 = '4',
    KEY_5 = '5',
    KEY_6 = '6',
    KEY_7 = '7',
    KEY_8 = '8',
    KEY_9 = '9',
    KEY_COLON = ':',
    KEY_SEMICOLON = ';',
    KEY_LESS = '<',
    KEY_EQUALS = '=',
    KEY_GREATER = '>',
    KEY_QUESTION = '?',
    KEY_AT = '@',
    /*
       Skip uppercase letters
     */
    KEY_LEFTBRACKET = '[',
    KEY_BACKSLASH = '\\',
    KEY_RIGHTBRACKET = ']',
    KEY_CARET = '^',
    KEY_UNDERSCORE = '_',
    KEY_BACKQUOTE = '`',
    KEY_a = 'a',
    KEY_b = 'b',
    KEY_c = 'c',
    KEY_d = 'd',
    KEY_e = 'e',
    KEY_f = 'f',
    KEY_g = 'g',
    KEY_h = 'h',
    KEY_i = 'i',
    KEY_j = 'j',
    KEY_k = 'k',
    KEY_l = 'l',
    KEY_m = 'm',
    KEY_n = 'n',
    KEY_o = 'o',
    KEY_p = 'p',
    KEY_q = 'q',
    KEY_r = 'r',
    KEY_s = 's',
    KEY_t = 't',
    KEY_u = 'u',
    KEY_v = 'v',
    KEY_w = 'w',
    KEY_x = 'x',
    KEY_y = 'y',
    KEY_z = 'z',

    KEY_CAPSLOCK = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

    KEY_F1 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
    KEY_F2 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
    KEY_F3 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
    KEY_F4 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
    KEY_F5 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
    KEY_F6 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
    KEY_F7 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
    KEY_F8 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
    KEY_F9 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
    KEY_F10 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
    KEY_F11 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
    KEY_F12 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

    KEY_PRINTSCREEN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
    KEY_SCROLLLOCK = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
    KEY_PAUSE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
    KEY_INSERT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
    KEY_HOME = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
    KEY_PAGEUP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
    KEY_DELETE = '\177',
    KEY_END = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
    KEY_PAGEDOWN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
    KEY_RIGHT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
    KEY_LEFT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
    KEY_DOWN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
    KEY_UP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

    KEY_NUMLOCKCLEAR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
    KEY_KP_DIVIDE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
    KEY_KP_MULTIPLY = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
    KEY_KP_MINUS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
    KEY_KP_PLUS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
    KEY_KP_ENTER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
    KEY_KP_1 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
    KEY_KP_2 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
    KEY_KP_3 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
    KEY_KP_4 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
    KEY_KP_5 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
    KEY_KP_6 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
    KEY_KP_7 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
    KEY_KP_8 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
    KEY_KP_9 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
    KEY_KP_0 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
    KEY_KP_PERIOD = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

    KEY_APPLICATION = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
    KEY_POWER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
    KEY_KP_EQUALS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
    KEY_F13 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
    KEY_F14 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
    KEY_F15 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
    KEY_F16 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
    KEY_F17 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
    KEY_F18 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
    KEY_F19 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
    KEY_F20 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
    KEY_F21 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
    KEY_F22 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
    KEY_F23 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
    KEY_F24 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
    KEY_EXECUTE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
    KEY_HELP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
    KEY_MENU = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
    KEY_SELECT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
    KEY_STOP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
    KEY_AGAIN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
    KEY_UNDO = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
    KEY_CUT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
    KEY_COPY = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
    KEY_PASTE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
    KEY_FIND = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
    KEY_MUTE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
    KEY_VOLUMEUP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
    KEY_VOLUMEDOWN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
    KEY_KP_COMMA = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
    KEY_KP_EQUALSAS400 =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

    KEY_ALTERASE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
    KEY_SYSREQ = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
    KEY_CANCEL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
    KEY_CLEAR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
    KEY_PRIOR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
    KEY_RETURN2 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
    KEY_SEPARATOR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
    KEY_OUT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
    KEY_OPER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
    KEY_CLEARAGAIN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
    KEY_CRSEL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
    KEY_EXSEL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

    KEY_KP_00 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
    KEY_KP_000 = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
    KEY_THOUSANDSSEPARATOR =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
    KEY_DECIMALSEPARATOR =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
    KEY_CURRENCYUNIT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
    KEY_CURRENCYSUBUNIT =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
    KEY_KP_LEFTPAREN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
    KEY_KP_RIGHTPAREN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
    KEY_KP_LEFTBRACE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
    KEY_KP_RIGHTBRACE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
    KEY_KP_TAB = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
    KEY_KP_BACKSPACE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
    KEY_KP_A = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
    KEY_KP_B = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
    KEY_KP_C = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
    KEY_KP_D = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
    KEY_KP_E = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
    KEY_KP_F = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
    KEY_KP_XOR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
    KEY_KP_POWER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
    KEY_KP_PERCENT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
    KEY_KP_LESS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
    KEY_KP_GREATER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
    KEY_KP_AMPERSAND = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
    KEY_KP_DBLAMPERSAND =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
    KEY_KP_VERTICALBAR =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
    KEY_KP_DBLVERTICALBAR =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
    KEY_KP_COLON = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
    KEY_KP_HASH = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
    KEY_KP_SPACE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
    KEY_KP_AT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
    KEY_KP_EXCLAM = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
    KEY_KP_MEMSTORE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
    KEY_KP_MEMRECALL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
    KEY_KP_MEMCLEAR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
    KEY_KP_MEMADD = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
    KEY_KP_MEMSUBTRACT =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
    KEY_KP_MEMMULTIPLY =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
    KEY_KP_MEMDIVIDE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
    KEY_KP_PLUSMINUS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
    KEY_KP_CLEAR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
    KEY_KP_CLEARENTRY = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
    KEY_KP_BINARY = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
    KEY_KP_OCTAL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
    KEY_KP_DECIMAL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
    KEY_KP_HEXADECIMAL =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

    KEY_LCTRL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
    KEY_LSHIFT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
    KEY_LALT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
    KEY_LGUI = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
    KEY_RCTRL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
    KEY_RSHIFT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
    KEY_RALT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
    KEY_RGUI = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

    KEY_MODE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

    KEY_AUDIONEXT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
    KEY_AUDIOPREV = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
    KEY_AUDIOSTOP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
    KEY_AUDIOPLAY = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
    KEY_AUDIOMUTE = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
    KEY_MEDIASELECT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
    KEY_WWW = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
    KEY_MAIL = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
    KEY_CALCULATOR = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
    KEY_COMPUTER = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
    KEY_AC_SEARCH = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
    KEY_AC_HOME = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
    KEY_AC_BACK = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
    KEY_AC_FORWARD = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
    KEY_AC_STOP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
    KEY_AC_REFRESH = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
    KEY_AC_BOOKMARKS = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

    KEY_BRIGHTNESSDOWN =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
    KEY_BRIGHTNESSUP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
    KEY_DISPLAYSWITCH = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
    KEY_KBDILLUMTOGGLE =
        KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
    KEY_KBDILLUMDOWN = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
    KEY_KBDILLUMUP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
    KEY_EJECT = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
    KEY_SLEEP = KEY_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP)
} KeyCode;

typedef enum {
    KEY_MOD_NONE = 0x0000,
    KEY_MOD_LSHIFT = 0x0001,
    KEY_MOD_RSHIFT = 0x0002,
    KEY_MOD_LCTRL = 0x0040,
    KEY_MOD_RCTRL = 0x0080,
    KEY_MOD_LALT = 0x0100,
    KEY_MOD_RALT = 0x0200,
    KEY_MOD_LGUI = 0x0400,
    KEY_MOD_RGUI = 0x0800,
    KEY_MOD_NUM = 0x1000,
    KEY_MOD_CAPS = 0x2000,
    KEY_MOD_MODE = 0x4000,
    KEY_MOD_RESERVED = 0x8000
} KeyMod;

#define KEY_MOD_CTRL (KEY_MOD_LCTRL|KEY_MOD_RCTRL)
#define KEY_MOD_SHIFT  (KEY_MOD_LSHIFT|KEY_MOD_RSHIFT)
#define KEY_MOD_ALT  (KEY_MOD_LALT|KEY_MOD_RALT)
#define KEY_MOD_GUI  (KEY_MOD_LGUI|KEY_MOD_RGUI)

class KeyboardEvent : public InputEvent {
public:

  static const char* KEY_PRESS;
  static const char* KEY_UP;
  static const char* KEY_DOWN;

  KeyboardEvent( const EventType& type, unsigned int timestamp, unsigned int key, bool repeat = false )
    : InputEvent( type, timestamp ),
      key( key ),
      repeat( repeat ) {}

  unsigned int key;

  bool repeat;

};

const char* KeyboardEvent::KEY_PRESS = "keyPress";
const char* KeyboardEvent::KEY_UP = "keyUp";
const char* KeyboardEvent::KEY_DOWN = "keyDown";

} // end namespace three

#endif // THREE_EVENTS_KEYBOARD_EVENT_H
