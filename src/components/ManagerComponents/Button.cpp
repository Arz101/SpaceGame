#include "ManagerIncludes/Button.hpp"

namespace UI{

CButton::CButton(const char* _tittle, SDL_Rect rect, SDL_Color color, SDL_Texture* texture, SDL_Renderer* r,std::function<void()> EventHandler = nullptr) 
: CComponent(rect, color, texture, r), tittle(_tittle) {}

void CButton::render(){
    if(this->CC_Texture == nullptr){
        if(state == State::Normal)
            SDL_SetRenderDrawColor(r, this->CC_Color.r, this->CC_Color.g, this->CC_Color.b, this->CC_Color.a);
        
        else if(state == State::Horverd) {
            Uint32 colorA = this->CC_Color.a;
            if(colorA == 255) colorA-=100;
            else {
                if(colorA == 0) colorA+=100; 
            }

            SDL_SetRenderDrawColor(r, 171, 171, 171, 171);
        
        }
        if(SDL_RenderFillRect(r, &CC_Rect) == 0){
        }
    } else{
        SDL_RenderCopy(r, CC_Texture, nullptr, &CC_Rect);
    }
    setButtonTittle();
}

void CButton::setButtonTittle(){
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf",24);
    
    if(!font){
        printf("font error: %s", TTF_GetError());
    }

    this->tittleTexture = cpt::generteText(r, font, tittle, SDL_Color{0,0,0,255});
    SDL_Rect rectTittle = {CC_Rect.x+ 3, CC_Rect.y+3, 50,20};
    
    if(tittleTexture == nullptr){
        printf("Error tittle texture could not be initialized: %s\n", SDL_GetError());
        return;
    } else SDL_RenderCopy(r, this->tittleTexture, nullptr, &rectTittle);
}

void CButton::EventHandler(SDL_Event& e){
    if(e.type == SDL_MOUSEMOTION){
        if(isClicked(e.button.x, e.button.y)){
            state = State::Horverd;
            printf("hereee\n");
        }else state = State::Normal;
    }
    
    if(e.type == SDL_MOUSEBUTTONDOWN){

    } else{
        printf("No function assign\n");
    }
}

bool CButton::isClicked(int& x, int& y) {
    return (x >= CC_Rect.x && x <= CC_Rect.x + CC_Rect.w &&
    y >= CC_Rect.y && y <= CC_Rect.y + CC_Rect.h);
}

}