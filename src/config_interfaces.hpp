#ifndef CONFIGINTERFACES_HPP
#define CONFIGINTERFACES_HPP

#include <string>
#include <SFML/System/Vector2.hpp>

struct RendererConfig {
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::string windowTitle;
    std::string icon;
    unsigned int frameRate;
};

struct MapConfig {
    std::string tileFolder;
    std::string tilePrefix;
    unsigned int zoomLevel;
    unsigned int tileCountX;
    unsigned int tileCountY;
    sf::Vector2i topLeft;
    sf::Vector2i bottomRight;
    sf::Vector2f km;
};

struct NetworkConfig {
    std::string entryFile;
};

struct AppConfig {
    RendererConfig renderer;
    MapConfig map;
    NetworkConfig network;
};

#endif // CONFIGINTERFACES_HPP