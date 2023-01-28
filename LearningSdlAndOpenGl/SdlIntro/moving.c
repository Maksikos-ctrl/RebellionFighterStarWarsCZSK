/*

moving.c is a- Handles the window close event

*/


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>



#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480


// speed in pixels/second

#define MOVE_SPEED 300

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
    SDL_Surface* image = IMG_Load("hello.png");

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
    dest.w /= 4;
    dest.h /= 4;


    // start sprite in the center of the screen
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;

    // we give sprite init velocity
    float x_vel = MOVE_SPEED;
    float y_vel = MOVE_SPEED;

    // set 1 when window close button is pressed
    int close_requested = 0;

    // anim loop
    while (!close_requested) {
        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close_requested = 1;
            }
        }

       // collision detection with bounds
        if (x_pos <= 0)
        {
            x_pos = 0;
            x_vel = -x_vel;
        }
        else if (x_pos >= WINDOW_WIDTH - dest.w) 
        {
            x_pos = WINDOW_WIDTH - dest.w;
            x_vel = -x_vel;
        }

        if (y_pos <= 0)
        {
            y_pos = 0;
            y_vel = -y_vel;
        }
        else if (y_pos >= WINDOW_HEIGHT - dest.h)
        {
            y_pos = WINDOW_HEIGHT - dest.h;
            y_vel = -y_vel;
        }


        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        
        // clear the window
        SDL_RenderClear(renderer);

        // draw the image to the window
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_RenderPresent(renderer);

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