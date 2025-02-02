//
//  Enemy.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 26/1/25.
//

#include "Enemy.hpp"
#include <time.h>

Enemy::Enemy(SDL_Renderer* render){
    enemyTexture = loadTexture("./resources/enemy1.png");
    destroyTexure = cpt::loadTexture("./resources/Explosion.png", render);
    generateCoords();
    y = -2;
    
    enemyRect = {x*CELL_SIZE, y, w, h};
}

Enemy::~Enemy(){
    if(enemyTexture != nullptr){
        SDL_DestroyTexture(enemyTexture);
        SDL_DestroyTexture(destroyTexure);
    }
    printf("Destroy Enemy\n");
}

void Enemy::generateCoords(){
    x = 1 + rand() % 27;
    printf("Generate enemy at: %d",x);
}

void Enemy::move(){
    if(enemyRect.y < 12){
        for(int i = 0; i < 12; i++){
            enemyRect.y++;
        }
    }

    enemyRect.x += velocity;
    if(enemyRect.x < 0 || enemyRect.x + cpt::CELL_SIZE > cpt::CELL_SIZE * cpt::CELL_COUNT){
        velocity *= -1;
        enemyRect.y+= 10;
    }
}

void Enemy::render(SDL_Renderer* render){
    SDL_RenderCopy(render, enemyTexture, NULL, &enemyRect);
    if(bullet != nullptr){
        bullet->bulletEnemyMove();
        bullet->render(render);
        destroyBullet();
    }   
}

void Enemy::destroyBullet(){
    if(bullet != nullptr){
        if(bullet->getY() + CELL_SIZE > cpt::CELL_SIZE * cpt::CELL_COUNT){
            delete bullet;
            bullet = nullptr;
        }
    }
}

void Enemy::destroyBulletByPlayerCollision(){
    if(bullet != nullptr){
        delete bullet;
        bullet = nullptr;
    }
}

SDL_Rect Enemy::getRect(){
    return enemyRect;
}

void Enemy::enemyDestroy(SDL_Renderer* render){
    SDL_RenderCopy(render, destroyTexure, NULL, &enemyRect);
}

void Enemy::setDestroyed(){
    destroyed = true;
}

bool Enemy::isDestroyed(){
    return destroyed;
}

void Enemy::attack(){
    if(bullet == nullptr)bullet = new Bullet(enemyRect.x+25, enemyRect.y+8);
}