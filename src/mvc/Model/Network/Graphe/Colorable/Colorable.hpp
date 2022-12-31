#ifndef COLORABLE_HPP
#define COLORABLE_HPP

#include <SFML/Graphics/Color.hpp>


class Colorable {
	public:
		Colorable();
		~Colorable();

        const sf::Color& getColor() const;

        void setColor(const sf::Color& color);

    protected:
        sf::Color m_color;
};

#endif // COLORABLE_HPP