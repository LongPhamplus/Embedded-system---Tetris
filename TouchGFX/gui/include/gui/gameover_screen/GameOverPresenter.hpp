#ifndef GAMEOVERPRESENTER_HPP
#define GAMEOVERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameOverView;

class GameOverPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GameOverPresenter(GameOverView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GameOverPresenter() {}

private:
    GameOverPresenter();

    GameOverView& view;
};

#endif // GAMEOVERPRESENTER_HPP
