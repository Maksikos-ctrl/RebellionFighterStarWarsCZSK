#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 1280
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 80
#define width 100
#define height 600

#define SPEED 350

bool init_sdl(SDL_Window **window, SDL_Renderer **renderer);

#endif
