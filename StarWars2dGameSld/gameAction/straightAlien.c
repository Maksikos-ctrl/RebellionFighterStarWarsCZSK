#include <math.h>

void initStraightALient(int startDelay, int x, int y, double dx, double dy) {

    sEntity *e;
    StraightAlien *s = malloc(sizeof(StraightAgent));
    memset(s, 0, sizeof(StraightAgent));

    s->startDelay = startDelay;
    s->dx = dx;
    s->dy = dy;

    if (littleImperialAlienTexture == NULL) {
        littleImperialAlienTexture = getAtlasImage("assets/imperialFighter.png", 1);
        bulletTexture = getAtlasImage("assets/bullet.png", 1);
    }

    e = spawnEntity(ET_ALIEN);
    e->texture = littleImperialAlienTexture;
    e->data = s;

    e->x = x - (e->texture->rect.w / 2);
    e->y = y;
    e->health = 2;
    
    e->tick = tick;
    e->draw = draw;
    e->takeDamage = takeDamage;
    e->die = die;

}

static void tick(sEntity *self) {

    StraightAlien *s = (StraightAlien*) self->data;

    s->startDelay -= app.deltaTime;

    if (s->startDelay <= 0) {
        self->x += s->dx * app.deltaTime;
        self->y += s->dy * app.deltaTime;
    }

    if ((s->dx < 0 && self->x < -75) || (s->dx > 0 && self->x > SCREEN_WIDTH)) {
        self->health = 0;
    }

    s->reload = fmax(s->reload - app.deltaTime, 0);

    if (s->reload < 0) {
        if (rand() % 5 == 0) fireBullet(self);
        s->reload = FPS;
    }

    s->damageTimer = fmax(s->damageTimer - app.deltaTime, 0);

    if (player->health > 0 && collision(self->x, self->y, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.h)) {
        self->health = 0;
        self->die(self);

        player->health = 0;
        player->die(player);
    }

    stage.hasAliens = 1;

}