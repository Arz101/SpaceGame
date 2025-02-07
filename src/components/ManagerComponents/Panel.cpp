#include "ManagerIncludes/Panel.hpp"

namespace UI{

CPanel::CPanel(SDL_Rect rec, SDL_Color color, SDL_Texture* texture, SDL_Renderer* r)
: CComponent(rec, color, texture, r){}


void CPanel::addButton(CButton* newButton){
    buttons.push_back(newButton);
}

void CPanel::addPanel(CPanel* newPanel){
    panels.push_back(newPanel);
}

void CPanel::render() {
    if(CC_Texture == nullptr){
        SDL_SetRenderDrawColor(r, CC_Color.r, CC_Color.g, CC_Color.b, CC_Color.a);
        SDL_RenderFillRect(r, &CC_Rect);
    } else{
        SDL_RenderCopy(r, CC_Texture, nullptr, &CC_Rect);
    }


    if(buttons.size() > 0){
        for(auto it = buttons.begin(); it != buttons.end(); ++it){
            if(visible) 
                (*it)->render();            
        }
    }
    if(panels.size() > 0){
        for(auto it = panels.begin(); it != panels.end(); ++it){
            if(visible)
                (*it)->render();
        }
    }
}

void CPanel::EventHandler(SDL_Event& e){
    for(auto& it: buttons){
        it->EventHandler(e);
    }
}

}