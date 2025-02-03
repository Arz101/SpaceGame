#include "Rocket.hpp"

Rocket::Rocket(SDL_Renderer* render) : Enemy(1, render, "./resources/rocket.png") {
    time = 0.0f;
    rocketPositionX = 1 + rand() % 27;
}

void Rocket::move() {
    enemyRect.y++;
    enemyRect.x = static_cast<int>((std::sin((time) * 0.3) * 5) + cpt::CELL_SIZE + rocketPositionX*cpt::CELL_SIZE); // Onda sinusoidal
    time += 0.2f;
}

void Rocket::render(SDL_Renderer* render){
    SDL_RenderCopy(render, enemyTexture, nullptr,&enemyRect);
    SDL_SetRenderDrawColor(render, 0,255,0,0);
    SDL_RenderDrawRect(render, &enemyRect);
}