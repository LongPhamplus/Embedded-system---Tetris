#ifndef GAMEBOARDPRESENTER_HPP
#define GAMEBOARDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameBoardView;

class GameBoardPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GameBoardPresenter(GameBoardView& v);

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

    virtual ~GameBoardPresenter() {}

private:
    GameBoardPresenter();

    GameBoardView& view;
};

#endif // GAMEBOARDPRESENTER_HPP
