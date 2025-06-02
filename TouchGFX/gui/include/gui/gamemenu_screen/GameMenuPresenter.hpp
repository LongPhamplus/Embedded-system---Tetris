#ifndef GAMEMENUPRESENTER_HPP
#define GAMEMENUPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameMenuView;

class GameMenuPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GameMenuPresenter(GameMenuView& v);

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

    virtual ~GameMenuPresenter() {}

private:
    GameMenuPresenter();

    GameMenuView& view;
};

#endif // GAMEMENUPRESENTER_HPP
