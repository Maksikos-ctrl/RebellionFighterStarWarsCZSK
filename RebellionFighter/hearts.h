#ifndef HEARTS_H
#define HEARTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* init_heart1(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *heart_image1, SDL_Window *window);
SDL_Texture* init_heart2(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *heart_image2, SDL_Window *window);
SDL_Texture* init_heart3(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *heart_image3, SDL_Window *window);


#endif