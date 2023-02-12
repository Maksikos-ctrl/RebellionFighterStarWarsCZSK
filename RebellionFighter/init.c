#include "init.h"

bool init_sdl(SDL_Window **window, SDL_Renderer **renderer) {
    // 0 == success
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Star wars. Rebellion Fighter!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT, WINDOW_WIDTH, 0);
        
    if (!*window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    *renderer = SDL_CreateRenderer(*window, -1, render_flags);

    if (!*renderer) {
        printf("SDL_CreateRenderer Error: %s");
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }

    return true;
}
