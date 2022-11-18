#include "Model.hpp"


Model::Model() {
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(AppConfig config) {
    // TODO : apply the config for the right models
    (void)config;
}

GuiModel& Model::getGui() noexcept {
    return m_gui;
}

MapModel& Model::getMap() noexcept {
    return m_map;
}

NetworkModel& Model::getNetwork() noexcept {
    return m_network;
}