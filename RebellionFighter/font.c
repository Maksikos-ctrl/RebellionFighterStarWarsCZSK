#include "font.h"
#include <stdbool.h>




bool font_init(TTF_Font **font, SDL_Renderer *renderer) {
    if (TTF_Init() != 0) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    *font = TTF_OpenFont("assets/arial.ttf", 14);
    if (*font == NULL) {
        printf("Error opening font: %s\n", TTF_GetError());
        return false;
    }

    TTF_SetFontStyle(*font, TTF_STYLE_NORMAL);

    return true;

    // TTF_CloseFont(font);
    //TTF_Quit();

    

}

bool load_text(SDL_Renderer *renderer, TTF_Font **font, SDL_Texture **text, const char *str, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    int w, h;
    TTF_SizeText(*font, str, &w, &h);

    SDL_Color color = {r, g, b, a};
    SDL_Surface* surface = TTF_RenderText_Solid(*font, str, color);
    if (surface == NULL) {
        printf("Error rendering text1: %s\n", TTF_GetError());
        return false;
    }

    *text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (*text == NULL) {
        printf("Error creating text: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
    
}