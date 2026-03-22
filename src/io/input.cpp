#include "io/input.hpp"

namespace chip::IO {

bool Input::keys_[16] = {0};

void Input::setKey(int key, bool pressed) {
    if (key > 0xF) return;
    if (key < 0x0) return;
    keys_[key] = pressed;
}

bool Input::getKey(int key) {
    if (key > 0xF) return false;
    if (key < 0x0) return false;
    return keys_[key];
}

}