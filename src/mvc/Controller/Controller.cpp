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
    m_input.update(renderer, model);



    //
    // |======| update models |======|
    //

    /////////////////
    // --- window ---

    // toggle window fullscreen
    if(m_input.isKeyPressed(sf::Keyboard::F)) {
        renderer.toggleFullscreen();
    }


    //////////////
    // --- map ---

    // grab map
    if(m_input.isMouseButtonDown(sf::Mouse::Button::Left)) {
        model.getMap().grab(m_input.getMousePosition());

        if(m_input.mouseMoved()) {
            model.getMap().grabMove(m_input.getMousePosition());
        }
    }
    else {
        model.getMap().ungrab();
    }

    // zoom map
    if(m_input.mouseWheeled()) {
        (m_input.getMouseWheelDirection() > 0)
            ? model.getMap().zoomIn()
            : model.getMap().zoomOut();
    }

    //////////////////
    // --- network ---

    // toggle antennas view
    if(m_input.isKeyPressed(sf::Keyboard::A)) {
        model.getNetwork().showAntennas(!model.getNetwork().shouldShowAntennas());
    }

    // toggle ranges view
    if(m_input.isKeyPressed(sf::Keyboard::R)) {
        model.getNetwork().showRanges(!model.getNetwork().shouldShowRanges());
    }

    // toggle colors view
    if(m_input.isKeyPressed(sf::Keyboard::C)) {
        model.getNetwork().showColors(!model.getNetwork().shouldShowColors());
    }
}