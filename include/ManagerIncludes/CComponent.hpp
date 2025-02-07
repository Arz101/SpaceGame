#ifndef CCOMPONENT_HPP
#define CCOMPONENT_HPP

#include "SDL2/SDL.h"

class CComponent{
protected:
    const SDL_Rect CC_Rect;
    const SDL_Color CC_Color;
    SDL_Texture* CC_Texture;
    SDL_Renderer* r;
    bool visible = false;
public:
    CComponent(SDL_Rect, SDL_Color, SDL_Texture*, SDL_Renderer*);
    ~CComponent() = default;
    virtual void render() = 0;
    virtual void EventHandler(SDL_Event&) = 0;
    void setVisible(bool e){visible=e;}
};

#endif