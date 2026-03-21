#pragma once

#include <stdint.h>

namespace chip::Timer {

class Sound {
public:
    static void step();
    static void write(uint8_t data);
private:
    Sound() {}
    static uint8_t data_;
};

}