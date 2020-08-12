#include "ui/ui_layer.hpp"
#include "SFML/Graphics.hpp"
#include "render/draw_call.hpp"
#include "utils/debug.hpp"
UILayer::UILayer(){
    Info("UILayer: created");
}
UILayer::~UILayer(){
    Info("UILayer: destroyed");
}

void UILayer::on_render(){
    m_controller->render();
}

void UILayer::on_update(float dt){
    m_controller->update(dt);
}   


void UILayer::set_controller(UIController* c){
    m_controller=c;
}