#include "common.hpp"

#include <SDL2/SDL.h>

#define PIXEL_SIZE    16

int main() {
    // --- inits SDL2 ---
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    // --- creates window ---
        SDL_Window* window = SDL_CreateWindow(
        "CHIP-8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        64 * PIXEL_SIZE,
        32 * PIXEL_SIZE,
        0
    );

    // --- inits renderer ---
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    // --- main loop ---
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 64; ++x) {
                if (chip::IO::Video::getPixel(x, y)) {
                    SDL_Rect r = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}