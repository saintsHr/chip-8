#pragma once

namespace chip::IO {

class Input {
public:
    static void setKey(int key, bool pressed);
    static bool getKey(int key);
private:
    Input() {};
    static bool keys_[16];
};

}