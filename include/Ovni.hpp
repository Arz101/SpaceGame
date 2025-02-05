#ifndef OVNI_HPP
#define OVNI_HPP

#include "Enemy.hpp"
#include "SDL2/SDL.h"
#include "Bullet.hpp"

class Ovni : public Enemy{
private:
    Bullet* bullet = nullptr;
    const int w = 100, h = 100;

public:
    Ovni(SDL_Renderer*);
    void move() override;
    void render();
};

#endif