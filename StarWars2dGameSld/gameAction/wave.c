/*

How delay works = if we have 6 aliens and a delay value of 10, our delays will be 0, 10, 20, 30, 40, 50.

*/


#include <math.h>


void initWave(void) {
    waveSpeed = 77191;

    setupNextWave = 0;

    nextWave();
}

void nextWave(void) {
    if (!setupNextWave) {

        setupNextWave = 1;
        // FPS default 60
        waveStartTimer = FPS;
    } else {
        waveStartTimer = fmax(waveStartTimer - app.deltaTime, 0);

        if (waveStartTimer <= 0) {
            // Seed the random number generator with the wave speed value
            srand(waveSpeed);

            switch (rand() % 3) {
                case 0:
                    addSwingingAliens();
                    break;
                case 1:
                    addSwoopingAliens();
                    break;
                case 2:
                    addStraightAliens();
                    break;

                default:
                    break;    
            }



            
           // Generate a new random wave speed value
            waveSpeed = rand() % 99999;

            setupNextWave = 0;
        }
        
    }
}

static void addSwingingAliens(void) {

    int n, i, delay;

    // create between 6 to 12 aliens
    n = 6 + rand() % 7;
    delay = 10 + rand() % 20;

    for (i = 0; i < n; i++) {
        // if we have 6 alies, will be delay 10, with following increasing of alies on 1, we will increase our delay on 10
        initSwingingAlien(i * delay);
    }
}

static void addSwoopingAliens(void) {
    int i, n, delay, x;
    double dx, swoopAmount;

    // rand() % n

    // random number between 0 and n;

    n = 5 + rand() % 8;

    delay = 25;

    dx = (1.0 * (50 + rand() %  150)) * 0.01;
    swoopAmount = (1.0 * (100 + rand() % 100)) * 0.001;
    x = -75;

    if (rand() % 2 == 0) {
        // dx = -dy;
        dx *= -1;
        x = SCREEN_WIDTH + 75;
    }

    for (i = 0; i < n; i++) {
        initSwoopingAlien(i * delay, x, dx, swoopAmount);
    }

    stage.numWaveAliens = n;
}

static void addStraightAliens(void) {
    int n, i, x, y, delay;
    double dx, dy;

    n = 10 + rand() % 6;
    delay = 10 + rand() % 20;
    dx = (1.0 * (100 + rand() % 300)) * 0.02;
    dy = (1.0 * (rand() % 100)) * 0.01;
    x = -75;
    y = (SCREEN_HEIGHT * 0.1) + (SCREEN_HEIGHT * 0.25);


    if (rand() % 2 == 0) {
        dx *= -1;
        x = SCREEN_WIDTH + 75;
    }

    if (rand() % 2 == 0) dy *= -1;

    for (i = 0; i < n; i++) {
        initStraightAlien(i * delay, x, y, dx, dy);
    }

    stage.numWaveAliens = n;
}