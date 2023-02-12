#ifndef INIT_H
#define INIT_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


bool font_init(TTF_Font **font, SDL_Renderer *renderer);

#endif