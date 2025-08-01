#ifndef GAMEOVERVIEW_HPP
#define GAMEOVERVIEW_HPP

#include <gui_generated/gameover_screen/GameOverViewBase.hpp>
#include <gui/gameover_screen/GameOverPresenter.hpp>

class GameOverView : public GameOverViewBase
{
public:
    GameOverView();
    virtual ~GameOverView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tickEvent();
    virtual void goToMenu();
protected:

    void updateScore();

};

#endif // GAMEOVERVIEW_HPP
