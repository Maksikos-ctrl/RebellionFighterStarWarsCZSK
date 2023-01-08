#include <math.h>

void initSwoopingAlien(int startDelay, int x, double dx, double swoopAmount) {

    sEntity *e;
    SwoopingAlien *s = malloc(sizeof(SwoopingAlien));
    memset(s, 0, sizeof(SwoopingAlien));

    s->startDelay = startDelay;
    s->swoopAmount = swoopAmount;
    s->dx = dx;

    if (littleImperialAlienTexture == NULL) {
        littleImperialAlienTexture = getAtlasImage("assets/imperialFighter.png", 1);
        bulletTexture = getAtlasImage("assets/bullet.png", 1);
    }

    e = spawnEntity(ET_ALIEN);
    e->texture = littleImperialAlienTexture;
    e->data = s;

    e->x = x - (e->texture->rect.w / 2);
    e->y = 0;
    e->health = 2;

    e->tick = tick;
    e->draw = draw;
    e->takeDamage = takeDamage;
    e->die = die;

}


static void(sEntity *self) {

    SwoopingAlien *s = (SwoopingAlien *) self->data;

    s->startDelay -= app.deltaTime;

    if (s->startDelay < 0) {
        s->swoop += s->swoopAmount * app.deltaTime;

        self->y += sin(s->swoop);
        self->x += s->dx * app.deltaTime;
    }

    if ((s->dx > 0 && self->x >= SCREEN_WIDTH || (s->dx < 0 && self->x <= -self->texture.rect.w))) {
        self->health = 0;
    }


    s->reload = fmax(s->reload - app.deltaTime, 0);

    if (s->reload == 0) {

        if (rand() % 5 == 0) fireBullet(self);

        s->reload = FPS;

    }

    s->damageTimer = fmax(s->damageTimer - app.deltaTime, 0);

    if (player->health > 0 && collision(self->x, self->y, self->texture.rect.w, self->texture.rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.h)) {
        self->health = 0;
        self->die(self);

        player->health = 0;
        player->die(player);
    }

    stage.hasAliens = 1;

}


static void draw(sEntity *s) {
    SwoopingAlien *s = (SwoopingAlien *) self->data;

    blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);

    if (s->damageTimer > 0) {
        SDL_SetTextureBlendMode(self->texture->texture, SDL_BLENDMODE_ADD);
        blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
        SDL_SetTextureBlendMode(self->texture->texture, SDL_BLENDMODE_BLEND);
    }
}

static void takeDamage(sEntity *self, int amount) {

    self->health -= amount;

    if (self->health == 0) {
        self->die(self);
    }

    ((SwoopingAlien *) self->data)->damageTimer = 8;

}

static void die(sEntity *self) {
    stage.score++;

    addExplosion(self->x + (self->texture->rect.w / 2), self->y + (self->texture->rect.h / 2));

    if (--stage.numWaveAliens == 0) addPointsPod(self->x, self->x);
}

void initStraightALien(int startDelay, int x, int y, double dx, double dy) {
    Entity *e;
    StraightAlien *s = malloc(sizeof(StraightAgent));
    memset(s, 0, sizeof(StraightAgent));


    s->startDelay = startDelay;
    s->dx = dx;
    s->dy = dy;

    if (littleImperialAlienTextures == NULL) {
        littleImperialAlienTextures = getAtlasImage("assets/imperialFighter.png", 1);
        bulletTextures = getAtlasImage("assets/bullet.png", 1);
    }

    e = spawnEntity(ET_ALIEN);
    e->texture = littleImperialAlienTextures;
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

    StraightAlien *s = (StraightAlien *) self->data;

    s->startDelay -= app.deltaTime;

    if (s->startDelay <= 0) {
        self->x += s->dx * app.deltaTime;
        self->y += s->dy * app.deltaTime;
    }

    if ((s->dx < 0 && self->x < -75) || (s->dx > 0 && self->x > SCREEN_WIDTH)) {
        self->health = 0;
    }

    s->reload = fmax(s->reload - app.deltaTime, 0);

    if (s->reload == 0) {
         
        if (rand() % 5 == 0) fireBullets(self);

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