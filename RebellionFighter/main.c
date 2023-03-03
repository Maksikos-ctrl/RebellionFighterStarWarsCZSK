/*

Rebellion fighhter game is game where you have to fight for the Republic against the Empire and save the world from the evil forces.




######  ####### ######  ####### #       #       ### ####### #     #    ####### ###  #####  #     # ####### ####### ######  
#     # #       #     # #       #       #        #  #     # ##    #    #        #  #     # #     #    #    #       #     # 
#     # #       #     # #       #       #        #  #     # # #   #    #        #  #       #     #    #    #       #     # 
######  #####   ######  #####   #       #        #  #     # #  #  #    #####    #  #  #### #######    #    #####   ######  
#   #   #       #     # #       #       #        #  #     # #   # #    #        #  #     # #     #    #    #       #   #   
#    #  #       #     # #       #       #        #  #     # #    ##    #        #  #     # #     #    #    #       #    #  
#     # ####### ######  ####### ####### ####### ### ####### #     #    #       ###  #####  #     #    #    ####### #     # 




*/


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <math.h>

#include "bullets.h"

#include "init.h"
#include "resources.h"
#include "font.h"


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Texture *background;
TTF_Font *font;
SDL_Texture *text;
SDL_Texture *heart, *heart2, *heart3;
SDL_Surface *image;
SDL_Surface *backgroundSurface;
SDL_Surface *heart_image1, *heart_image2, *heart_image3;




