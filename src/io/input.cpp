#include "io/input.hpp"

namespace chip::IO {

bool Input::keys_[KEY_AMOUNT] = {0};

void Input::setKey(int key, bool pressed) {
    if (key > KEY_AMOUNT) return;
    if (key < 0x0) return;
    keys_[key] = pressed;
}

bool Input::getKey(int key) {
    if (key > KEY_AMOUNT) return false;
    if (key < 0x0) return false;
    return keys_[key];
}

int Input::getPressedKey() {
    for (int i = 0; i < KEY_AMOUNT; i++) {
        if (getKey(i)) return i;
    }
    return -1;
}

}