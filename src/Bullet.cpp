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

    int offsetX = 8;
    int offsetY = 8;

    bulletHitBox = {bulletRect.x + offsetX, bulletRect.y + offsetY, 25,25};
}

Bullet::~Bullet(){
    printf("Destroy Bullet\n");
}

void Bullet::render(SDL_Renderer* render){
    if(SDL_RenderCopy(render, bulletTexture, NULL, &bulletRect) != 0){
        printf("Error rendering bullet texture: %s", SDL_GetError());
    }
    SDL_SetRenderDrawColor(render, 255,0,0,255);
    SDL_RenderDrawRect(render, &bulletHitBox);

    SDL_SetRenderDrawColor(render, 0,255,0,255);
    SDL_RenderDrawRect(render, &bulletRect);
}

void Bullet::bulletMove(){
    bulletRect.y-=velocity;
    bulletHitBox.y-=velocity;
}

void Bullet::bulletEnemyMove(){
    bulletRect.y+= enemyVelocity;
    bulletHitBox.y+=enemyVelocity;
}

int Bullet::getY(){
    return bulletRect.y;
}

