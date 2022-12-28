
void initStage(void) {

    memset(&stage, 0, sizeof(Stage));

    // here will be awaked init functions

    initEntities();

    initPlayer();

    initBullets();


    bg = loadTexture("assets/starfield.jpg");


    // will be used to hold the position of the background as it scrolls
    bgY = -SCREEN_HEIGHT;

    app.delegate.logic = logic;
    app.delegate.draw = draw;
}



static void logic(void) {


    // This will shift our background down when it comes to drawing.
    bgY += app.deltaTime;


    if (bgY >= 0) {
        bgY -= SCREEN_HEIGHT;
    }

    moveStars();

    doPlayer();

    removeOffscreenBullets();
}

static void draw(void) {
    drawBg();

	renderStars();

	drawEntities();

	drawBullets();

	drawHud();
}

static void drawBg(void) {

    

    double y;

    for (y = bgY; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT) {
        blit(bg, 0, y, 0, SDL_FLIP_NONE);
    }

}    


