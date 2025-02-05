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
#include "Rocket.hpp"
#include "SDL2/SDL_ttf.h"
#include "ManagerIncludes/Button.hpp"
#include "LevelManager.hpp"

Player* player = nullptr;
Enemy* enemy = nullptr;
std::vector<Enemy*> enemies;
Rocket* rocket = nullptr;

UI::Button* managerButton = nullptr;


SDL_Window* window = nullptr;
SDL_Renderer* render = nullptr;

const int CELL_SIZE = 25;
const int CELL_COUNT = 30;

bool init();
void close();
void gameLoop();
void initEntities();
void generateEnemies(SDL_Renderer*);
void loadText(int&);

int kills = 0;

SDL_Texture* loadTexture(const char*);

int main(int argc, char** argv) {
    // insert code here...
    managerButton = new Button("Test", SDL_Rect{25*CELL_SIZE, 25*CELL_SIZE, 100,100}, SDL_Color{128,128,128,128}, nullptr, [](){
        LevelManager* manager = new LevelManager(window);
    });

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
            printf("IMG could not be initalized! Error: %s", IMG_GetError());
            return false;
        }

        if(TTF_Init() == -1){
            printf("Error: %s", TTF_GetError());
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
    rocket = new Rocket(render);
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
            managerButton->OnClick(e);
            if(currentTime > lastTime + interval){
                player->attack(e);
                lastTime = currentTime;
            }
        }
        //Update
        rocket->move();
        //Enemy ATTACK
        if(EnemyCurrentTime > EnemyLasTime + 200){
            for(auto it = enemies.begin(); it != enemies.end(); ++it){
                (*it)->attack();
            }
            EnemyLasTime = EnemyCurrentTime;
        }
        
        if(!player->bulletsIsEmpty()){
            //Obtener las balas del jugador
            auto& bullet = player->getBullets();
            for(auto it = bullet.begin(); it != bullet.end(); ++it){
                (*it)->bulletMove(); //Mover las balas
                if((*it)->getY() < 0){ //Verificar si las balas salen de los limites
                    delete *it; //Eliminar la bala
                    bullet.erase(it); //Eliminar la bala de la cola
                }
                //Verificar si existen enemigos
                else if(enemies.size() > 0){
                    for(auto itEnemy = enemies.begin(); itEnemy != enemies.end(); ++itEnemy){
                        //Verificar si las balas del jugador colisionaron con algun enemigo
                        if(cpt::isCollision((*it)->getRect(), (*itEnemy)->getRect())){
                            // Si la bala del jugador colisiono con el enemigo, bajar la vida del enemigo
                            (*itEnemy)->setDestroyed(); //El enemigo aguanta 3 golpes, con cada golpe se le restara 1

                            //Destruir la bala del jugador
                            //player->destroyBulletByEnemyCollision((&*it));
                            //it = bullet.erase(it); // Eliminar la bala de la cola del jugador
                            //break;
                        }
                    }
                }
            }
        }

        //Verificar si existen enemigos
        if(enemies.size() > 0){
            for(auto it = enemies.begin(); it != enemies.end(); ++it){
                //Verificar si existen balas enemigas
                if((*it)->getBullet() != nullptr){
                    //Verificar si el jugador colisiono con alguna bala enemiga
                    if(cpt::isCollision(player->getRect(), (*it)->getBullet()->getRect())){
                        player->getHealth()->deleteHearth(); // Si la colision es verdadera, eliminar una vida
                        (*it)->destroyBulletByPlayerCollision(); // Destruir la bala con la cual colisiono
                        break; //Salir del bucle
                    }
                }
            }
        }
        //Render
        SDL_SetRenderDrawColor(render, 255,255,255,0);
        SDL_RenderClear(render);
        player->render(render);
        rocket->render(render);

        //Verificar si el jugador ha atacando
        if(player->playerAttack){
            //Obtener las la balas disparadas
            auto& bullet = player->getBullets();
            for(auto it = bullet.begin(); it != bullet.end(); it++){
                //Renderizar balas del jugador
                (*it)->render(render);
            }
        }

        //Verificar si existen enemigos
        if(enemies.size() > 0){
            for(auto it = enemies.begin(); it != enemies.end();){
                (*it)->move(); //Mover el enemigo
                (*it)->render(render); //Renderizar el enemigo
                
                //Verificar si el enemigo fue destruido
                if((*it)->isDestroyed()){
                    //Ejecutar animacion de explocion
                    (*it)->enemyDestroy(render);
                    delete *it; // Eliminar el enemigo
                    it = enemies.erase(it); //Eliminarlo del vector
                    kills+=10; //aumentar los puntos
                }
                else ++it; // Si el enemigo actual no fue destruido aumentamos

                if(enemies.size() <= 0){
                    generateEnemies(render);
                }
            }
        }
        loadText(kills);

        managerButton->render(render);
        SDL_RenderPresent(render);
        
        Uint32 frame_time = SDL_GetTicks() - start_time;
        if(frame_time < 16){
            SDL_Delay(16 - frame_time);
        }
    }
}

void loadText(int& kills){
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf",24);
    SDL_Texture* text = cpt::generteText(render, font, ("Points: " + std::to_string(kills)).c_str(), SDL_Color{0,0,0,255});
    SDL_Rect textRect = {0,0, 100,20};

    SDL_RenderCopy(render, text, nullptr, &textRect);
}