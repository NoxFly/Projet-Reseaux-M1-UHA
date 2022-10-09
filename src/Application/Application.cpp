#include "Application.hpp"

Application::Application(int argc, char** argv):
    m_running(false),
    m_mapLayer{}, m_guiLayer{}, m_networkLayer{},
    m_window(nullptr),
    m_thread(&Application::animate, this)
{
    // TODO : do arg verification & config loader
    (void)argc;
    (void)argv;
}

Application::~Application() {

}

bool Application::isRunning() const {
    return m_running;
}

void Application::start() {
    if(!m_running) {
        m_running = true;

        generateNewWindow();

        // TODO : create new MVC for map, gui and network
        // then create their layer and update Application's layers

        m_thread.launch();
    }
}

void Application::stop() {
    // the thread will dispose itself because of the
    // while condition which is looking for m_running
    m_running = false;
}

void Application::generateNewWindow() {
    // TODO : do it with loaded configuration

    // create window
    m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Test window", sf::Style::Close | sf::Style::Titlebar);
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

void Application::animate() {
    while(m_running) {
        update();

        if(m_running) {
            render();
        }
    }
}