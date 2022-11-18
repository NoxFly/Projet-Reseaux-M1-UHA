#include "Renderer.hpp"



Renderer::Renderer() {
    
}

Renderer::~Renderer() {
    
}

void Renderer::render(sf::RenderWindow* window, Model& model) {
    (void)window;
    
    auto& gui = model.getGui().getTgui();

    gui.draw();

}