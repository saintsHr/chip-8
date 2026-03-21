#pragma once

#include <stdint.h>

namespace chip {

class Stack {
public:
    static void push(uint16_t value);
    static uint16_t pop();

private:
    Stack() {}
    static uint16_t data_[16];
    static uint8_t sp_;
};

}