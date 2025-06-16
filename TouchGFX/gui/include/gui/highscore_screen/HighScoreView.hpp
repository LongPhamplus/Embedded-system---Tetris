#ifndef HIGHSCOREVIEW_HPP
#define HIGHSCOREVIEW_HPP

#include <gui_generated/highscore_screen/HighScoreViewBase.hpp>
#include <gui/highscore_screen/HighScorePresenter.hpp>

class HighScoreView : public HighScoreViewBase
{
public:
    HighScoreView();
    virtual ~HighScoreView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tickEvent();
protected:
};

#endif // HIGHSCOREVIEW_HPP
