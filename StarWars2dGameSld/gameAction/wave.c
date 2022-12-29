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
            addSwingingAliens();
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