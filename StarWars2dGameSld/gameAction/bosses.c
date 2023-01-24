#include <math.h>

static void initDarthVader(void) {
    Boss *b = malloc(sizeof(Boss));
    memset(b, 0, sizeof(Boss));

    b->maxHealth = 100;
    b->attack = fireDarthVaderWithBullets;

    if (darthVaderTexture == NULL) {
        darthVaderTexture = getAtlasImage("assets/darthVader.jpeg");
        downBulletTexture = getAtlasImage("assets/downBullet.png");

    }

    sEntity *e = spawnEntity(ET_ALIEN);

    e->texture = darthVaderTexture;
    e->x = (SCREEN_WIDTH - e->texture->w) / 2;
    e->y = -250;
    e->health = b->maxHealth;
    e->data = b;

    e->tick = tick;
    e->draw = draw;
    e->takeDamage = takeDamage;
    e->die = die;

    
}

static void tick(sEntity *e) {
    Boss *b;

    stage.hasAliens = 1;

    if (self->y < 120) {
        self->y += app.deltaTime;
        return;
    }

    b = (Boss*) self->data;

    self->x += b->dx;
    self->x = fax(fmin(self->x, SCREEN_WIDTH - self->texture->w), 0);

    if ((self->x == 0 && b->dx < 0) || (self->x == SCREEN_WIDTH - self->texture->w && b->dx > 0)) {
        b->dx = -b->dx;
    }

    self->y = 120;

    b->thinkTime = fmax(b->thinkTime - app.deltaTime, 0);

    if (b->thinkTime <= 0) {
        b->dx = 0;

        if (rand() % 5 != 0) {
            b->dx = (1.0 * (rand() % 500 - rand() % 500)) * 0.001;
        }

        b->thinkTime = FPS * (25 + (rand() % 75));
        b->thinkTime *= 0.01;
    }

    b->attackTime = fmax(b->attackTime - app.deltaTime, 0);


    if (b->attackTime == 0) {
        b->numShootsToFire = 3 + rand() % 4;
        b->attackTime = FPS * (1 + (rand() % 5));
    }

    b->reload = fmax(b->reload - app.deltaTime, 0);

    if (b->reload == 0 && b->numShootsToFire > 0) {
        b->numShootsToFire--;
        b->reload = 12;
        b->attack(self);
    }

    b->damageTimer = fmax(b->damageTimer - app.deltaTime, 0);

    if (player->health > 0 && collision(self->x, self->y, self->texture->rect.w, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.w, player->texture->rect.h)) {
        player->health = 0;
        player->die();
    }

    stage.boss = self;
}

static void draw(sEntity *self) {
    Boss *b = (Boss *) self->data;

    blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);

    if (b->damageTimer > 0) {
        SDL_SetTextureBlendMode(self->texture->texture, SDL_BLENDMODE_ADD);
        blitAtlasImage(self->texture, self->x, self->y, 0, SDL_FLIP_NONE);
        SDL_SetTextureBlendMode(self->texture->texture, SDL_BLENDMODE_BLEND);
    }
}

static void takeDamage(sEntity *self, int amount) {
    if (self->y >= 120) {
        self->health -= amount;
        
        if (self->health <= 0) {
            self->die(self);
        }

        // creates an object Boss, then casts it to a pointer to a Boss
        ((Boss*) self->data)->damageTimer = 8;
    }
}


static void die(sEntity *self) {
    int i, x, y;

    stage.score += 100;

    for (i = 0; i < 25; i++) {
        x = self->x + (self->texture->rect.w / 2);
        x -= rand() % self->texture->rect.w;
        x += rand() % self->texture->rect.w;

        y = self->y + (self->texture->rect.h / 2);
        y -= rand() % self->texture->rect.h;
        y += rand() % self->texture->rect.h;

        addExplosion(x, y);
    }
}

static void fireDarthVaderWithBullets(sEntity *self) {
    sBullet *b = spawnBullet(self);

    b->texture = downBulletTexture;
    b->x = self->x + (self->texture->rect.w / 2) - (downBulletTexture->rect.w / 2);
    b->x -= 25;
	b->y = self->y + self->texture->rect.h;
	b->dy = 10;

	b = spawnBullet(self);
	b->texture = downBulletTexture;
	b->x = self->x + (self->texture->rect.w / 2) - (downBulletTexture->rect.w / 2);
	b->x += 25;
	b->y = self->y + self->texture->rect.h;
	b->dy = 10;
}

