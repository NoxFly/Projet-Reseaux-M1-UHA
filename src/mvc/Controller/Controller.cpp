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

    if(renderer.isClosed()) {
        return;
    }

    if(m_input.isMouseButtonPressed(sf::Mouse::Button::Left)) {
        if(model.getGui().isShowingShortcutMenu()) {
            const auto& mouse = m_input.getMousePosition();

            if(mouse.x < 80 && mouse.y < 80) {
                model.getGui().hideShortcutMenu();
            }
        }
    }

    if(model.getGui().isShowingHomeMenu()) {
        return;
    }

    //
    // |======| update models |======|
    //

    /////////////////
    // --- window ---

    // toggle window fullscreen
    if(m_input.isKeyPressed(sf::Keyboard::F)) {
        // buggy
        //renderer.toggleFullscreen();
    }


    if(m_input.isKeyPressed(sf::Keyboard::Escape)) {
        // model.getGui().hideAntennaDetailsMenu();
        model.getGui().showHomeMenu();
    }

    // freq filter
    //      previous
    if(m_input.isKeyPressed(sf::Keyboard::Num1)) {
        const int l = model.getNetwork().getFrequencies().size();
        int freq = renderer.getFreqFilter();
        int newFreq = (freq == -1)? l - 1 : freq - 1;
        renderer.setFreqFilter(newFreq);
    }
    //      next
    if(m_input.isKeyPressed(sf::Keyboard::Num2)) {
        const int l = model.getNetwork().getFrequencies().size();
        int freq = renderer.getFreqFilter();
        int newFreq = (freq < l - 1)? freq + 1 : -1;
        renderer.setFreqFilter(newFreq);
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

                const auto freqF = renderer.getFreqFilter();

                const auto filterFreq = (freqF != -1)
                    ? model.getNetwork().getFrequencies()[freqF]
                    : 0;

                for(auto& antenna : antennas) {
                    if(filterFreq && antenna->getFreq() != filterFreq) {
                        continue;
                    }

                    const auto& pos = antenna->getPosition().pixels();

                    if(
                        pos.x - antAreaWidth <= mouse.x && mouse.x <= pos.x + antAreaWidth &&
                        pos.y - antAreaHeight <= mouse.y && mouse.y <= pos.y
                    ) {
                        model.getGui().showAntennaDetailsMenu(antenna.get());
                        model.getMap().setPosition(
                            (antenna->getPosition().pixels().x * model.getMap().getCurrentRatio() + menuWidth / 2),
                            antenna->getPosition().pixels().y * model.getMap().getCurrentRatio()
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