int main(int argc, char *argv[]) {

    
    if (!init_sdl(&window, &renderer)) {
        return 1;
    }

    

    if (!(image = IMG_Load("assets/pngwing.png"))) {
        printf("Failed to load image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }

    if (!load_image(renderer, "assets/pngwing.png", &texture, image, window)) {
        printf("Failed to load texture");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_FreeSurface(image);
        return 1;
    }

    if (!(backgroundSurface = IMG_Load("assets/pikrepo.jpg"))) {
        printf("Failed to load bgImage: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }
     
    if (!load_background(renderer, "assets/pikrepo.jpg", &background, backgroundSurface, window)) {
        printf("SDL_CreateTextureFromSurface Error: %s",SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(background);
        return 1;
    }



    if (!font_init(&font, renderer)) {
        printf("Failed to load text");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        return 1;
    }



    if (!load_text(renderer, &font, &text, "Score", 255, 255, 255, 255)) {
        printf("Failed to load text");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(text);
        return 1;
    }

      

    if (!(heart_image1 = IMG_Load("assets/fullHeart.png"))) {
        printf("Failed to load heart image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(texture);
        return 1;
    }

    if (!(heart_image2 = IMG_Load("assets/fullHeart.png"))) {
        printf("Failed to load heart image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(texture);
        return 1;
    }

    if (!(heart_image3 = IMG_Load("assets/fullHeart.png"))) {
        printf("Failed to load heart image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyTexture(texture);
        return 1;
    }

    
    if(!init_heart1(renderer, "assets/fullHeart.png", &texture, heart_image1, window)) {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }
   

    if(!init_heart2(renderer, "assets/fullHeart.png", &texture, heart_image2, window)) {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }

    if(!init_heart3(renderer, "assets/fullHeart.png", &texture, heart_image3, window)) {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return 1;
    }

    char frame_rate_buffer[50];

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
        printf("Error rendering text2: %s\n", TTF_GetError());
        return 1;
    }

    
    SDL_Texture* fps_text= SDL_CreateTextureFromSurface(renderer, fps_surface);
    TTF_CloseFont(fps_font);
    SDL_DestroyTexture(fps_text);
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

    
    heart_dest.x = width + heart_dest.w + 1120;
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
    SDL_QueryTexture(image, NULL, NULL, &img_dest.w, &img_dest.h);
    SDL_QueryTexture(fps_text, NULL, NULL, &fps_dest.w, &fps_dest.h);
    SDL_QueryTexture(heart, NULL, NULL, &heart_dest.w, &heart_dest.h);
    SDL_QueryTexture(heart2, NULL, NULL, &heart2_dest.w, &heart2_dest.h);
    SDL_QueryTexture(heart3, NULL, NULL, &heart3_dest.w, &heart3_dest.h);
    

    img_dest.w /= 4;
    img_dest.h /= 4;

   
    


    int up = 0, down = 0, left = 0, right = 0;
    int close_requested = 0;
    int frame_rate = 60;
    float x_pos = (WINDOW_WIDTH - img_dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - img_dest.h) / 2;
    
    float x_vel = 0;
    float y_vel = 0;
    



    
    while (!close_requested) {


        int frame_start = SDL_GetTicks();
    
        
      
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

        

        // Update game stats
        if (up && !down) {
            y_vel = -SPEED;
        } else if (down && !up) {
            y_vel = SPEED;
        } else {
            y_vel = 0;
        }

        if (left && !right) {
            x_vel = -SPEED;
        } else if (right && !left) {
            x_vel = SPEED;
        } else {
            x_vel = 0;
        }

      
        x_pos += x_vel / frame_rate;
        y_pos += y_vel / frame_rate;

        // set the positions in the struct
        img_dest.x = x_pos;
        img_dest.y = y_pos;

        int w1, h1;
       
        SDL_Rect fps_dest = {10, 10, w1, h1};
       

        SDL_Rect img_dest;

        SDL_Rect text_dest;
        SDL_Rect heart_dest, heart2_dest, heart3_dest;
        

        text_dest.x = 10;
        text_dest.y = 10;

        img_dest.x = 100;
        img_dest.y = 100;

        
        heart_dest.x = width + heart_dest.w + 1120;
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
        SDL_QueryTexture(image, NULL, NULL, &img_dest.w, &img_dest.h);
        SDL_QueryTexture(fps_text, NULL, NULL, &fps_dest.w, &fps_dest.h);
        SDL_QueryTexture(heart, NULL, NULL, &heart_dest.w, &heart_dest.h);
        SDL_QueryTexture(heart2, NULL, NULL, &heart2_dest.w, &heart2_dest.h);
        SDL_QueryTexture(heart3, NULL, NULL, &heart3_dest.w, &heart3_dest.h);
        

        img_dest.w /= 4;
        img_dest.h /= 4;


        



        // Rendering
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, text, NULL, &text_dest);
        SDL_RenderCopy(renderer, fps_text, NULL, &fps_dest);
        SDL_RenderCopy(renderer, heart, NULL, &heart_dest);
        SDL_RenderCopy(renderer, heart2, NULL, &heart2_dest);
        SDL_RenderCopy(renderer, heart3, NULL, &heart3_dest);
        SDL_RenderCopy(renderer, image, NULL, &img_dest);
        SDL_RenderPresent(renderer);

        
        
      
        int elapsed_time = SDL_GetTicks() - frame_start;
        if (elapsed_time > 0) {
            frame_rate = 1000 / elapsed_time;
        }

        if (frame_rate > 0) {
            sprintf(frame_rate_buffer, "FPS: %d", frame_rate); 

           
            fps_surface = TTF_RenderText_Solid(fps_font, frame_rate_buffer, fps_color);
            if (fps_surface == NULL) {
                printf("Error rendering text3: %s\n", TTF_GetError());
                return 1;
            }

           
            SDL_DestroyTexture(fps_text);            
            fps_text = SDL_CreateTextureFromSurface(renderer, fps_surface);
            
            if (fps_text == NULL) {
                printf("Error creating texture: %s\n", SDL_GetError());
                return 1;
            }

            SDL_FreeSurface(fps_surface);
            // SDL_Delay(1000/180);
        }
 
       
       
        
    }



    printf("Press any key to continue...");

    // clear the window
    SDL_RenderClear(renderer);



    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(fps_text);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(heart2);
    SDL_DestroyTexture(heart3);
    TTF_CloseFont(font);
    TTF_CloseFont(fps_font);
    TTF_Quit();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    


}