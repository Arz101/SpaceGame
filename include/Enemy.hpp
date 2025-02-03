//
//  Enemy.hpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 26/1/25.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "Bullet.hpp"
#include <deque>
#include "Components.hpp"
#include <thread>
#include <chrono>
#include "health.hpp"

extern SDL_Texture* loadTexture(const char*);
extern const int CELL_SIZE;

class Enemy{
protected:
    SDL_Texture* enemyTexture = nullptr;
    SDL_Texture* destroyTexure = nullptr;
    const int w = 100, h = 100;
    Bullet* bullet;
    int x, y;
    SDL_Rect enemyRect;
    SDL_Rect enemyHitBox;
    std::deque<Bullet*> enemyBullets;
    int generateCoords();
    bool destroyed = false;
    int velocity = 10;
    Health* enemyHealt = nullptr;
public:
    Enemy(int, SDL_Renderer*, const char*);
    Enemy(SDL_Renderer*);
    ~Enemy();
    
    void render(SDL_Renderer*);
    virtual void move();
    void attack();
    void enemyDestroy(SDL_Renderer*);
    SDL_Rect& getRect(){return enemyHitBox;};
    void setDestroyed();
    bool isDestroyed();
    Bullet* getBullet(){return bullet;};
    void destroyBullet();
    void destroyBulletByPlayerCollision();
    Health* modifyHp(){return enemyHealt;};
};

#endif /* Enemy_hpp */
