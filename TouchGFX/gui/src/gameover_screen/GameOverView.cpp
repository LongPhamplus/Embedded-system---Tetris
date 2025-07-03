#include <gui/gameover_screen/GameOverView.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"
extern int score;
extern int high_score;
extern osMessageQueueId_t myQueue01Handle;
extern osMessageQueueId_t myQueue02Handle;
GameOverView::GameOverView()
{
	if (score > high_score){
		high_score = score;
		Unicode::snprintf(textArea1Buffer, 100, "New high score: %d!!!",score);
		textArea1.setWildcard(textArea1Buffer);
		textArea1.resizeToCurrentText();
		textArea1.invalidate();
	} else {
		Unicode::snprintf(textArea1Buffer, 100, "Score: %d", score);
		textArea1.setWildcard(textArea1Buffer);
		textArea1.resizeToCurrentText();
		textArea1.invalidate();
	}
}



void GameOverView::setupScreen()
{
    GameOverViewBase::setupScreen();
}
void GameOverView::goToMenu()
{
	application().gotoMenu1ScreenNoTransition();
}


void GameOverView::tearDownScreen()
{
    GameOverViewBase::tearDownScreen();
}
void GameOverView::tickEvent(){
	uint8_t res;
	if (osMessageQueueGetCount(myQueue01Handle) > 0) {
	    	osMessageQueueGet(myQueue01Handle, &res, NULL, osWaitForever);
	    	if (res == 2){
	    		goToMenu();
	    	} else if (res  == 3){
	    		application().gotoStartGameScreenNoTransition();
	    	}
	}
}
