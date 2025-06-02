#include <gui/gameover_screen/GameOverView.hpp>

extern int score;
GameOverView::GameOverView()
{
	Unicode::snprintf(textArea1Buffer, 10, "%d", score);
	textArea1.setWildcard(textArea1Buffer);
	textArea1.resizeToCurrentText();
	textArea1.invalidate();
}



void GameOverView::setupScreen()
{
    GameOverViewBase::setupScreen();
}

void GameOverView::tearDownScreen()
{
    GameOverViewBase::tearDownScreen();
}
