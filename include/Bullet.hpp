//
//  Bullet.hpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "SDL2/SDL.h"
#include "Components.hpp"

class Bullet{
private:
    int x,y;
    const int w=50;
    const int h=50;
    const int velocity= 20;
    const int enemyVelocity = 10;
    SDL_Texture* bulletTexture;
    SDL_Rect bulletRect;
    SDL_Rect bulletHitBox;
public:
    Bullet();
    Bullet(int, int, SDL_Renderer*);
    ~Bullet();
    void bulletCollision();
    void bulletPosition();
    void render(SDL_Renderer*);
    void bulletMove();
    void bulletEnemyMove();
    SDL_Rect& getRect(){return bulletHitBox;};
    int getY();
    
};

#endif /* Bullet_hpp */
