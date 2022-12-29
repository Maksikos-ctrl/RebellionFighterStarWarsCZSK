#include <math.h>

#define POINTS_POD_TIMEOUT (FPS * 5)


void addPointsPod(int x, int y) {
    Entity *e;
    PointsPod *p = malloc(sizeof(PointsPod));
    memset(p, 0, sizeof(PointsPod));

    p->dx = (1.0 * (-25 + rand() % 50)) * 0.2;
    p->dy = (1.0 * (-25 + rand() % 50)) * 0.2;
    p->timeout = POINTS_POD_TIMEOUT;

    if (texture == NULL) texture = getAtlasImage("assets/star.png", 1);


    e =  = spawnEntity(ET_POINTS);
    e->x = x;
    e->y = y;
    e->texture = texture;
    e->data = p;

    e->tick = tick;
}


static void tick(Entity *self) {
    PointsPod *p = (PointsPod *)self->data;

    // updates the position
    self->x += p->dx * app.deltaTime;
    self->y += p->dy * app.deltaTime;

    if (self->x < 0) {
        p->dx = -p->dx;
        self->x = 0;
    }

    if (self->y < 0) {
        p->dy = -p->dy;
        self->y = 0;
    }

    if (self->x > SCREEN_WIDTH - self->texture->rect.w) {
        self->x = (SCREEN_WIDTH - self->texture->rect.w - 1);
        p->dx = -p->dx;
    }

    if (self->y > SCREEN_HEIGHT - self->texture->rect.h) {
        self->y = (SCREEN_WIDTH - self->texture->rect.w - 1);
        p->dy = -p->dy;
    }


    // if our entity has collided with any of the edges of the screen and if so our entity will bounce back into the screen
    if (collision(self->x, self->y, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->texture->rect.w, player->texture->rect.h)) {
        stage.score++;

        stage.highscore = fmax(stage.highscore, stage.score);

        self->health = 0;
    }


    p->timeout -= app.deltaTime;

 
    if (p->timeout <= 0) self->health = 0;
}