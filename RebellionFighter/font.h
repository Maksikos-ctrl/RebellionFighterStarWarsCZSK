#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>


bool font_init(TTF_Font **font, SDL_Renderer *renderer);
bool load_text(SDL_Renderer *renderer, TTF_Font **font, SDL_Texture **text, const char *str, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


#endif