#pragma once

#include <stdint.h>

namespace chip {

class Program {
public:
    static void write(uint16_t data);
    static uint16_t read();
private:
    Program() {}
    static uint16_t data_;
};

}