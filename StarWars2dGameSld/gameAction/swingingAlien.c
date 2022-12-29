

void initSwingingAlien(int startDelay) {

    Entity *e = spawnEntity(ET_ALIEN);

    SwingingAlien *s = malloc(sizeof(SwingingAlien));
    memset(s, 0, sizeof(SwingingAlien));

    s->startDelay = startDelay;

    // check if lAlText has not yet been initialized, if yes, init it
    if (littleAlienTexture == NULL) {
        littleAlienTexture = getAtlasImage("assets/skyEnemy.png", 1);
    }

    
    e->texture = littleAlienTexture;
    e->data = s;

    // approx sets our enemy/ies in the middle of the screen and a bit of above
    e->x = (SCREEN_WIDTH - e->texture-rect.w) / 2;
    e->y = -150;

    e->tick = tick;
    e->die = die; 

}


static void tick(Entity *self) {
    SwingingAlien *s = (SwingingAlien *) self->data;

    s->startDelay -= app.deltaTime;

    if (s->startDelay <= 0) {
        s->swing += 0.05 * app.deltaTime;

        self->x += cos(s->swing) * (8 * app.deltaTime);
        self->y += 2 * app.deltaTime;    
    }

    if (self->y >= SCREEN_HEIGHT) self->health = 0;

    stage->hasAliens = 1;
}


static void die(Entity *self) {
    addPointsPod(self->x, self->y);
}