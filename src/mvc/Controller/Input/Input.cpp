#include "Input.hpp"

Input::Input() {
    // init to false all the keys state
    for(auto i=0; i < sf::Keyboard::KeyCount; i++) {
        m_keys[i] = false;
        m_pressed_keys[i] = false;
    }

    // init to false all the buttons state
    for(auto i=0; i < sf::Mouse::ButtonCount; i++) {
        m_mouseButtons[i] = false;
        m_mouseButtons_pressed[i] = false;
    }
}

Input::~Input() {

}

void Input::update(Renderer& renderer) {
    sf::Event event;

    // reset key pressed
    for(auto i=0; i < sf::Keyboard::KeyCount; i++)
        m_pressed_keys[i] = false;

    // reset mouse button pressed
    for(auto i=0; i < sf::Mouse::ButtonCount; i++)
        m_mouseButtons_pressed[i] = false;

    // update
    while(renderer.getWindow()->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            renderer.close();
            return;
        }

        treatEvent(event);
    }
}

void Input::treatEvent(const sf::Event& event) {
    switch(event.type) {
        case sf::Event::KeyPressed:
            m_pressed_keys[event.key.code] = false;
            m_keys[event.key.code] = true;
            break;

        // keyboard's key released
        case sf::Event::KeyReleased:
            if(m_keys[event.key.code]) m_pressed_keys[event.key.code] = true;
            m_keys[event.key.code] = false;
            break;

        // mouse's button pressed
        case sf::Event::MouseButtonPressed:
            m_mouseButtons_pressed[event.mouseButton.button] = false;
            m_mouseButtons[event.mouseButton.button] = true;
            break;

        // mouse's button released
        case sf::Event::MouseButtonReleased:
            if(m_mouseButtons[event.mouseButton.button]) m_mouseButtons_pressed[event.mouseButton.button] = true;
            m_mouseButtons[event.mouseButton.button] = false;
            break;

        default:
            break;
    }
}

bool Input::isKeyDown(sf::Keyboard::Key key) const {
    return m_keys[key];
}

bool Input::isKeyUp(sf::Keyboard::Key key) const {
    return !m_keys[key];
}

bool Input::isKeyPressed(sf::Keyboard::Key key) const {
    return m_pressed_keys[key];
}

bool Input::isMouseButtonDown(sf::Mouse::Button btn) const {
    return m_mouseButtons[btn];
}

bool Input::isMouseButtonUp(sf::Mouse::Button btn) const {
    return !m_mouseButtons[btn];
}

bool Input::isMouseButtonPressed(sf::Mouse::Button btn) const {
    return m_mouseButtons_pressed[btn];
}