#ifndef GAMEMENUVIEW_HPP
#define GAMEMENUVIEW_HPP

#include <gui_generated/gamemenu_screen/GameMenuViewBase.hpp>
#include <gui/gamemenu_screen/GameMenuPresenter.hpp>

class GameMenuView : public GameMenuViewBase
{
public:
    GameMenuView();
    virtual ~GameMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void tickEvent();
protected:

    uint32_t tickCount = 0;
    bool startAnimation = false;

    void startGame();
    void chooseMode();
};

#endif // GAMEMENUVIEW_HPP
