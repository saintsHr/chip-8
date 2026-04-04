#pragma once

#define KEY_AMOUNT 16

namespace chip::IO {

class Input {
public:
    static void setKey(int key, bool pressed);
    static bool getKey(int key);
    static int  getPressedKey();
private:
    Input() {};
    static bool keys_[KEY_AMOUNT];
};

}