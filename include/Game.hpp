#ifndef GAME_HPP
#define GAME_HPP

#include "SDL2/SDL.h"
#include "Enemy.hpp"
#include "Rocket.hpp"
#include "Player.hpp"
#include "Components.hpp"

class Game{
private: 
    Uint32 lastTime = 0;
    Uint32 EnemyLasTime = 0;
    Uint32 interval = 200;
    Uint32 currentTime = 0;
    Uint32 EnemyCurrentTime = 0;

    Player* player = nullptr;
    Enemy* enemy = nullptr;
    std::vector<Enemy*> enemies;
    Rocket* rocket = nullptr;
    SDL_Renderer* r = nullptr;
    int kills=0;

    void generateEnemies();
    void loadText(int&);
    
public:
    Game(SDL_Renderer*);
    void counters(Uint32&, Uint32);
    void render();
    void logic();
    void close();
    void event(SDL_Event&);
};


#endif