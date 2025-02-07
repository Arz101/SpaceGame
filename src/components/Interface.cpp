#include "Interface.hpp"

Interface::Interface(SDL_Window* w, SDL_Renderer* r){
    this->window = w;
    this->r = r;
    SDL_GetWindowSize(window, &width, &height);
    mainPanel = new UI::CPanel(SDL_Rect{0,0,width,height}, SDL_Color{0,0,0,255}, cpt::loadTexture("./resources/star.png", r), this->r);
    mainPanel->setVisible(true);   
    createButtons();
}

void Interface::render(){
    mainPanel->render();
}

void Interface::createButtons(){
    UI::CButton* playButton = new UI::CButton("Play",{20,20,200,100}, {255,255,255,0},nullptr, this->r,[this](){
        if(this->GAME)
            this->GAME();
    });
    playButton->setVisible(true);

    mainPanel->addButton(playButton);

    UI::CButton* playManagement = new UI::CButton("Manage",{18*cpt::CELL_SIZE,20,200,100}, {255,255,255,0},nullptr, this->r,[this](){
        initManage();
    });

    playManagement->setVisible(true);

    mainPanel->addButton(playManagement);
}

void Interface::initGame(std::function<void()> g){
    printf("Init Game!!1\n");
    this->GAME = std::move(g);
    if (this->GAME) {
        printf("Game function successfully assigned.\n");
    } else {
        printf("Warning: Game function is empty.\n");
    }
}

void Interface::initManage(){
    printf("Init Level Management!!!\n");
}

void Interface::setEvent(SDL_Event& e){
    mainPanel->EventHandler(e);
}