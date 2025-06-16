#ifndef MENU1VIEW_HPP
#define MENU1VIEW_HPP

#include <gui_generated/menu1_screen/Menu1ViewBase.hpp>
#include <gui/menu1_screen/Menu1Presenter.hpp>

class Menu1View : public Menu1ViewBase
{
public:
    Menu1View();
    virtual ~Menu1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tickEvent();
protected:
    uint8_t tickCount = 0;
};

#endif // MENU1VIEW_HPP
