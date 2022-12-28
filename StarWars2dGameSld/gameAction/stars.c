/*

Our bg will be moving from top to bottom.


nce our star has reached SCREEN_HEIGHT (the bottom of the screen), we'll move it back to the top by substracting SCREEN_HEIGHT from its y coordinate. 

Our stars are represented by a vertical line,

*/



void moveStars(void) {
    int i;

    for (i = 0; i < NUM_STARS; ++i) {
        //  star to move vertically down the screen at a rate 
        stars[i].y += (stars[i].speed * app.deltaTime);
        
        if (stars[i].y >= SCREEN_HEIGHT) {

            stars[i].y -= SCREEN_HEIGHT; 
        }
    }
}


void renderStars(void) {

    int i, c;

    for (i = 0; i < NUM_STARS; ++i) {

        // the faster our stars moving the faster they will be
        
        c = 60 * stars[i].speed;


		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x, stars[i].y - 3);
    }    

}
    