#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "SDL2/SDL.h"
#include "Components.hpp"
#include <functional>
#include "CComponent.hpp"

namespace UI{

class CButton : public CComponent{
private:
    enum class State{Normal, Horverd, Pressed};
    State state = State::Normal;
    const char* tittle;
    SDL_Texture* tittleTexture;
    std::function<void()> func;
public:
    CButton(const char*,SDL_Rect,SDL_Color,SDL_Texture*, SDL_Renderer*,std::function<void()> EventHandler);
    void render() override;
    void EventHandler(SDL_Event& e) override;
    void setButtonTittle();
    bool isClicked(int&, int&);
};

}

#endif