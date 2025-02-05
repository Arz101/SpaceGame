#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "SDL2/SDL.h"
#include "Components.hpp"
#include <functional>

namespace UI{

class Button{
private:
    char* tittle;
    SDL_Rect buttonRect;
    SDL_Color buttonColor;
    SDL_Texture* buttonTexture;
    SDL_Texture* titileTexture;
    bool visible = false;
    std::function<void()> EventHandler;
public:
    Button(const char* , SDL_Rect,SDL_Color, SDL_Texture*, std::function<void()> EventHandler);
    void render(SDL_Renderer*);
    void ActionListener(SDL_Event& e);
    void setButtonTittle(SDL_Renderer*);
    void OnClick(SDL_Event&);
    void setVisible(bool);
    bool getVisible() {return visible;};
};

}

#endif