#include "Controller.hpp"
#include <iostream>

Controller::Controller():
    m_input()
{

}

Controller::~Controller() {

}


void Controller::update(Renderer& renderer, Model& model) {
    // update view input (poll event)
    m_input.update(renderer);


    // update models
    if(m_input.isKeyPressed(sf::Keyboard::F)) {
        renderer.toggleFullscreen();
    }

    if(m_input.isMouseButtonDown(sf::Mouse::Button::Left)) {
        model.getMap().grab(m_input.getMousePosition());

        if(m_input.mouseMoved()) {
            model.getMap().grabMove(m_input.getMousePosition());
        }
    }
    else {
        model.getMap().ungrab();
    }

    if(m_input.mouseWheeled()) {
        (m_input.getMouseWheelDirection() > 0)
            ? model.getMap().zoomIn()
            : model.getMap().zoomOut();
    }
}