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
        m_pressed_mouseButtons[i] = false;
    }
}

Input::~Input() {

}

void Input::update(Renderer& renderer, Model& model) {
    sf::Event event;

    // reset key pressed
    for(auto i=0; i < sf::Keyboard::KeyCount; i++)
        m_pressed_keys[i] = false;

    // reset mouse button pressed
    for(auto i=0; i < sf::Mouse::ButtonCount; i++)
        m_pressed_mouseButtons[i] = false;

    m_hasMouseMoved = false;
    m_hasMouseWheeled = false;

    auto& gui = model.getGui();

    // update
    while(renderer.getWindow() && renderer.getWindow()->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            renderer.close();
            return;
        }

        treatEvent(event, renderer);

        gui.handleEvent(event);
    }
}

void Input::treatEvent(const sf::Event& event, Renderer& renderer) {
    sf::Vector2i mousep;

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
            m_pressed_mouseButtons[event.mouseButton.button] = false;
            m_mouseButtons[event.mouseButton.button] = true;
            break;

        // mouse's button released
        case sf::Event::MouseButtonReleased:
            if(m_mouseButtons[event.mouseButton.button])
                m_pressed_mouseButtons[event.mouseButton.button] = true;
            m_mouseButtons[event.mouseButton.button] = false;
            break;

        case sf::Event::MouseMoved:
            m_hasMouseMoved = true;
            mousep = sf::Mouse::getPosition(*renderer.getWindow());
            m_mouseOffset = m_mousePosition - mousep;
            m_mousePosition = mousep;
            break;

        case sf::Event::MouseWheelScrolled:
            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                m_hasMouseWheeled = true;
                m_mouseWheelDelta = event.mouseWheelScroll.delta;
            }
            break;

        default:
            break;
    }
}

bool Input::isKeyDown(const sf::Keyboard::Key key) const {
    return m_keys[key];
}

bool Input::isKeyUp(const sf::Keyboard::Key key) const {
    return !m_keys[key];
}

bool Input::isKeyPressed(const sf::Keyboard::Key key) const {
    return m_pressed_keys[key];
}

bool Input::isMouseButtonDown(const sf::Mouse::Button btn) const {
    return m_mouseButtons[btn];
}

bool Input::isMouseButtonUp(const sf::Mouse::Button btn) const {
    return !m_mouseButtons[btn];
}

bool Input::isMouseButtonPressed(const sf::Mouse::Button btn) const {
    return m_pressed_mouseButtons[btn];
}

bool Input::mouseMoved() const {
    return m_hasMouseMoved;
}

bool Input::mouseWheeled() const {
    return m_hasMouseWheeled;
}

const sf::Vector2i& Input::getMousePosition() const {
    return m_mousePosition;
}

const sf::Vector2i& Input::getMouseOffset() const {
    return m_mouseOffset;
}

float Input::getMouseWheelDirection() const {
    return m_mouseWheelDelta;
}