#pragma once

#include <stdint.h>

namespace chip::Timer {

class Sound {
public:
    static void step();
    static void write(uint16_t data);
private:
    Sound() {}
    static uint16_t data_;
};

}