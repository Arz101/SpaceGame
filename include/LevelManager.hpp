#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include "SDL2/SDL.h"
#include "Enemy.hpp"
#include "Components.hpp"
#include <vector>
#include "ManagerIncludes/Button.hpp"
#include "ManagerComponents/Panel.cpp"

class LevelManager{
private:
    const int CELL_SIZE = 30;
    const int CELL_COUNT = 25;
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
    UI::CPanel panel;
public:
    LevelManager(SDL_Window*);
    bool init();

};

#endif