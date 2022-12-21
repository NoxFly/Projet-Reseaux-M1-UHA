#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Graphics.hpp>

#include "mvc/Renderer/Renderer.hpp"


class Input {
	public:
		Input();
		~Input();
        
        void update(Renderer& renderer, Model& model);

        // getters
        /** return a bool either a specific key/button is downed, pressed, or released
         * @param   sf::Keyboard::Key   target key
         * @return  bool                key state
         */
        bool isKeyDown(const sf::Keyboard::Key key) const; // key is down
        bool isKeyUp(const sf::Keyboard::Key key) const; // key is released
        bool isKeyPressed(const sf::Keyboard::Key key) const; // key is pressed
        bool isMouseButtonDown(const sf::Mouse::Button key) const; // mouse button down
        bool isMouseButtonUp(const sf::Mouse::Button key) const; // mouse button released
        bool isMouseButtonPressed(const sf::Mouse::Button btn) const; // mouse button pressed
        bool mouseMoved() const;
        bool mouseWheeled() const;
        const sf::Vector2i& getMousePosition() const;
        const sf::Vector2i& getMouseOffset() const;
        float getMouseWheelDirection() const;

    private:
        void treatEvent(const sf::Event& event, Renderer& renderer);

        // keyboard keys (true = down, false = up)
        bool m_keys[sf::Keyboard::KeyCount];
        bool m_pressed_keys[sf::Keyboard::KeyCount];
        // mouse buttons (true = down, false = up)
        bool m_mouseButtons[sf::Mouse::ButtonCount];
        bool m_pressed_mouseButtons[sf::Mouse::ButtonCount];
        bool m_hasMouseMoved;
        bool m_hasMouseWheeled;
        float m_mouseWheelDelta;
        sf::Vector2i m_mousePosition;
        sf::Vector2i m_mouseOffset;
};

#endif // INPUT_HPP