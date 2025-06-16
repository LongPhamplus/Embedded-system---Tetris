#include <gui/menu1_screen/Menu1View.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"
#include "BitmapDatabase.hpp"
int last_temp = 299;
uint8_t temp = 0;
uint8_t res = 0;
uint8_t buttonPressedUp = 0;
uint8_t buttonPressedDown = 0;
extern osMessageQueueId_t myQueue01Handle;
extern osMessageQueueId_t myQueue02Handle;
Menu1View::Menu1View()
{

}

void Menu1View::setupScreen()
{
    Menu1ViewBase::setupScreen();
}

void Menu1View::tearDownScreen()
{
    Menu1ViewBase::tearDownScreen();
}
void Menu1View::tickEvent()
{
    tickCount++;
    uint8_t res = 0;
    if (osMessageQueueGetCount(myQueue01Handle) > 0) {
    	osMessageQueueGet(myQueue01Handle, &res, NULL, osWaitForever);
    	if(res == 4 ){
    		temp ++;
    	     if (temp > 4){
    	        	temp = 1;
    	        } else if(temp <= 0){
    	        	temp = 4;
    	        }
    	} else
    	if(res == 1 ){
    		temp --;
    	     if (temp > 4){
    	        	temp = 1;
    	        } else if(temp <= 0){
    	        	temp = 4;
    	        }
    	} else if (res == 3){
			application().gotoStartGameScreenNoTransition();
    	}
    	if(res == 2){
    		switch(temp){
    		case 1:
    			application().gotoGameBoardScreenNoTransition();
    			break;
    		case 2:
    			application().gotoGameMenuScreenNoTransition();
    			break;
    		case 3:
    			application().gotoHighScoreScreenNoTransition();
    			break;
    		case 4:
    			application().gotoStartGameScreenNoTransition();
    			break;
    		default:
    			break;
    		}
    	}
    if (temp != last_temp)
    {
        // Bỏ blur ảnh cũ (nếu có)
        switch (last_temp)
        {
            case 1:
            	 image2.setBitmap(touchgfx::Bitmap(BITMAP_STAR_GAME__ID));
            	 image2.invalidate();
                break;
            case 2:
            	 image3.setBitmap(touchgfx::Bitmap(BITMAP_DO_KHO_ID));
            	 image3.invalidate();
                break;
            case 3:
            	 image4.setBitmap(touchgfx::Bitmap(BITMAP_HIGH_SCORE_ID));
            	 image4.invalidate();
                break;
            case 4:
            	 image5.setBitmap(touchgfx::Bitmap(BITMAP_EXIT_ID));
            	 image5.invalidate();
                break;
            default:
                break;
        }
        switch (temp)
        {
            case 1:
                 image2.setBitmap(touchgfx::Bitmap(BITMAP_STAR_GAME_1_ID));
                 image2.invalidate();
                break;
            case 2:
            	 image3.setBitmap(touchgfx::Bitmap(BITMAP_DO_KHO_1_ID));
            	 image3.invalidate();
                break;
            case 3:
            	 image4.setBitmap(touchgfx::Bitmap(BITMAP_HIGH_SCORE_1_ID));
            	 image4.invalidate();
                break;
            case 4:
            	 image5.setBitmap(touchgfx::Bitmap(BITMAP_EXIT_1_ID));
            	 image5.invalidate();
                break;
            default:
                break;
        }
        // Cập nhật lại lệnh cũ
        last_temp = temp;
    }
    }
}
