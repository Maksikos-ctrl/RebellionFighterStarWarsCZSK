

void doEntities(void) {
    sEntity *e, *prev;

    prev = &stage.entityHead;

    for (e = stage.entityHead.next; e!= NULL; e = e->next) {

        if (e->tick != NULL) e->tick(e);

        if (e->health <= 0) {
            if (e == stage.entityEnd) stage.entityEnd = prev;

            prev->next = e->next;

            
            deadEnd->next = e;
            deadEnd = e;
            deadEnd->next = Null;
            

            e = prev;
        }
        prev = e;   
    }
}


void clearEntities(void) {
    
    sEntity * e;

    while (stage.entityHead.next != NULL) {
        e = stage.entityHead.next;

        stage.entityHead.next = e->next;

        if (e->data != NULL) free(e->data);

        free(e);
    }

    stage.entityEnd = &stage.entityHead;    

}

void clearDeadEntities(void) {
    sEntity *e;

    while (deadHead.next) {
        e = deadHead.next;

        deadHead.next = e->next;

        if (e->data != NULL) free(e->data);

        free(e);
    }

    deadEnd = &deadHead;
}

void drawEntities(void) {
    sEntity * e;

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->draw != NULL) {
            e->draw(e);
        } else if (e->texture != NULL) {
            blitAtlasImage(e->texture, e->x, e->y, 0, SDL_FLIP_NONE);
        } else {
            printf("ERROR: Entity is missing a texture.\n");
        }
    }
}


static void doAlienCollision(sBullet *b) {
    Entity *e;

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->type == ET_ALIEN && collision(e->x, e->y, e->texture->rect.w, e->texture->rect.h, b->x, b->y, b->texture->rect.w, b->texture->rect.h)) {
            e->takeDamage(e, 1);
            b->dead = 1;

            if (b->texture != NULL) {
                addSmallExplosion(b->x + (b->texture->rect.w / 2), b->y + (b->texture->rect.h / 2));
            }
        }
    }
}      