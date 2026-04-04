#pragma once

namespace chip::IO {

class Video {
public:
    static void clear(bool value);
    static void setPixel(int x, int y, bool value);
    static bool getPixel(int x, int y);
    static bool xorPixel(int x, int y);
private:
    Video() {}
    static bool framebuffer_[32][64];
};

}