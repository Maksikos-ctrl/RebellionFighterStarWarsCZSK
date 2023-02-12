#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.h"


SDL_Texture* load_image(SDL_Renderer *renderer, const char *img_path) {
    SDL_Surface* image = IMG_Load(img_path);
    if (!image) {
        printf("IMG_Load Error: %s",IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    return texture;
}


void free_resources(SDL_Texture *texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* load_background(SDL_Renderer *renderer, const char *bg_path) {
    SDL_Surface* backgroundSurface = IMG_Load(bg_path);
    if (!backgroundSurface) {
        printf("IMG_Load Error: %s",IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);



    return texture;
}
