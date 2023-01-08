#include "Model.hpp"

#include <iostream>

#include "utils/PerfMeasure/PerfMeasure.hpp"
#include "common.hpp"
#include "utils/utils.hpp"


Model::Model():
    m_gui(), m_map(), m_network()
{
    
}

Model::~Model() {
    
}

void Model::loadFromConfig(const AppConfig& config) {
    // @remark : it's important to load the map first
    // so the antennas in the network have access to the right map's lambert coords & size
#ifdef MEASURE_PERF
    PerfMeasure perf;

    perf.start();
#endif

    m_map.loadFromConfig(config.map);

#ifdef MEASURE_PERF
    perf.flag();
#endif

    m_network.loadFromConfig(config.network);

#ifdef MEASURE_PERF
    perf.end();

    std::cout << "\n" << BOX_TL << repeat(BOX_HL, 7) << " Model loading performances log " << repeat(BOX_HL, 6) << BOX_TR
        << "\n" << BOX_VL << " MapModel     : " << perf.getTime(0)
        << "\n" << BOX_VL << " NetworkModel : " << perf.getTime(1)
        << "\n" << BOX_BL << repeat(BOX_HL, 46) << BOX_BR
        << std::endl;
#endif
}

GuiModel& Model::getGui() {
    return m_gui;
}

MapModel& Model::getMap() {
    return m_map;
}

NetworkModel& Model::getNetwork() {
    return m_network;
}

const GuiModel& Model::getGui() const {
    return m_gui;
}

const MapModel& Model::getMap() const {
    return m_map;
}

const NetworkModel& Model::getNetwork() const {
    return m_network;
}