#ifdef RESOURCES_H
#define RESOURCES_H
#include <SDL2/SDL.h>


SDL_Texture* load_image(SDL_Renderer *renderer, const char *img_path, SDL_Texture **texture, SDL_Surface *image);
SDL_Texture* load_background(SDL_Renderer *renderer, const char *bg_path, SDL_Texture **background, SDL_Surface *backgroundSurface);

#endif