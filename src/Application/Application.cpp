#include "Application.hpp"
#include <iostream>
#include "ConfigReader.hpp"
#include "NetworkModel.hpp"

Application::Application(int argc, char** argv):
    m_running(false),
    m_config{},
    m_model(), m_renderer(), m_controller(),
    m_window(nullptr)
{
    if(argc < 2) {
        throw std::runtime_error("Missing configuration file path !\nAborting.");
    }

    ConfigReader reader;
    NetworkModel test;//for debugging the new functionality only

    m_config = reader.loadFromFile(argv[1]);

    m_model.loadFromConfig(m_config);
    test.loadFromConfig(m_config);//for debugging the new functionality only
    std::cout << test.getNetworkAt(1).getPosition().lambert().x << std::endl;//for debugging the new functionality only
}

Application::~Application() {

}

bool Application::isRunning() const {
    return m_running;
}

void Application::start() {
    if(!m_running) {
        m_running = true;
        launch();
    }
}

void Application::stop() {
    // the thread will dispose itself because of the
    // while condition which is looking for m_running
    m_running = false;
}

void Application::generateNewWindow() {
    // create window
    m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Mulhouse Networking", sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(60);
    m_window->setKeyRepeatEnabled(false);

    // app icon
    sf::Image icon;
    icon.loadFromFile("res/favicon.png");
    m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // position window at center of the screen
    auto desktop = sf::VideoMode::getDesktopMode();
    auto wX = desktop.width / 2 - m_window->getSize().x / 2;
    auto wY = desktop.height / 2 - m_window->getSize().y / 2;

    m_window->setPosition(sf::Vector2i(wX, wY));
    // ---

    m_window->setActive();
}

void Application::update() {
    m_controller.update(m_window, m_model, &m_running);
}

void Application::render() {
    m_window->clear();

    m_renderer.render(m_window, m_model);

    m_window->display();
}


void Application::launch() {
    generateNewWindow();
    animate();
}

void Application::animate() {
    while(m_running) {
        update();

        if(m_running) {
            render();
        }
    }
}