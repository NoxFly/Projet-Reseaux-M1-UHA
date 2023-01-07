#include "Application.hpp"

#include <iostream>

#include "ConfigReader/ConfigReader.hpp"

#include "utils/PerfMeasure/PerfMeasure.hpp"
#include "utils/utils.hpp"
#include "common.hpp"


Application::Application(int argc, char** argv):
    m_config{},
    m_model(), m_renderer(), m_controller()
{
    if(argc < 3) {
        throw std::runtime_error("[ERROR] Application : " + std::to_string(argc-1) + " argument given, 2 expected (configuration file path + antenna sample file path)\nAborting.");
    }

#ifdef MEASURE_PERF
    PerfMeasure perf;

    perf.start();
#endif

    ConfigReader reader;

    m_config = reader.loadFromFile(argv[1]);

#ifdef MEASURE_PERF
    perf.flag();
#endif

    m_config.network.entryFile = argv[2];

    m_model.loadFromConfig(m_config);

#ifdef MEASURE_PERF
    perf.end();

    std::cout << "\n┌──────── Application performances log ───────┐"
        << "\n│ Config reader : " << perf.getTime(0)
        << "\n│ Model loading : " << perf.getTime(1)
        << "\n│ Total time    : " << perf.getTotalTime()
        << "\n└─────────────────────────────────────────────┘"
        << std::endl;
#endif
}

Application::~Application() {

}

bool Application::isRunning() const {
    return !m_renderer.isClosed();
}

void Application::start() {
    if(!isRunning()) {
#ifdef MEASURE_PERF
        PerfMeasure perf;

        perf.start();
#endif
        generateNewWindow();

#ifdef MEASURE_PERF
        perf.end();

        std::cout << "┌───────── Renderer performances log ─────────┐"
            << "\n│ Create window : " << nsToTime(perf.getDuration())
            << "\n└─────────────────────────────────────────────┘"
            << std::endl;
#endif

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

    m_model.getGui().showHomeMenu();
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