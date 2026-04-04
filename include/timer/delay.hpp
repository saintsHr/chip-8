#pragma once

#include <stdint.h>

namespace chip::Timer {

class Delay {
public:
    static void step();
    static void write(uint8_t data);
    static uint16_t get();
private:
    Delay() {}
    static uint8_t data_;
};

}