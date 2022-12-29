/*

delta time == elapsed time

*/

void removeOffscreenBullets(void) {

    Bullet *b, *prev;


    prev = &stage.bulletHead;

    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        
        // updates x and y coordinates of the bullet by adding the product of bullet 'dx,dy' vals and the elapsed time to it, it forces bullet to move both horizontally and vertically
        b->x += b->dx * app.deltaTime;
        b->y += b->dy * app.deltaTime;

        //checks whether the bullet is still on the screen 

        if (!collision(b->x, b->y, b->texture->rect.w, b->texture->rect.h, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
            b->dead = 1;
        } else if (b->host == player) {
            doAlienCollision();
        }

        if (b->dead) {

            prev->next = b->next;

            if (b == stage.bulletEnd) stage.bulletEnd =  prev;

            free(b);

            b = prev;

        }

       
        prev = b;
    } 
}


static void doAlienCollision(Bullet *b) {
    Entity *e;

    for (e = stage.entityHead.next; e != NULL; e = e->next) {
        if (e->type == ET_ALIEN && collision(e->x, e->y, e->texture->rect.w, e->texture->rect.h, b->x, b->y, b->texture->rect.w, b->texture->rect.h)) {
            e->health--;

            if (e->health <= 0) e->die(e);
            
            b->dead = 1;
                
        }
    }
}