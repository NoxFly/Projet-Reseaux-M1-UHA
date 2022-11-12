#ifndef CONFIGINTERFACES_HPP
#define CONFIGINTERFACES_HPP

#include <string>

struct RendererConfig {
    uint windowWidth;
    uint windowHeight;
    std::string windowTitle;
    std::string icon;
    uint frameRate;
};

struct MapConfig {
    std::string tileFolder;
    std::string tilePrefix;
    uint zoomLevel;
    uint tileCountX;
    uint tileCountY;
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