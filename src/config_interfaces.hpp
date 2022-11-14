#ifndef CONFIGINTERFACES_HPP
#define CONFIGINTERFACES_HPP

#include <string>

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