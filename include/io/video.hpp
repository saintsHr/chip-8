#pragma once

#include <stdint.h>

namespace chip::IO {

class Video {
public:
    static void clear(bool value);
    static void setPixel(uint8_t x, uint8_t y, bool value);
    static bool getPixel(uint8_t x, uint8_t y);
private:
    Video() {}
    static bool framebuffer_[32][64];
};

}