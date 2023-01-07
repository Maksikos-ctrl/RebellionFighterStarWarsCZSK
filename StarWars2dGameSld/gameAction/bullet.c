/*

delta time == elapsed time

*/

void removeOffscreensBullets(void) {

    sBullet *b, *prev;


    prev = &stage.bulletHead;

    for (b = stage.bulletHead.next; b != NULL; b = b->next) {
        
        // updates x and y coordinates of the bullet by adding the product of bullet 'dx,dy' vals and the elapsed time to it, it forces bullet to move both horizontally and vertically
        b->x += b->dx * app.deltaTime;
        b->y += b->dy * app.deltaTime;

        //checks whether the bullet is still on the screen 

        if (!collision(b->x, b->y, b->texture->rect.w, b->texture->rect.h, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
            b->dead = 1;
        } else if (b->host == player) {
            doAlienCollision(b);
        } else if (b->host->type == ET_ALIEN && player.health > 0) {
            doPLayerCollision(b);
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


static void doAlienCollision(sBullet *b) {
    

    
    if ((collision(player->x, player->y, player->texture->rect.w, player->texture->rect.h, b->x, b->y, b->texture->rect.w, b->texture->rect.))) {
        
        player.health = 0;

        player->die(player);

        
        
        b->dead = 1;

        addSmallExplosion(b->x + (b->texture->rect.w / 2), b->y + (b->texture->rect.h / 2));
            
    }

}

static void die(sEntity *e)  {

    addExplosion(self->x + (self->texture->rect.w / 2), self->y + (self->texture->rect.h / 2)

}