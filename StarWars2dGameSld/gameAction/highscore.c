#include <string.h>

void initHighScores(void) {
    int i;

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        memset(&game.highscore[i], 0, sizeof(game.highscore[i]));
        STRCPY(game.highscore[i].name, "Anonymous");
        game.highscore[i].score = 550 - (i * 50);
    }
}

void updateHighscores(void)
{
	game.highscores[NUM_HIGHSCORES - 1].score = stage.score;

	qsort(game.highscores, NUM_HIGHSCORES, sizeof(Highscore), highscoreComparator);
}

static int highscoreComparator(const void *a, const void *b)
{
	Highscore *h1 = ((Highscore*)a);
	Highscore *h2 = ((Highscore*)b);

	return h2->score - h1->score;
}