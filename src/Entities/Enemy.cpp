//
//  Enemy.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 26/1/25.
//

#include "Enemy.hpp"
#include <time.h>

Enemy::Enemy(int TYPE, SDL_Renderer* render, const char* path){
    enemyTexture = cpt::loadTexture(path, render);
    this->y = -50;
    int offsetX = 16;
    int offsetY = 16;
    enemyRect = {x, y, w, h};
    enemyHitBox = {enemyRect.x + offsetX, enemyRect.y + offsetY, 25,25};
}

Enemy::Enemy(SDL_Renderer* render){
    enemyTexture = cpt::loadTexture("./resources/enemy1.png",render);
    destroyTexure = cpt::loadTexture("./resources/Explosion.png", render);
    this->x = generateCoords();
    y = -100;
    enemyRect = {x*CELL_SIZE, y, w, h};
    enemyHealt = new Health(3);

    int offsetX = 16;
    int offsetY = 16;
    enemyHitBox = {enemyRect.x + offsetX, enemyRect.y + offsetY, 50,50};
}

Enemy::~Enemy(){
    if(enemyTexture != nullptr){
        SDL_DestroyTexture(enemyTexture);
        SDL_DestroyTexture(destroyTexure);
    }
    printf("Destroy Enemy\n");
}

int Enemy::generateCoords(){
    int coor = 1 + rand() % 27;
    printf("Generate enemy at: %d",x);
    return coor;
}

void Enemy::move(){
    if(enemyRect.y < 0){
        enemyRect.y+=1;
        enemyHitBox.y+=1;
    }
    enemyRect.x += velocity;
    enemyHitBox.x += velocity;
    if(enemyRect.x < 0 || enemyRect.x + cpt::CELL_SIZE > cpt::CELL_SIZE * cpt::CELL_COUNT){
        velocity *= -1;
        if(enemyRect.y >= 0) {
            enemyRect.y+=10;
            enemyHitBox.y+=10;
        }
    }
}

void Enemy::render(SDL_Renderer* render){
    SDL_RenderCopy(render, enemyTexture, NULL, &enemyRect);
    SDL_SetRenderDrawColor(render, 255,0,0,255);
    SDL_RenderDrawRect(render, &enemyHitBox);
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
    if(bullet == nullptr)bullet = new Bullet(enemyRect.x+25, enemyRect.y+8,r);
}