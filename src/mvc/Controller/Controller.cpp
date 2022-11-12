#include "Controller.hpp"
#include <iostream>

Controller::Controller() {

}

Controller::~Controller() {

}


void Controller::update(Renderer& renderer, Model model) {
    (void)model;

    // update view input (poll event)
    m_input.update(renderer);

    if(m_input.isKeyPressed(sf::Keyboard::F)) {
        renderer.toggleFullscreen();
    }
}