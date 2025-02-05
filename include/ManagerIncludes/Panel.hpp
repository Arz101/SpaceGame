#ifndef PANEL_HPP
#define PANEL_HPP

#include "SDL2/SDL.h"
#include <vector>
#include "Button.hpp"

namespace UI{

class CPanel{
private:
    SDL_Rect rectPanel;
    SDL_Color color;
    SDL_Texture* panelTexture;
    bool visible = false;
    std::vector<Button*> buttons;
    std::vector<CPanel*> panels;
public:
    CPanel(SDL_Rect, SDL_Color);
    void render(SDL_Renderer*);
    void addButton(Button*);
    void addPanel(CPanel*);
    void setVisible(bool);
    bool getVisible(){return visible;}
};

}

#endif