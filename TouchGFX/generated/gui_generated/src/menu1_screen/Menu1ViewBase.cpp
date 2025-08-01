/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/menu1_screen/Menu1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

Menu1ViewBase::Menu1ViewBase()
{
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_MENU_ID));
    add(image1);

    image2.setXY(41, 106);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_STAR_GAME__ID));
    add(image2);

    image3.setXY(41, 160);
    image3.setBitmap(touchgfx::Bitmap(BITMAP_DO_KHO_ID));
    add(image3);

    image4.setXY(41, 212);
    image4.setBitmap(touchgfx::Bitmap(BITMAP_HIGH_SCORE_ID));
    add(image4);

    image5.setXY(68, 260);
    image5.setBitmap(touchgfx::Bitmap(BITMAP_EXIT_ID));
    add(image5);
}

Menu1ViewBase::~Menu1ViewBase()
{

}

void Menu1ViewBase::setupScreen()
{

}

void Menu1ViewBase::handleTickEvent()
{
    //Interaction1
    //When every N tick call virtual function
    //Call tickEvent
    tickEvent();
}
