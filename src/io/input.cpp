#include "io/input.hpp"

namespace chip::IO {

bool Input::keys_[16] = {0};

void Input::setKey(int key, bool pressed) {
    keys_[key] = pressed;
}

bool Input::getKey(int key) {
    return keys_[key];
}

}