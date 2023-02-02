#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_ttf.h>
#include "bullets.h"


typedef struct {
    int x, y, isActive;

} sBullet;

sBullet bullets[MAX_BULLETS];

// Function to initialize the bullets
void init_bullets(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].isActive = 0;
    }
}

// Function to shoot a bullet
void shoot_bullet(int x, int y) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullets[i].x = x;
            bullets[i].y = y;
            bullets[i].isActive = 1;
            break;
        }
    }
}

// Function to update the bullet positions
void update_bullets(void) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            bullets[i].y -= 5;
            if (bullets[i].y < 0) {
                bullets[i].isActive = 0;
            }
        }
    }
}




void render_bullets(SDL_Renderer* renderer) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            SDL_Rect bulletRect = {bullets[i].x, bullets[i].y, 5, 10};
            SDL_SetRenderDrawColor(renderer, 216, 124, 108, 255);
            SDL_RenderFillRect(renderer, &bulletRect);
        }
    }
}
