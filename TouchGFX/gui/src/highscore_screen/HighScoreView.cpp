#include <gui/highscore_screen/HighScoreView.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"
extern int score;
extern int high_score;
extern osMessageQueueId_t myQueue01Handle;
extern osMessageQueueId_t myQueue02Handle;
HighScoreView::HighScoreView()
{
//		Unicode::snprintf(textArea2Buffer, 10, "%d",high_score);
//		textArea1.setWildcard1(textArea2Buffer);
//		textArea1.resizeToCurrentText();
//		textArea1.invalidate();
}

void HighScoreView::setupScreen()
{
    HighScoreViewBase::setupScreen();
}

void HighScoreView::tearDownScreen()
{
    HighScoreViewBase::tearDownScreen();
}
void HighScoreView::tickEvent()
{
	uint8_t temp = 0;
	if (osMessageQueueGetCount(myQueue01Handle) > 0) {
	    	osMessageQueueGet(myQueue01Handle, &temp, NULL, osWaitForever);
	    	if (temp == 3){
	    		application().gotoMenu1ScreenNoTransition();
	    	}
	}
}
