#pragma once

#include <stdint.h>

namespace chip {

class Index {
public:
    static void write(uint16_t data);
    static uint16_t read();
private:
    Index() {}
    static uint16_t data_;
};

}