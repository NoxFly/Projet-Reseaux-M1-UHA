#include "Controller.hpp"

Controller::Controller() {

}

Controller::~Controller() {

}


void Controller::update(sf::RenderWindow* window, Model model, bool* running) {
    (void)model;

    // update view input (poll event)
    sf::Event e;

    while(window->pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            *running = false;
        }
    }
}