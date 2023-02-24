#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "hearts.h"



SDL_Texture* init_heart1(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *image, SDL_Window *window) {

    if (image == NULL) {
        printf("Failed to load heart image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if (!*texture) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    return *texture;


 

    
}


SDL_Texture* init_heart2(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *image, SDL_Window *window) {
    
    if (image == NULL) {
        printf("Failed to load heart image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if (!*texture) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    return *texture;


    
}

SDL_Texture* init_heart3(SDL_Renderer *renderer, const char *heart_path, SDL_Texture **texture, SDL_Surface *image, SDL_Window *window) {
    
    if (image == NULL) {
        printf("Failed to load heart image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if (!*texture) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    return *texture;


}