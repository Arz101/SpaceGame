#ifndef HEALTH_HPP
#define HEALTH_HPP

#include "Components.hpp"
#include "SDL2/SDL.h"
#include <vector>

class Health{
private:
    int countHits;
    SDL_Texture* healthTexture;
    std::vector<SDL_Rect*> hp;
    
public:
    Health(int);
    Health(int, SDL_Renderer*, const int);
    void render(SDL_Renderer*);
    void deleteHearth();
    void hit();
    bool dead();
};

#endif