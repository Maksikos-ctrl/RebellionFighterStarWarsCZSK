/*

Here will be all out explosion proccesses

sprintf = writes to buffer

? Our explosions are LINKED LISTS

*/


void initEffects() {
    int i;
    char fileName[MAX_FILENAME_LENGTH];

    memset(&explosionEffect, 0, sizeof(explosionEffect));

    if (!hasTexture) {
        hasTexture = 1;

        for (i = 0; i < NUM_SMALL_EXPLOSION_FRAMES; i++) {
            sprintf(fileName, "assets/explosion%02d.png", i + 1);

            smallExplosionTextures[i] = getAtlasImage(fileName, 1);
        }

        for (i = 0; i < NUM_EXPLOSION_FRAMES; i++) {
            sprintf(fileName, "assets/bigExplosion%02d.png", i + 1);

            explosionTextures[i] = getAtlasImage(fileName, 1);
        }

    }
}

void doEffects(void) {

    Explosion *e, *prev;

    prev = &explosionHead;

    for (e = explosionHead.next; e != NULL; e = e->next) {

        e->frameTime -= app.deltaTime;

        if (e->frameTime <= 0) {
            e->frame++;

            e->frame = e->frameSpeed;

            if (e->frame < e->numFrames) {
                e->textures++;
            } else {
                prev->next = e->next;

                if (e == explosionEnd) explosionEnd = prev;

                free(e);

                e = prev;
            }
        }

        prev = e;

    }
}

void drawEffects(void) {
    Explosion *e;


    for (e = explosionHead.next; e != NULL; e = e->next) {
        // we set 1 here to center so that our explosions will be set around their pos
        blitAtlasImage(*e->texture, e->x, e->y, 1, width);
    }
}

void drawSmallExplosion(int x, int y) {

    Explosion *e;

    e = malloc(sizeof(Explosion));
    memset(e, 0, sizeof(Explosion));
    explosionEnd->next = e;
    explosionEnd = e;

    e->x = x;
    e->y = y;
    e->numFrames = NUM_SMALL_EXPLOSION_FRAMES;
    e->frameSpeed = 1;
    e->frameTime = e->frameSpeed;
    e->texture = smallExplosionTextures;

}


void addExplosion(int x, int y) {
    
    EExplosion *e;

    e = malloc(sizeof(Explosion));
    memset(e, 0, sizeof(Explosion));
    explosionEnd->next = e;
    explosionEnd = e;

    e->x = x;
    e->y = y;
    e->numFrames = NUM_SMALL_EXPLOSION_FRAMES;
    e->frameSpeed = 5;
    e->frameTime = e->frameSpeed;
    e->texture = smallExplosionTextures;

}


void clearEffects(void) {
    Explosion *e;

    while (explosionHead.next) {
        e = explosionHead.next;
        explosionHead.next = e->next;

        free(e);
    }

    explosionEnd = &explosionHead;
} 


