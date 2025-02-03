#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "Enemy.hpp"
#include "SDL2/SDL.h"
#include "Components.hpp"
#include <cmath>

class Rocket : public Enemy{
private:
    float time;
    int rocketPositionX;

public:
    Rocket(SDL_Renderer*);

    void move() override;
    void render(SDL_Renderer*);
};

#endif