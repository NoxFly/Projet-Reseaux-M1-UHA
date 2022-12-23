#include "Application.hpp"

#include <iostream>

#include "ConfigReader/ConfigReader.hpp"
#include "mvc/Model/Network/NetworkModel.hpp"
#include "mvc/Model/Network/Graphe/Graphe.hpp"


Application::Application(int argc, char** argv):
    m_config{},
    m_model(), m_renderer(), m_controller()
{
    if(argc < 3) {
        throw std::runtime_error("[ERROR] Application : " + std::to_string(argc-1) + " argument given, 2 expected (configuration file path + antenna sample file path)\nAborting.");
    }

    ConfigReader reader;

    m_config = reader.loadFromFile(argv[1]);

    m_config.network.entryFile = argv[2];

    m_model.loadFromConfig(m_config);

    
    //do logic to figure out which antennas are in each others zone
    // for every two interfering antennas, take their indexes
    // and pass them to addEdge method of Graphe class
    int antennasCr = m_model.getNetwork().getAntennas().size();
	Graphe graphe(antennasCr);
    graphe.addEdge(0, 3);
    graphe.addEdge(4, 2);
    graphe.addEdge(1, 3);
    graphe.addEdge(1, 2);
	graphe.colorationGraphe(m_model.getNetwork());

    #ifdef DEBUG
        for(unsigned i = 0; i < m_model.getNetwork().getAntennas().size(); i++){
        std::cout << " antenna number : " << i << std::endl;
        std::cout << "red : ";
        std::cout.operator<<(m_model.getNetwork().getAntennas().at(i).getColor().r);
        std::cout << ", green : ";
        std::cout.operator<<(m_model.getNetwork().getAntennas().at(i).getColor().g);
        std::cout << ", blue : ";
        std::cout.operator<<(m_model.getNetwork().getAntennas().at(i).getColor().b);
        std::cout << "\n~~" << std::endl;
        }
    #endif
}

Application::~Application() {

}

bool Application::isRunning() const {
    return !m_renderer.isClosed();
}

void Application::start() {
    if(!isRunning()) {
        generateNewWindow();
        animate();
    }
}

void Application::stop() {
    m_renderer.close();
}

void Application::generateNewWindow() {
    m_renderer.createWindow(m_config.renderer);
    m_renderer.getWindow()->setActive();

    m_model.getGui().bindRenderer(&m_renderer);
    m_model.getGui().setup(m_model);
}

void Application::update() {
    m_controller.update(m_renderer, m_model);
}

void Application::render() {
    m_renderer.render(m_model);
}

void Application::animate() {
    while(isRunning()) {
        update();

        if(isRunning()) {
            render();
        }
    }
}