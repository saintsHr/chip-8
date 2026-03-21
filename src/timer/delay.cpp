#include "timer/delay.hpp"

namespace chip::Timer {

uint16_t Delay::data_ = 0x0000;

void Delay::write(uint16_t data) {
    data_ = data;
}

void Delay::step() {
    if (data_ > 0x0000) data_--;
}

}