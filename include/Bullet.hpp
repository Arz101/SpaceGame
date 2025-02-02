//
//  Bullet.hpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include <SDL.h>

extern SDL_Texture* loadTexture(const char*);

class Bullet{
private:
    int x,y;
    const int w =50;
    const int h=50;
    const int velocity= 20;
    SDL_Texture* bulletTexture;
    SDL_Rect bulletRect;
public:
    Bullet();
    Bullet(int, int);
    ~Bullet();
    void bulletCollision();
    void bulletPosition();
    void render(SDL_Renderer*);
    void bulletMove();
    void bulletEnemyMove();
    SDL_Rect getRect();
    int getY();
    
};

#endif /* Bullet_hpp */
