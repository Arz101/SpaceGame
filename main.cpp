//
//  main.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 25/1/25.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Components.hpp"

Player* player = nullptr;
Enemy* enemy = nullptr;
std::vector<Enemy*> enemies;


SDL_Window* window = nullptr;
SDL_Renderer* render = nullptr;

const int CELL_SIZE = 25;
const int CELL_COUNT = 30;

bool init();
void close();
void gameLoop();
void initEntities();
void generateEnemies(SDL_Renderer*);

SDL_Texture* loadTexture(const char*);

int main(int argc, char** argv) {
    // insert code here...
    if(!init()){
        close();
        return -1;
    }
    else{
        initEntities();
        gameLoop();
    }
    close();
    return 0;
}

bool init(){
    srand(static_cast<unsigned int>(time(nullptr)));

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: %s", SDL_GetError());
        return false;
    }
    else{
        window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CELL_SIZE*CELL_COUNT, CELL_SIZE*CELL_COUNT, SDL_WINDOW_SHOWN);
        
        if(window == NULL){
            printf("Window could not be initialized!! Error: %s", SDL_GetError());
            return false;
        }
        
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        
        if(render == NULL){
            printf("Render could not be intialized! Error: %s ", SDL_GetError());
            return false;
        }
        
        SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
        
        if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
            printf("IMG could not be initalized! Error: %s", SDL_GetError());
            return false;
        }
    }
    return true;
}



SDL_Texture* loadTexture(const char* path){
    
    SDL_Texture* chargedTexture = nullptr;
    
    SDL_Surface* chargedSurface = IMG_Load(path);
    
    if(chargedSurface != nullptr){
        
        chargedTexture = SDL_CreateTextureFromSurface(render, chargedSurface);
        
        if(chargedTexture == nullptr){
            printf("Texture could not be initialized! Error: %s", SDL_GetError());
            return nullptr;
        }
        
        SDL_FreeSurface(chargedSurface);
    }
    else {
        printf("Error texture: %s", SDL_GetError());
        return nullptr;
    }
    return chargedTexture;
}

void initEntities(){
    int x = 6, y = 27;
    player = new Player(x * CELL_SIZE, y * CELL_SIZE, 100, 100, render, CELL_SIZE);
}

void generateEnemies(SDL_Renderer* render){
    for(int i = 0; i < 3; i++)
        enemies.push_back(new Enemy(render));
}


void close(){
    SDL_DestroyWindow(window);
    
    SDL_DestroyRenderer(render);
    render = NULL;

    delete player;
    player = nullptr;
    
    delete enemy;
    enemy = nullptr;
    
    SDL_Quit();
    IMG_Quit();
}



void gameLoop(){
    bool running = true;
    
    Uint32 lastTime = 0;
    Uint32 EnemyLasTime = 0;
    Uint32 EnemyCurrentTime = 0;
    Uint32 interval = 200;
    Uint32 currentTime = 0;
    
    SDL_Event e;
    if(enemies.size() <= 0) generateEnemies(render); 

    while(running){
        Uint32 start_time = SDL_GetTicks();
        
        currentTime = SDL_GetTicks();
        EnemyCurrentTime = SDL_GetTicks();
        while (SDL_PollEvent(&e) > 0) {
            if(e.type == SDL_QUIT){
                running = false;
            }
            player->move(e);

            if(currentTime > lastTime + interval){
                player->attack(e);
                lastTime = currentTime;
            }
        }
        //Update

        //Enemy ATTACK
        if(EnemyCurrentTime > EnemyLasTime + 200){
            for(auto it = enemies.begin(); it != enemies.end(); ++it){
                (*it)->attack();
            }
            EnemyLasTime = EnemyCurrentTime;
        }
        
        if(!player->bulletsIsEmpty()){
            auto& bullet = player->getBullets();
            for(auto it = bullet.begin(); it != bullet.end(); it++){
                (*it)->bulletMove();
                if((*it)->getY() < 0){
                    delete *it;
                    bullet.erase(it);
                }
                else if(enemies.size() > 0){
                    for(auto itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++){
                        if(cpt::isCollision((*it)->getRect(), (*itEnemy)->getRect())){
                            // Arreglar esto ->
                            (*itEnemy)->setDestroyed();
                            break;
                        }
                    }
                }
            }
        }

    
        if(enemies.size() > 0){
            for(auto it = enemies.begin(); it != enemies.end(); ++it){
                if((*it)->getBullet() != nullptr){
                    if(cpt::isCollision(player->getRect(), (*it)->getBullet()->getRect())){
                        player->getHealth()->deleteHearth();
                        (*it)->destroyBulletByPlayerCollision();
                        break;
                    }
                }
            }
        }
        //Render
        SDL_RenderClear(render);
        player->render(render);

        //Verificar si el jugador ha atacando
        if(player->playerAttack){
            //Obtener las la balas disparadas
            auto& bullet = player->getBullets();
            for(auto it = bullet.begin(); it != bullet.end(); it++){
                //Renderizar balas del jugador
                (*it)->render(render);
            }
        }

        if(enemy != nullptr)enemy->render(render);
        if(enemies.size() > 0){
            for(auto it = enemies.begin(); it != enemies.end();){
                (*it)->move();
                (*it)->render(render);
                
                if((*it)->isDestroyed()){
                    (*it)->enemyDestroy(render);
                    delete *it;
                    it = enemies.erase(it);
                }
                else ++it;

                if(enemies.size() <= 0){
                    generateEnemies(render);
                }
            }
        }
        
        SDL_RenderPresent(render);
        
        Uint32 frame_time = SDL_GetTicks() - start_time;
        if(frame_time < 16){
            SDL_Delay(16 - frame_time);
        }
    }
}
