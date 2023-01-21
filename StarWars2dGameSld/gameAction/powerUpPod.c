/*

CHANGE_TIMER == 3 seconds in our header (FPS * 3)

*/

void powerUpPod(int x, int y, int type) {

    sEntity *e;
    PowerUpPod *p = malloc(sizeof(PowerUpPod));
    memset(p, 0, sizeof(PowerUpPod));


    p->type = type;
    p->changeTimer = CHANGE_TIMER;

    e = spawnsEntity(ET_POWER_UP_POD);
    e->x = x;
    e->y = y;
    e->data = p;

    e->tick = tick;

    if (sidearmPodTexture == NULL) sidearmPodTexture = getAtlasImage("assets/sidearm.png", 1);


    updateTexture(e, p);
 
}

static void tick(ssEntity *self) {

    PointsPod *p = (PointsPod*) self->data;
    p->changeTimer -= app.deltaTime;

    if (p->changeTimer <= 0) {
        p->type = (p->type + 1) % PP_MAX;
        p->changeTimer = CHANGE_TIMER;

        updateTexture(self, p);
    }


    if (collision(self->x, self->y, self->texture->rect.w, self->texture->rect.h, player->x, player->y, player->textures->rect.w, player->textures->rect.h)) {
        activatePowerUpPod(self, p);
    }

    self->y += 3 * app.deltaTime;

    if (self->y >= SCREEN_HEIGHT) self->health = 0;
}

static void updateTexture(sEntity *e, PointsPod *p) {
    
    switch (p->type) {
        case PP_SIDEARM:
            e->texture = sidearmPodTexture;
            break;
        default:
            break;    
    }

    self->health = 0;


}


