/* 

All stuff related to animation



IN Graphics, origin is LEFT TOP CORNER

*/

*/



#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>


#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

#define SCROLL_SPEED 300

int main(void) {

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
    SDL_Surface* image = IMG_Load("skywing.png");

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

    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } 

    // struct to hold the pos and size of the sprite
    SDL_Rect dest;

    // get the dimensions of the textures
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    // pos the sprite at the bottom center of the window
    // origin is the top left corner, +y is down

    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    // require float resol for y pos

    float y_pos = WINDOW_HEIGHT;


    // require float resolution for y pos

    while (dest.y >= -dest.h) {
        // clear the window
        SDL_RenderClear(renderer);

        // set the y pos in the struct

        dest.y = (int) y_pos;

        // draw the image to the window
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);

        // update sprite pos

        y_pos -= (float) SCROLL_SPEED / 60;

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }


    // message on the screen

    printf("Press any key to continue...");

    // clear the window
    SDL_RenderClear(renderer);

    // draw the image to the window
    
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    // double buffering is when you draw to a "back buffer" that isn't displayed, then you swap the back buffer with the front buffer (the one that is displayed) so that what you drew appears on the screen. This prevents flickering
    SDL_RenderPresent(renderer);


    

    // clean up resources before exiting
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}