#include <gui/startgame_screen/StartGameView.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"

StartGameView::StartGameView()
{

}

extern osMessageQueueId_t myQueue01Handle;

void StartGameView::setupScreen()
{
    StartGameViewBase::setupScreen();
}

void StartGameView::tearDownScreen()
{
    StartGameViewBase::tearDownScreen();
}

void StartGameView::goToMenu() {
	application().gotoMenu1ScreenNoTransition();
}

void StartGameView::handleTickEvent() {
    tickCountStart++;

    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    uint8_t res;
	if (osMessageQueueGetCount(myQueue01Handle) > 0) {
		osMessageQueueGet(myQueue01Handle, &res, NULL, osWaitForever);
		if (res == 2) {
			goToMenu();
		}
	}
    if (tickCountStart % 5 == 0) {
        if (startAnimation) {
            textArea2.moveTo(27, 278);
            textArea2.setColor(touchgfx::Color::getColorFromRGB(186, 48, 48));
        } else {
            textArea2.moveTo(27, 283);
            textArea2.setColor(touchgfx::Color::getColorFromRGB(185, 107, 48));
        }
        startAnimation = !startAnimation;
        textArea2.invalidate();  // << Nhớ invalidate để cập nhật giao diện!
    }
}
