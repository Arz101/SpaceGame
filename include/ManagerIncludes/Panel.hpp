#ifndef PANEL_HPP
#define PANEL_HPP

#include "SDL2/SDL.h"
#include <vector>
#include "Button.hpp"
#include "CComponent.hpp"

namespace UI{

class CPanel : public CComponent{
private:
    std::vector<CButton*> buttons;
    std::vector<CPanel*> panels;
public:
    CPanel(SDL_Rect, SDL_Color, SDL_Texture* ,SDL_Renderer*);
    void render() override;
    void EventHandler(SDL_Event&) override;
    void addButton(CButton*);
    void addPanel(CPanel*);

};

}

#endif