
void initStage(void) {

    memset(&stage, 0, sizeof(Stage));

    // here will be awaked init functions

    initEntities();

    initPlayer();   

    initStars();

    initsBullets();

    initEffects();

    initWave();


    bg = loadTexture("assets/starfield.jpg");


    // will be used to hold the position of the background as it scrolls
    bgY = -SCREEN_HEIGHT;

    // 2 secs timeout

    gameOverTime = FPS * 2;

    

    app.delegate.logic = logic;
    app.delegate.draw = draw;
}



static void logic(void) {

    stage.numAliens = 0;


    // This will shift our background down when it comes to drawing.
    bgY += app.deltaTime;


    if (bgY >= 0) bgY -= SCREEN_HEIGHT; 

    moveStars();

    doEntities();

    removeOffscreensBullets();

    doEffects();

    if (player->health <= 0) {
        gameOverTime -= app.deltaTime;

        if (gameOverTime <= 0) {
            resetStage();

            initStage();
        }
    } else if (stage.numAliens == 0) {

        clearDeadEntities();

        nextWave();
    }
}

static void draw(void) {
    drawBg();

	renderStars();

	drawEntities();

	drawsBullets();

	drawHud();
}

static void drawBg(void) {

    clearEntities();

    clearDeadEntities();

    clearBullets();

    clearEffects();

}    


