void drawHud(void)
{
	char text[16];

	sprintf(text, "Score: %03d", stage.score);

	drawText(text, 10, 0, 255, 255, 255, TEXT_ALIGN_LEFT, 0);

	if (stage.score > game.highscores[0].score)
	{
		sprintf(text, "Highscore: %03d", stage.score);
		
		drawText(text, SCREEN_WIDTH - 10, 0, 128, 255, 128, TEXT_ALIGN_RIGHT, 0);
	}
	else
	{
		sprintf(text, "Highscore: %03d", game.highscores[0].score);
		drawText(text, SCREEN_WIDTH - 10, 0, 255, 255, 255, TEXT_ALIGN_RIGHT, 0);
	}
}