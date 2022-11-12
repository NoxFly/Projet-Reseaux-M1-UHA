#include "Renderer.hpp"

#include <iostream>


Renderer::Renderer():
    m_fonts{}, m_background(232, 234, 237)
{
    // init font(s)
    sf::Font font;

    std::string fontName = "Roboto";
    std::string fontPath = "res/fonts/Roboto-Bold.ttf";

    if(!font.loadFromFile(fontPath)) {
#ifdef DEBUG
        std::err << "Failed to load font " << fontPath << std::endl;
#endif
    }
    else {
        m_fonts[fontName] = font;
    }
}

Renderer::~Renderer() {
    
}

void Renderer::render(sf::RenderWindow* window, Model& model) {
    window->clear(m_background);

    // map
    const TileMap& tiles = model.getMap().getTilesOfLevel(1);

    for(const Tile& t : tiles.tiles()) {
        if(t.hasLoaded) {
            window->draw(t.tile);
        }

    // red debug grid
#ifdef TILE_DEBUG
        sf::RectangleShape r;
        r.setSize((sf::Vector2f)tiles.getTileSize());
        r.setPosition(t.tile.getPosition());
        r.setOutlineColor(sf::Color::Red);
        r.setOutlineThickness(1);
        r.setFillColor(sf::Color::Transparent);

        window->draw(r);

        std::string position = std::to_string(t.position.x) + ", " + std::to_string(t.position.y);

        sf::Text txt;
        txt.setFont(m_fonts.at("Roboto"));
        txt.setCharacterSize(.2 * tiles.getTileSize().y);
        txt.setFillColor(sf::Color::Red);
        txt.setString(position);
        txt.setPosition(t.tile.getPosition());

        window->draw(txt);
#endif
    }


    window->display();
}