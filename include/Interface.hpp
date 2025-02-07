#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "ManagerIncludes/Button.hpp"
#include "ManagerIncludes/Panel.hpp"
#include "SDL2/SDL.h"
#include "Components.hpp"
#include "Game.hpp"

class Interface {
private:
    SDL_Window* window;
    SDL_Renderer* r;
    UI::CPanel* mainPanel;
    int width, height;
    std::function<void()> GAME;
public:
    Interface(SDL_Window*, SDL_Renderer*);
    void createButtons();
    void initGame(std::function<void()>);
    void initManage();
    void setEvent(SDL_Event&);
    void render();
    void close();
};

#endif