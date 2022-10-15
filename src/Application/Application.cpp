#include "Application.hpp"

#include "ConfigReader.hpp"

#include "MapModel.hpp"
#include "NetworkModel.hpp"
#include "GuiModel.hpp"

#include "MapController.hpp"
#include "NetworkController.hpp"
#include "GuiController.hpp"

#include "MapRenderer.hpp"
#include "NetworkRenderer.hpp"
#include "GuiRenderer.hpp"


Application::Application(int argc, char** argv):
    m_running(false),
    m_config{},
    m_mapLayer{}, m_guiLayer{}, m_networkLayer{},
    m_window(nullptr),
    m_thread(&Application::launch, this)
{
    if(argc < 2) {
        throw std::runtime_error("Missing configuration file path !\nAborting.");
    }

    ConfigReader reader;

    m_config = reader.loadFromFile(argv[1]);
}

Application::~Application() {

}

bool Application::isRunning() const {
    return m_running;
}

void Application::start() {
    if(!m_running) {
        m_running = true;

        m_thread.launch();
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
    // update view input (poll event)
    sf::Event e;

    while(m_window->pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            m_running = false;
        }
    }

    // TODO : update controllers
}

void Application::render() {
    m_window->clear();

    if(m_mapLayer.view)
        m_mapLayer.view->render(m_window);

    if(m_networkLayer.view)
        m_networkLayer.view->render(m_window);

    if(m_guiLayer.view)
        m_guiLayer.view->render(m_window);

    m_window->display();
}


void Application::launch() {
    // === MVC ===
    // map MVC
    auto mm = std::make_shared<MapModel>(m_config.map);
    auto mc = std::make_shared<MapController>();
    auto mr = std::make_shared<MapRenderer>();
    // network MVC
    auto nm = std::make_shared<NetworkModel>(m_config.network);
    auto nc = std::make_shared<NetworkController>();
    auto nr = std::make_shared<NetworkRenderer>();
    // gui MVC
    auto gm = std::make_shared<GuiModel>();
    auto gc = std::make_shared<GuiController>();
    auto gr = std::make_shared<GuiRenderer>();
    // === === ===

    // layers
    m_mapLayer = MVCLayer(mm, mr, mc);
    m_networkLayer = MVCLayer(nm, nr, nc);
    m_guiLayer = MVCLayer(gm, gr, gc);
    // ===

    //
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