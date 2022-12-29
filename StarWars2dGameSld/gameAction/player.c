
/*

TODO Static means that the function or variable is only visible within the file it is defined in.

*/

#include <math.h>


void initPlayer(void) {

    Fighter *f = malloc(sizeof(Fighter));
    memset(f, 0, sizeof(Fighter));

    f->speed = 5.0;
    f->reloadRate = 25;


    player = spawnEntity();
    player->texture = getAtlasImage("assets/plane.jpeg", 1);
    player->x = (SCREEN_WIDTH - player->texture->rect.w) / 2;
    player->y = SCREEN_HEIGHT - 100;
    player->data = f;

    bulletTexture = getAtlasImage("assets/bullets.png", 1);
}


void doPlayer(void) {
    

    Fighter *f = (Fighter*) player->data;

    f->reload = fmax(f->reload - app.deltaTime, 0);

    

    if (app.keyboard[SDL_SCANCODE_LEFT]) player->x  -= f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_RIGHT]) player->x  += f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_UP]) player->x  -= f->speed * app.deltaTime;
    if (app.keyboard[SDL_SCANCODE_DOWN]) player->x  += f->speed * app.deltaTime;

    if (app.keyboard[SDL_SCANCODE_LCTRL] && f->reload == 0) {
        fireBullet();
        
        f->reload = f->reloadRate;
    }


    player->x = fmin(fmax(player->x, 0), SCREEN_WIDTH - player->texture->rect.w);
    player->y = fmin(fmax(player->y, 0), SCREEN_HEIGHT - player->texture->rect.w);

}

static void fireBullet(void) {
    Bullet *b = spawnBullet();

    b->host = player;
    b->texture = bulletTexture;
    // t sets the x field of b to the center of the player's entity, minus half the width of the bullet texture. This aligns the bullet with the center of the player's entity.
    b->x = player->x + (player->texture->rect.w / 2) - (bulletTexture->rect.w / 2);
    // It sets the y field of b to the top of the player's entity, minus the height of the bullet texture. This positions the bullet just above the player's entity.
    b->y = player->y - bulletTexture->rect.w;
    // -n - moving up the screen, n = moving down 
    b->dy = -15;
}