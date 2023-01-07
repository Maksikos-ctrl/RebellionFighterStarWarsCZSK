/*

sidearm.c is created to display functionality of the preparation gun of our entity to fire enemies

ox = offset 



*/

static AtlasImage *sidearmTexture = NULL;
static AtlasImage *bulletTexture = NULL;


void initSidearm(int ox) {
    Entity *e;
    Sidearm *s = malloc(sizeof(Sidearm));
    memset(s, 0, sizeof(Sidearm));

    s->ox = ox;

    if (sidearmTexture == NULL) {
        sidearmTexture = getAtlasImage("assets/sidearm.png", 1);
        bulletTexture = getAtlasImage("assets/bullet.png", 1);
    }


    e = spawnEntity(ET_SIDEARM);
    e->texture = sidearmTexture;
    e->data = s;

    e->tick = tick;

    tick(e);


}



static void tick(sEntity *e) {
    Sidearm *s = (Sidearm*) self->data;

    self->x = player->x;
    self->x += player->texture->rect.w / 2;
    self->x -= self.texture.rect.w / 2;
    self->x += s->ox;

    self->y = player->y + player->texture->rect.h;
    self.y -= self->texture.rect.h;

    if (((Fighter *) player->data)->invokeSidearm) firesBullet(self);

    if (player->health <= 0) {
        addExplosion(self->x + (self->texture->rect.w / 2) - (bulletTexture->rect.w / 2));
        self->health = 0;
    }
}


static void firesBullet(sEntity *e) {

    sBullet *b = spawnsBullet(player);
    b->texture = bulletTexture;
    b->x = self->x + (self->texture->rect.w / 2) - (bulletTexture->rect.w / 2);
    b->y = self->y - bulletTexture->rect.h;
    b->dy = -15;
}

