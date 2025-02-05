#include "ManagerIncludes/Button.hpp"

namespace UI{

Button::Button(const char* tittle, SDL_Rect rect, SDL_Color color, SDL_Texture* texture, std::function<void()> EventHandler = nullptr){
    if(texture != nullptr){
        this->buttonTexture = texture;
    } else this->buttonTexture = nullptr;
    
    this->buttonColor = color;

    this->buttonRect = rect;
    this->EventHandler = EventHandler;
}

void Button::render(SDL_Renderer* render){
    setButtonTittle(render);
    if(this->buttonTexture == nullptr){
        SDL_SetRenderDrawColor(render, this->buttonColor.r, this->buttonColor.g, this->buttonColor.b, this->buttonColor.a);
        SDL_RenderFillRect(render, &buttonRect);
    } else{
        SDL_RenderCopy(render, buttonTexture, nullptr, &buttonRect);
    }
}

void Button::setButtonTittle(SDL_Renderer* render){
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf",24);
    this->titileTexture = cpt::generteText(render, font, tittle, SDL_Color{0,0,0,255});
    SDL_Rect rectTittle = {buttonRect.x - 3, buttonRect.y, 20,20};
    
    if(titileTexture == nullptr){
        //printf("Error tittle texture could not be initialized: %s\n", SDL_GetError());
        return;
    } else SDL_RenderCopy(render, this->titileTexture, nullptr, &rectTittle);
}

void Button::OnClick(SDL_Event& e){
    if(e.type == SDL_MOUSEBUTTONDOWN){
        int mouseX = e.button.x;
        int mouseY = e.button.y;
        if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w && mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
            EventHandler(); // Ejecutar la función asignada
        }
    } else{
        printf("No function assign\n");
    }
}

void Button::setVisible(bool e){
    this->visible = e;
}

}