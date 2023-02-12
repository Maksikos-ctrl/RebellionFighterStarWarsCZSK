#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "hearts.h"

#include "hearts.h"

bool init_heart1(SDL_Renderer *renderer, SDL_Texture *heart) {
    heart = NULL;
    

    SDL_Surface *heartSurface = IMG_Load("assets/fullHeart.png");
    if (!heartSurface ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        return false;
    }

    heart = SDL_CreateTextureFromSurface(renderer, heartSurface);
    SDL_FreeSurface(heartSurface);

    if (!heart) {
        printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        return false;
    }

    SDL_Surface *heartSurface2 = IMG_Load("assets/fullHeart.png");
    if (!heartSurface2 ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyTexture(heart);
        SDL_DestroyRenderer(renderer);
        return false;
    }
    

    return true;
}


bool init_heart2(SDL_Renderer *renderer, SDL_Texture *heart2) {
    
    heart2 = NULL;
   
    SDL_Surface *heartSurface2 = IMG_Load("assets/fullHeart.png");
    if (!heartSurface2 ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyTexture(heart);
        SDL_DestroyRenderer(renderer);
        return false;
    }
    heart2 = SDL_CreateTextureFromSurface(renderer, heartSurface2);
    SDL_FreeSurface(heartSurface2);

    if (!heart2) {
        printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
        SDL_DestroyTexture(heart);
        SDL_DestroyRenderer(renderer);
        return false;
    }

    return true;
}

bool init_heart3(SDL_Renderer *renderer, SDL_Texture *heart3) {
    heart3 = NULL;

    SDL_Surface *heartSurface3 = IMG_Load("assets/fullHeart.png");
    if (!heartSurface3 ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyTexture(heart);
        SDL_DestroyTexture(heart2);
        SDL_DestroyRenderer(renderer);
        return false;
    }
    heart3 = SDL_CreateTextureFromSurface(renderer, heartSurface3);
    SDL_FreeSurface(heartSurface3);

    if (!heart3) {
        printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
        SDL_DestroyTexture(heart);
        SDL_DestroyTexture(heart2);
        SDL_DestroyRenderer(renderer);
        return false;
    }

    return true;
}