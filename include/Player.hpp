//
//  Player.hpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SDL.h>
#include <string>
#include "Bullet.hpp"
#include <deque>
#include "health.hpp"

extern SDL_Texture* loadTexture(const char*);

class Player{
private:
    Health* hpPlayer = nullptr;
    SDL_Rect playerRect;
    SDL_Rect playerHitBox;
    const int velocity = 10;
    std::deque<Bullet*> bullets;
    SDL_Renderer* r = nullptr;
public:
    bool playerAttack = false;
    SDL_Texture* playerTexture=nullptr;
    Player();
    Player(int, int, int, int, SDL_Renderer*, const int);
    ~Player();
    void move(SDL_Event&);
    void attack(SDL_Event&);
    void render(SDL_Renderer*);
    void die();
    SDL_Rect& getRect(){return playerHitBox;};
    SDL_Texture* getTexture();
    int getX();
    int getY();
    void destroyBullet();
    bool bulletsIsEmpty();
    std::deque<Bullet*>& getBullets();
    Health* getHealth(){return hpPlayer;};
    void destroyBulletByEnemyCollision(Bullet** b);
};


#endif /* Player_hpp */
