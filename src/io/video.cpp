#include "io/video.hpp"

namespace chip::IO {

bool Video::framebuffer_[32][64] = {0};

void Video::clear(bool value) {
    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            framebuffer_[y][x] = value;
        }
    }
}

void Video::setPixel(int x, int y, bool value) {
    if (x >= 64|| y >= 32) return;
    framebuffer_[y][x] = value;
}

bool Video::getPixel(int x, int y) {
    if (x >= 64|| y >= 32) return false;
    return framebuffer_[y][x];
}

}