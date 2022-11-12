#include "Application.hpp"

#include "ConfigReader.hpp"

Application::Application(int argc, char** argv):
    m_config{},
    m_model(), m_renderer(), m_controller()
{
    if(argc < 2) {
        throw std::runtime_error("Missing configuration file path !\nAborting.");
    }

    ConfigReader reader;

    m_config = reader.loadFromFile(argv[1]);

    m_model.loadFromConfig(m_config);
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