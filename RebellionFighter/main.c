/*

this file was created for the purpose of handling keyboard input

*/


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_ttf.h>
#include "bullets.h"
#include <stdbool.h>
#include <math.h>

#define WINDOW_HEIGHT 960
#define WINDOW_WIDTH 580
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 80
#define width 100
#define height 600

#define SPEED 350






// speed in pixels/second


// void update_fps(int *frame_count) {
//     (*frame_count)++;
// }






int main(int argc, char *argv[]) {
     // 0 == success
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Star wars. Rebellion Fighter!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT, WINDOW_WIDTH, 0);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

   
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

  
    SDL_Surface* image = IMG_Load("assets/pngwing.png");

    if (!image) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }     

   

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } 
    
  
    SDL_Surface* backgroundSurface = IMG_Load("assets/pikrepo.jpg");
    if (!backgroundSurface ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } 
   
    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (!background) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

   
    if (TTF_Init() != 0) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

   
    TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 14);
    if (font == NULL) {
        printf("Error opening font: %s\n", TTF_GetError());
        return 1;
    }

    

    
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);

  
    int w, h;
    TTF_SizeText(font, "Score", &w, &h);


   
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Score", color);
    if (surface == NULL) {
        printf("Error rendering text: %s\n", TTF_GetError());
        return 1;
    }


    SDL_Texture* text= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (text== NULL) {
        printf("Error creating text: %s\n", SDL_GetError());
        return 1;
    }




    SDL_Texture *heart, *heart2, *heart3;
  
    SDL_Surface *heartSurface = IMG_Load("assets/fullHeart.png");
    if (!heartSurface ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    heart = SDL_CreateTextureFromSurface(renderer, heartSurface);
    SDL_FreeSurface(heartSurface);


 
    SDL_Surface *heartSurface2 = IMG_Load("assets/fullHeart.png");
    if (!heartSurface2 ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    heart2 = SDL_CreateTextureFromSurface(renderer, heartSurface2);
    SDL_FreeSurface(heartSurface2);


    SDL_Surface *heartSurface3 = IMG_Load("assets/fullHeart.png");
    if (!heartSurface3 ) {
        printf("IMG_Load Error: %s",IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    heart3 = SDL_CreateTextureFromSurface(renderer, heartSurface3);
    SDL_FreeSurface(heartSurface3);

  
    int frame_rate = 0, frame_start = SDL_GetTicks();
   
    int elapsed_time = SDL_GetTicks() - frame_start;
    if (elapsed_time > 0) {
        frame_rate = 1000 / elapsed_time;
    } else {
        frame_rate = 60; 
    }

      

    char frame_rate_buffer[50];
    sprintf(frame_rate_buffer, "FPS: %d", frame_rate); 

    TTF_Font* fps_font = TTF_OpenFont("assets/arial.ttf", 14);
    if (fps_font == NULL) {
        printf("Error opening font: %s\n", TTF_GetError());
        return 1;
    }

    
    TTF_SetFontStyle(fps_font, TTF_STYLE_BOLD);

    int w1, h1;
    TTF_SizeText(fps_font, frame_rate_buffer, &w1, &h1);


    
    SDL_Color fps_color = {0, 255, 0};
    SDL_Surface* fps_surface = TTF_RenderText_Solid(fps_font, frame_rate_buffer, fps_color);
    if (fps_surface == NULL) {
        printf("Error rendering text: %s\n", TTF_GetError());
        return 1;
    }

    
    SDL_Texture* fps_text= SDL_CreateTextureFromSurface(renderer, fps_surface);
    SDL_FreeSurface(fps_surface);
    if (fps_text== NULL) {
        printf("Error creating text: %s\n", SDL_GetError());
        return 1;
    }

   

       
  
    SDL_Rect img_dest;

    SDL_Rect text_dest;
    SDL_Rect heart_dest, heart2_dest, heart3_dest;
    SDL_Rect fps_dest;

    text_dest.x = 10;
    text_dest.y = 10;

    img_dest.x = 100;
    img_dest.y = 100;

    
    heart_dest.x = width + heart_dest.w + 800;
    heart_dest.y = 0;

    heart2_dest.x = heart_dest.x + heart_dest.w - 30;
    heart2_dest.y = 0;

    heart3_dest.x = heart2_dest.x + heart2_dest.w - 30;
    heart3_dest.y = 0;


    fps_dest.x = 10;
    fps_dest.y = height - h1;
    fps_dest.w = w1;
    fps_dest.h = h1;
    


  



   
    SDL_QueryTexture(text, NULL, NULL, &text_dest.w, &text_dest.h);
    SDL_QueryTexture(texture, NULL, NULL, &img_dest.w, &img_dest.h);
    SDL_QueryTexture(fps_text, NULL, NULL, &fps_dest.w, &fps_dest.h);
    SDL_QueryTexture(heart, NULL, NULL, &heart_dest.w, &heart_dest.h);
    SDL_QueryTexture(heart2, NULL, NULL, &heart2_dest.w, &heart2_dest.h);
    SDL_QueryTexture(heart3, NULL, NULL, &heart3_dest.w, &heart3_dest.h);
    

    img_dest.w /= 4;
    img_dest.h /= 4;

    // start sprite in the center of the screen
    float x_pos = (WINDOW_WIDTH - img_dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - img_dest.h) / 2;
    
    float x_vel = 0;
    float y_vel = 0;



    int up = 0, down = 0, left = 0, right = 0;



    int close_requested = 0;
    // int score = 0;

    // anim loop
    while (!close_requested) {
        
        
      
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close_requested = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }


        // determine velocity
        x_vel = y_vel = 0;

        if (up && !down) {
            y_vel = -SPEED;
        } else if (down && !up) {
            y_vel = SPEED;
        }

        if (left && !right) {
            x_vel = -SPEED;
        } else if (right && !left) {
            x_vel = SPEED;
        }

        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // set the positions in the struct
        img_dest.y = (int) y_pos;
        img_dest.x = (int) x_pos;
        
       
        SDL_RenderClear(renderer);

   
        
        SDL_RenderCopy(renderer, background, NULL, NULL);

        
        SDL_RenderCopy(renderer, text, NULL, &text_dest);

        SDL_RenderCopy(renderer, fps_text, NULL, &fps_dest);

        SDL_RenderCopy(renderer, heart, NULL, &heart_dest);
        SDL_RenderCopy(renderer, heart2, NULL, &heart2_dest);
        SDL_RenderCopy(renderer, heart3, NULL, &heart3_dest);

        
        SDL_RenderCopy(renderer, texture, NULL, &img_dest);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderPresent(renderer);

        //wait 1/60th of a second
        SDL_Delay(1000/180);
    }


    // message on the screen

    printf("Press any key to continue...");

    // clear the window
    SDL_RenderClear(renderer);



    // clean up resources before exiting

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(fps_text);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(heart2);
    SDL_DestroyTexture(heart3);
    TTF_CloseFont(font);
    TTF_CloseFont(fps_font);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    


}