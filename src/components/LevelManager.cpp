#include "LevelManager.hpp"

LevelManager::LevelManager(SDL_Window* mainWindow){
    SDL_HideWindow(window);
    UI::CButton* test = new UI::CButton("Test", SDL_Rect{3*CELL_SIZE, 25*CELL_SIZE, 100,100}, SDL_Color{128,128,128,128}, nullptr, render,[](){
        printf("Function");
    });


    if(!init()){
        printf("Manager could not be initialized");
    }
    else{
        bool running = true;
        SDL_Event e;

        while(running){
            Uint32 start_time = SDL_GetTicks();

            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    running = false;
                }
            }

            //Render Button
            SDL_SetRenderDrawColor(render, 255,255,255,0);
            SDL_RenderClear(render);

            test->render();

            SDL_RenderPresent(render);

            Uint32 frame_time = SDL_GetTicks() - start_time;
            if(frame_time < 16){
                SDL_Delay(16 - frame_time);
            }
        }
    }
}

bool LevelManager::init(){
    window = SDL_CreateWindow("Manager", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CELL_SIZE*CELL_COUNT,CELL_COUNT*CELL_SIZE, SDL_WINDOW_SHOWN);

    if(window == nullptr){
        printf("Window could not be initialized: %s", SDL_GetError());
        return false;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(render == nullptr){
        printf("Renderer could not be initialized: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(render, 255,255,255,0);

    return true;
}