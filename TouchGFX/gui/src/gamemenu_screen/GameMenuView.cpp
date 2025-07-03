#include <gui/gamemenu_screen/GameMenuView.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"

GameMenuView::GameMenuView()
{

}

extern osMessageQueueId_t myQueue01Handle;
extern int mode;

void GameMenuView::setupScreen()
{
    GameMenuViewBase::setupScreen();
}

void GameMenuView::tearDownScreen()
{
    GameMenuViewBase::tearDownScreen();
}

void GameMenuView::chooseMode1() {
	if (image2.getY() == 9 || image2.getY() == 14) {
		mode = 1;
		image2.moveTo(image2.getX(), 109);
	} else if (image2.getY() == 109 || image2.getY() == 114) {
		mode = 2;
		image2.moveTo(image2.getX(), 197);
	} else {
		mode = 3;
		image2.moveTo(image2.getX(), 9);
	}
}
void GameMenuView::chooseMode2() {
	if (image2.getY() == 197 || image2.getY() == 205) {
		mode = 3;
		image2.moveTo(image2.getX(), 109);
	} else if (image2.getY() == 109 || image2.getY() == 114) {
		mode = 2;
		image2.moveTo(image2.getX(), 9);
	} else {
		mode = 1;
		image2.moveTo(image2.getX(), 197);
	}
}
void GameMenuView::startGame() {
	application().gotoGameBoardScreenNoTransition();
}

void GameMenuView::tickEvent() {
    tickCount++;

    uint8_t res;
	if (osMessageQueueGetCount(myQueue01Handle) > 0) {
		osMessageQueueGet(myQueue01Handle, &res, NULL, osWaitForever);
		if(res == 2){
			chooseMode1();
		}
		else if (res == 1){
			chooseMode2();
		}else if (res == 4){
			startGame();
		}else if(res == 3){
			application().gotoMenu1ScreenNoTransition();
		}

		}
    if (tickCount % 5 == 0) {
        if (startAnimation) {
        	image2.moveTo(image2.getX(), image2.getY() + 5);
        } else {
        	image2.moveTo(image2.getX(), image2.getY() - 5);
        }
        startAnimation = !startAnimation;
        image2.invalidate();
    }
}

