#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>

#include "Renderer.hpp"


class Input {
	public:
		Input();
		~Input();
        
        void update(Renderer& renderer);

        // getters
        /** return a bool either a specific key/button is downed, pressed, or released
         * @param   sf::Keyboard::Key   target key
         * @return  bool                key state
         */
        bool isKeyDown(sf::Keyboard::Key key) const; // key is down
        bool isKeyUp(sf::Keyboard::Key key) const; // key is released
        bool isKeyPressed(sf::Keyboard::Key key) const; // key is pressed
        bool isMouseButtonDown(sf::Mouse::Button key) const; // mouse button down
        bool isMouseButtonUp(sf::Mouse::Button key) const; // mouse button released
        bool isMouseButtonPressed(sf::Mouse::Button btn) const; // mouse button pressed

        // keyboard keys (true = down, false = up)
        bool m_keys[sf::Keyboard::KeyCount];
        bool m_pressed_keys[sf::Keyboard::KeyCount];
        // mouse buttons (true = down, false = up)
        bool m_mouseButtons[sf::Mouse::ButtonCount];
        bool m_mouseButtons_pressed[sf::Mouse::ButtonCount];

    private:
        void treatEvent(const sf::Event& event);
};

#endif // INPUT_HPP