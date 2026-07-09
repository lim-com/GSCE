//
// Created by lim on 08.07.2026.
//

#define SDL_MAIN_HANDLED
#include "test.h"
#include <SDL.h>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool running = true;
Uint8 color = 0;
bool peak = false;



void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
        }
    }

    if (color >= 255) peak = true;
    if (color <= 0) peak = false;

    color = peak ? color -= 1 : color += 1;

    if (color > 255) color = 255;
    if (color < 0) color = 0;

    //std::cout << "color = " << color << std::endl;


    SDL_SetRenderDrawColor(renderer, color, 0, 0, 250);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

}

int main() {
    SDL_SetMainReady();
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");
    SDL_Init(SDL_INIT_VIDEO);



    window = SDL_CreateWindow("GSCE Debug Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, true); // 0 = использовать requestAnimationFrame, 1 = simulate infinite loop
#else
    while (running) {
        mainLoop();
    }
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}