//
//  Player.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#include "Player.hpp"

Player::Player(){
    
}

Player::Player(int x, int y, int w, int h, SDL_Renderer* render, const int CELL_SIZE){
    playerRect = {x,y,w,h};
    this->playerTexture = cpt::loadTexture("./resources/nave.png", render);
    hpPlayer = new Health(10, render, CELL_SIZE);
    
    int offsetX = 34;
    int offsetY = 16;
    playerHitBox ={playerRect.x + offsetX, playerRect.y + offsetY, 35,45};
}

Player::~Player(){
    if(playerTexture != NULL){
        SDL_DestroyTexture(playerTexture);
        playerTexture = NULL;
        printf("Destroy Player\n");
    }
}

void Player::move(SDL_Event &e){
    switch (e.key.keysym.sym) {
        case SDLK_UP:
            printf("Key Up is pressed \n");
            playerRect.y -= velocity;
            playerHitBox.y -= velocity;
            break;
        case SDLK_DOWN:
            printf("Key Down is pressed\n");
            playerRect.y += velocity;
            playerHitBox.y += velocity;
            break;
        case SDLK_LEFT:
            printf("Key Left is pressed\n");
            playerRect.x -= velocity;
            playerHitBox.x -= velocity;
            break;
        case SDLK_RIGHT:
            printf("Key right is pressed\n");
            playerRect.x += velocity;
            playerHitBox.x += velocity;

            break;
    }
}

void Player::attack(SDL_Event& e){
    if(e.key.keysym.sym == SDLK_x){
        printf("Attack!\n");
        Bullet* bullet = new Bullet(playerRect.x+25, playerRect.y+8);
        bullets.push_back(bullet);
        playerAttack = true;
    }
}

void Player::render(SDL_Renderer* render){
    if(SDL_RenderCopy(render, playerTexture, nullptr, &playerRect) != 0){
        printf("Render Copy Error: %s\n", SDL_GetError());
    }
    SDL_SetRenderDrawColor(render, 255,0,0,255);
    SDL_RenderDrawRect(render, &playerHitBox);
    hpPlayer->render(render);
}

SDL_Texture* Player::getTexture(){
    if(playerTexture == NULL){
        printf("Player Texture is NULL");
        return NULL;
    }
    
    return playerTexture;
}

int Player::getX(){
    return playerRect.x;
}

int Player::getY(){
    return playerRect.y;
}

void Player::destroyBullet(){
    bullets.pop_front();
}

bool Player::bulletsIsEmpty(){
    return bullets.size() < 0? true:false;
}

std::deque<Bullet*>& Player::getBullets(){
    return bullets;
}

void Player::destroyBulletByEnemyCollision(Bullet** b){
    if(*b != nullptr){
        delete *b;
        *b = nullptr;
    }
}