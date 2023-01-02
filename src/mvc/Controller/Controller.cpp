#include "Controller.hpp"

#include <iostream>

Controller::Controller():
    m_input(),
    m_mouseWasDragging(false)
{

}

Controller::~Controller() {

}


void Controller::update(Renderer& renderer, Model& model) {
    // update view input (poll event)
    m_input.update(renderer, model);

    if(renderer.isClosed() || model.getGui().isShowingHomeMenu()) {
        return;
    }

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

    // click [on antenna or something else]
    if(m_input.isMouseButtonPressed(sf::Mouse::Button::Left)) {
        const unsigned int menuWidth = 400;

        if(!m_mouseWasDragging) {
            if(model.getGui().noMenuOpened()) {
                auto& antennas = model.getNetwork().getAntennas();
                
                const int antAreaWidth = 50;
                const int antAreaHeight = 190;

                auto mouse = renderer.getPixelToWorldCoords(m_input.getMousePosition(), model.getMap());

                for(auto& antenna : antennas) {
                    const auto& pos = antenna->getPosition().coords();

                    if(
                        pos.x - antAreaWidth <= mouse.x && mouse.x <= pos.x + antAreaWidth &&
                        pos.y - antAreaHeight <= mouse.y && mouse.y <= pos.y
                    ) {
                        model.getGui().showAntennaDetailsMenu(antenna.get());
                        model.getMap().setPosition(
                            (antenna->getPosition().coords().x * model.getMap().getCurrentRatio() + menuWidth / 2),
                            antenna->getPosition().coords().y * model.getMap().getCurrentRatio()
                        );
                    }
                }
            }
            else {
                // we considere here only the right menu is opened (antenna's details)
                if(m_input.getMousePosition().x < (int)(renderer.getWindow()->getSize().x - menuWidth)) {
                    model.getGui().hideAntennaDetailsMenu();
                }
            }
        }

        m_mouseWasDragging = false;
        model.getMap().ungrab();
    }

    // grab map
    if(m_input.isMouseButtonDown(sf::Mouse::Button::Left)) {
        model.getMap().grab(m_input.getMousePosition());

        if(m_input.mouseMoved()) {
            m_mouseWasDragging = true;
            model.getMap().grabMove(m_input.getMousePosition());            
        }
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