#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "init.h"
#include "resources.h"




void load_image(SDL_Renderer *renderer, const char *img_path, SDL_Texture **image, SDL_Surface *imageSurface, SDL_Window *window) {

    if (imageSurface == NULL) {
        printf("Failed to load image\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    *image= SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);


    if (!*image) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        // SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }


    

    
}



void load_background(SDL_Renderer *renderer, const char *bg_path, SDL_Texture **background, SDL_Surface *backgroundSurface, SDL_Window *window) {

    if (backgroundSurface == NULL) {
        printf("Failed to load background surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }

    *background = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

   
    if (!*background) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        exit(1);
    }



   
}
