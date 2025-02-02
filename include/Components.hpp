//
//  Components.hpp
//  SkyInvaders
//
//  Created by Adrian Rodriguez on 26/1/25.
//

#ifndef Components_hpp
#define Components_hpp

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

namespace cpt{

const int CELL_SIZE = 25;
const int CELL_COUNT = 30;

enum BulletTypes{
    ENEMYBULLET,
    PLAYERBULLET_1
};
    
SDL_Texture* loadTexture(const char*, SDL_Renderer*);
SDL_bool isCollision(const SDL_Rect&, const SDL_Rect&);

}
#endif /* Components_hpp */
