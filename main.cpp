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
#include "Interface.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* render = nullptr;
Interface* initInterface = nullptr;

const int CELL_SIZE = 25;
const int CELL_COUNT = 30;

bool init();
void close();
void gameLoop();

int main(int argc, char** argv) {


    if(!init()){
        close();
        return -1;
    }
    else{
        initInterface->initGame(nullptr);
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
        
        if(window == nullptr){
            printf("Window could not be initialized!! Error: %s", SDL_GetError());
            return false;
        }
        
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        
        if(render == nullptr){
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
        initInterface= new Interface(window, render);

    }
    return true;
}

void close(){
    SDL_DestroyWindow(window);
    
    SDL_DestroyRenderer(render);
    render = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}



void gameLoop(){
    bool running = true;
    SDL_Event e;

    while(running){
        Uint32 start_time = SDL_GetTicks();


        while (SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT){
                running = false;
            }
            initInterface->setEvent(e);
        }
        SDL_RenderClear(render);
        initInterface->render();
        SDL_RenderPresent(render);

        
        Uint32 frame_time = SDL_GetTicks() - start_time;
        if(frame_time < 16){
            SDL_Delay(16 - frame_time);
        }
    }
}

