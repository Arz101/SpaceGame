//
//  Bullet.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#include "Bullet.hpp"

Bullet::Bullet(int x, int y){
    this->x = x;
    this->y = y;
    bulletTexture = loadTexture("/Users/adrian/libreSprite/bullet.png");
    bulletRect = {this->x,this->y,w,h};
}

Bullet::~Bullet(){
    printf("Destroy Bullet\n");
}

void Bullet::render(SDL_Renderer* render){
    if(SDL_RenderCopy(render, bulletTexture, NULL, &bulletRect) != 0){
        printf("Error rendering bullet texture: %s", SDL_GetError());
    }
}

void Bullet::bulletMove(){
    bulletRect.y-=velocity;
}

void Bullet::bulletEnemyMove(){
    bulletRect.y+= velocity;
}

int Bullet::getY(){
    return bulletRect.y;
}

SDL_Rect Bullet::getRect(){
    return bulletRect;
}
