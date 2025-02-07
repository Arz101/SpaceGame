#include "Game.hpp"


Game::Game(SDL_Renderer* _r)
: r(_r){
    int x = 6, y = 27;
    player = new Player(x * cpt::CELL_SIZE, y * cpt::CELL_SIZE, 100, 100, r, CELL_SIZE);
    rocket = new Rocket(r);
}

void Game::counters(Uint32& enemyCounter, Uint32 currentCounter){
    this->currentTime = currentCounter;
    this->EnemyCurrentTime = enemyCounter;
}

void Game::generateEnemies(){
    for(int i = 0; i < 3; i++)
        enemies.push_back(new Enemy(r));
}

void Game::logic(){
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
}

void Game::render(){
    SDL_SetRenderDrawColor(r, 255,255,255,0);
    
    SDL_RenderClear(r);
    player->render(r);
    rocket->render(r);

    //Verificar si el jugador ha atacando
    if(player->playerAttack){
        //Obtener las la balas disparadas
        auto& bullet = player->getBullets();
        for(auto it = bullet.begin(); it != bullet.end(); it++){
            //Renderizar balas del jugador
            (*it)->render(r);
        }
    }

        //Verificar si existen enemigos
    if(enemies.size() > 0){
        for(auto it = enemies.begin(); it != enemies.end();){
            (*it)->move(); //Mover el enemigo
            (*it)->render(r); //Renderizar el enemigo
                
            //Verificar si el enemigo fue destruido
            if((*it)->isDestroyed()){
                //Ejecutar animacion de explocion
                (*it)->enemyDestroy(r);
                delete *it; // Eliminar el enemigo
                it = enemies.erase(it); //Eliminarlo del vector
                kills+=10; //aumentar los puntos
            }
            else ++it; // Si el enemigo actual no fue destruido aumentamos

            if(enemies.size() <= 0){
                generateEnemies();
            }
        }
    }
    loadText(kills);

    SDL_RenderPresent(r);
}

void Game::event(SDL_Event& e){
    player->move(e);
    if(currentTime > lastTime + interval){
        player->attack(e);
        lastTime = currentTime;
    }
}

void Game::loadText(int& kills){
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf",24);
    SDL_Texture* text = cpt::generteText(r, font, ("Points: " + std::to_string(kills)).c_str(), SDL_Color{0,0,0,255});
    SDL_Rect textRect = {0,0, 100,20};

    SDL_RenderCopy(r, text, nullptr,  &textRect);
}

void Game::close(){    
    SDL_DestroyRenderer(r);

    delete player;
    player = nullptr;
    delete rocket;
    rocket = nullptr;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}
