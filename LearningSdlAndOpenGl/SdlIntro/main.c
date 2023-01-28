/*

Init Sdl



*/



#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


int main(void) {
    // attempt to initialize SDL
    // 0 == success
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Seems it works!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // load the image into memory using SDL_image library function
    // can u change the size of the image
    // how to set my img not on full size

    SDL_Surface* image = IMG_Load("hello.png");
    // SDL_Surface* image = IMG_Load("plane.png");

    SDL_Surface* background = IMG_Load("starfield.png");
    

    if (!image) {
        printf("IMG_Load Error: %s");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }     

    // load the image data into the graphics hardware's memory

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    // Create a texture for the background image
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, background);
    SDL_FreeSurface(background);

    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } 

    
    // clear the window
    SDL_RenderClear(renderer);

    // draw the image to the window
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    // double buffering is when you draw to a "back buffer" that isn't displayed, then you swap the back buffer with the front buffer (the one that is displayed) so that what you drew appears on the screen. This prevents flickering
    SDL_RenderPresent(renderer);


    SDL_Delay(6000);

    // clean up resources before exiting
    SDL_DestroyTexture(texture);
    SDL_RenderCopy(renderer, texture, background_texture, &dest);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}






