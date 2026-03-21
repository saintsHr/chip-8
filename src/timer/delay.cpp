#include "timer/delay.hpp"

namespace chip::Timer {

uint8_t Delay::data_ = 0x00;

void Delay::write(uint8_t data) {
    data_ = data;
}

void Delay::step() {
    if (data_ > 0x00) data_--;
}

}