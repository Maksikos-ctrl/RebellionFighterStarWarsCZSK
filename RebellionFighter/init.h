#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 580
#define WINDOW_HEIGHT 960

bool init_sdl(SDL_Window **window, SDL_Renderer **renderer);

#endif
