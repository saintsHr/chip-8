#pragma once

#include <stdint.h>

namespace chip::Timer {

class Delay {
public:
    static void step();
    static void write(uint16_t data);
private:
    Delay() {}
    static uint16_t data_;
};

}