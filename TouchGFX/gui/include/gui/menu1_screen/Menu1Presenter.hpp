#ifndef MENU1PRESENTER_HPP
#define MENU1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Menu1View;

class Menu1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Menu1Presenter(Menu1View& v);

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

    virtual ~Menu1Presenter() {}

private:
    Menu1Presenter();

    Menu1View& view;
};

#endif // MENU1PRESENTER_HPP
