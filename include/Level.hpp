#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "SDL2/SDL.h"
#include "Enemy.hpp"
#include "Components.hpp"
#include <vector>

class Level{
private:
    std::vector<Enemy> enemies;
public:
    Level(SDL_Renderer*);
    ~Level();
};