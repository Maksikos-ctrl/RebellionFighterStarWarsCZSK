#include <math.h>

void initSwingingAlien(int startDelay, int x, double swingAmount, int sweepRange, int dy) {

    sEntity *e = spawnsEntity(ET_ALIEN);

    SwingingAlien *s = malloc(sizeof(SwingingAlien));
    memset(s, 0, sizeof(SwingingAlien));

    s->startDelay = startDelay;
    s->reload = rand() % (int) FPS;
    s->swingAmount = swingAmount;
    s->sweepRange = sweepRange;
    s->dy = dy;

    // check if lAlText has not yet been initialized, if yes, init it
    if (littleAlienTexture == NULL) {
        littleAlienTexture = getAtlasImage("assets/skyEnemy.png", 1);
        bulletsTexture = getAtlasImage("assets/bullet.png", 1);
    }



   
    e = spawnEntity(ET_ALIEN); 
    e->texture = littleAlienTexture;
    e->data = s;

    
    e->x =  e->texture-rect.w / 2;
    e->y = -150;

    e->tick = tick;
    e->die = die; 

}


static void tick(sEntity *self) {
    SwingingAlien *s = (SwingingAlien *) self->data;

    s->startDelay -= app.deltaTime;

    if (s->startDelay <= 0) {
        s->swing += 0.05 * app.deltaTime;

        self->x += cos(s->swing) * (s->sweepRange * app.deltaTime);
        self->y += s->dy * app.deltaTime;    
    }

    if (self->y >= SCREEN_HEIGHT) self->health = 0;

    s->reload = fmax(s->reload - app.deltaTime, 0);

    if (s->reload == 0) {

        if (rand() % 5 == 0) {
            fireBullets(self);
        }

        s->reload = FPS;

    }


    if (player->health > 0 & collision(self->x, self->y, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.h)) {
        self->health = 0;
        self->die(self);

        player->health = 0;
        player->die(player);
    }

    stage.numAliens++;
}


static void die(sEntity *self) {
    addPointsPod(self->x, self->y);
}