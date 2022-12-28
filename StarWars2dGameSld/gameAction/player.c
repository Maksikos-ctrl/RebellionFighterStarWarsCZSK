#include <math.h>


void initPlayer(void) {

    Fighter *f = malloc(sizeof(Fighter));
    memset(f, 0, sizeof(Fighter));

    f->speed = 5.0;
    f->reloadRate = 25;


    player = spawnEntity();
    player->texture = getAtlasImage("assets/plane.jpeg", 1);
    player->x = (SCREEN_WIDTH - player->textures->rect.w) / 2;
    player->y = SCREEN_HEIGHT - 100;
    player->data = f;

    bulletTexture = getAtlasImage("assets/bullets.png", 1);
}


void doPlayer(void) {
    

    Fighter *f = (Fighter*) player->data;

    f->reload = fmax(f->reload - app.deltaTime, 0);

    int x_

    if (app.keyboard[SDL_SCANCODE_LEFT]) player->x  -= f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_RIGHT]) player->x  += f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_UP]) player->x  -= f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_DOWN]) player->x  += f->speed * app.deltaTime;

    if (app.keyboard[SDL_SCANCODE_LCTRL] && f->reload == 0) {
        fireBullet();
        
        f->reload = f->reloadRate;
    }


    player->x = fmin(fmax(player->x, 0), SCREEN_WIDTH - player->textures->rect.w);
    player->y = fmin(fmax(player->y, 0), SCREEN_HEIGHT - player->textures->rect.w);

}