#include "ManagerIncludes/Panel.hpp"

namespace UI{

CPanel::CPanel(SDL_Rect rectPanel, SDL_Color color){
    this->rectPanel = rectPanel;
    this->color = color;
}


void CPanel::addButton(Button* newButton){
    buttons.push_back(buttons);
}

void CPanel::addPanel(CPanel* newPanel){
    panels.push_back(newPanel);
}

void CPanel::render(SDL_Renderer* render){
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, &rectPanel);

    if(buttons.size() > 0){
        for(auto it = buttons.begin(); it != buttons.end(); ++it){
            if((*it)->getVisible()) 
                (*it)->render(render);
        }
    }

    if(panels.size() > 0){
        for(auto it = panels.begin(); it != panels.end(); ++it){
            if((*it)->getVisible())
                (*it)->render(render);
        }
    }
}

void CPanel::setVisible(bool e){
    this->visible = e;
}

}