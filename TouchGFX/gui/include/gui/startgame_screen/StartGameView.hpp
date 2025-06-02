#ifndef STARTGAMEVIEW_HPP
#define STARTGAMEVIEW_HPP

#include <gui_generated/startgame_screen/StartGameViewBase.hpp>
#include <gui/startgame_screen/StartGamePresenter.hpp>

class StartGameView : public StartGameViewBase
{
public:
    StartGameView();
    virtual ~StartGameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

protected:

    uint32_t tickCountStart = 0;
    bool startAnimation = false;

    void chooseMode();
};

#endif // STARTGAMEVIEW_HPP
