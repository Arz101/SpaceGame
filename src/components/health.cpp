#include "health.hpp"


Health::Health(int hits){
    this->countHits = hits;
}

Health::Health(int countHits, SDL_Renderer* render, const int CELL_SIZE){
    healthTexture = cpt::loadTexture("./resources/health.png", render);
    this->countHits = countHits;

    for(int i = 0; i < countHits; ++i){
        hp.push_back(new SDL_Rect{i*CELL_SIZE, 28*CELL_SIZE ,50,50});
    }
}

void Health::render(SDL_Renderer* render){
    for(auto it = hp.begin(); it != hp.end(); ++it){
        SDL_RenderCopy(render, healthTexture, nullptr, (*it));
    }
}

void Health::deleteHearth(){
    delete hp[hp.size()-1];
    hp.pop_back();
}

void Health::hit(){
    countHits--;
}

bool Health::dead(){
    return countHits <= 0? true : false;
}