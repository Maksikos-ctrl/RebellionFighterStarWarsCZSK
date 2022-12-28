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
            //  function removes the bullet from the linked list by updating the next pointer of the previous bullet (prev) to point to the next bullet in the list (b->next).
            prev->next = b->next;

            if (b == stage.bulletEnd) {
                stage.bulletEnd =  prev;
            }

            free(b);

            b = prev;

        }

        prev = b;
    } 
}