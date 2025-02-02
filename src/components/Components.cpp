//
//  Components.cpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 26/1/25.
//

#include "Components.hpp"

namespace cpt {

SDL_Texture* loadTexture(const char* path, SDL_Renderer* render){
    SDL_Texture* chargedTexture = nullptr;
    
    SDL_Surface* chargedSurface = IMG_Load(path);
    
    if(chargedSurface != nullptr){
        
        chargedTexture = SDL_CreateTextureFromSurface(render, chargedSurface);
        
        if(chargedTexture == nullptr){
            printf("Error Creating texture: %s", SDL_GetError());
            return nullptr;
        }
    }else {
        printf("Error Creating texture: %s", SDL_GetError());
        return nullptr;
    }
    
    return chargedTexture;
}

SDL_bool isCollision(const SDL_Rect& a, const SDL_Rect& b){
    return SDL_HasIntersection(&b,&a);
}

}
