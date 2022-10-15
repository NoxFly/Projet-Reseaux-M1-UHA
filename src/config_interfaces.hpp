#ifndef CONFIGINTERFACES_HPP
#define CONFIGINTERFACES_HPP

#include <string>

struct MapConfig {
    std::string tileFolder;
    std::string tileSuffix;
    int zoomLevel;
    int tileCountX;
    int tileCountY;
};

struct NetworkConfig {
    std::string entryFile;
};

struct AppConfig {
    MapConfig map;
    NetworkConfig network;
};

#endif // CONFIGINTERFACES_HPP