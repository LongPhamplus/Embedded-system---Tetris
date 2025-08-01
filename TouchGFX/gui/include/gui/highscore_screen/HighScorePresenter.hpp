#ifndef HIGHSCOREPRESENTER_HPP
#define HIGHSCOREPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HighScoreView;

class HighScorePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HighScorePresenter(HighScoreView& v);

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

    virtual ~HighScorePresenter() {}

private:
    HighScorePresenter();

    HighScoreView& view;
};

#endif // HIGHSCOREPRESENTER_HPP
