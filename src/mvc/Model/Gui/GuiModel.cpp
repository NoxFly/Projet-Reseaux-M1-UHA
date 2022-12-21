#include "GuiModel.hpp"

#include <TGUI/TGUI.hpp>

#include "mvc/Renderer/Renderer.hpp"
#include "mvc/Model/Model.hpp"

GuiModel::GuiModel():
    m_gui(),
    m_window(nullptr),
    m_renderer(nullptr),
    m_draw(true)
{
    
    tgui::Theme::setDefault(tgui::Theme::create("res/themes/BabyBlue.txt"));

    // Create the background image
    auto picture = tgui::Picture::create("res/images/menu/MenuBackground.jpg");
    picture->setSize(1280, 720);


    //Add title(label)
    auto title = tgui::Label::create();
    title->setText("Mulhouse Networking");
    title->setPosition(225, 160);
    title->getRenderer()->setFont("res/fonts/font.ttf");
    title->getRenderer()->setTextColor(sf::Color(255,255,255));
    title->getRenderer()->setTextOutlineThickness(3);
    title->getRenderer()->setTextOutlineColor(sf::Color(80,80,80));
    //title->getRenderer()->setBackgroundColor(sf::Color(187,226,233));
    title->setTextSize(92);
    title->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);


    

    m_gui.add(picture);
    m_gui.add(title);

}

GuiModel::~GuiModel() {

}

tgui::GuiSFML& GuiModel::getTgui() {
    return m_gui;
}

void GuiModel::bindRenderer(Renderer* renderer) {

    m_renderer = renderer;

    m_gui.setTarget(*(m_renderer->getWindow()));

}

void GuiModel::setup(Model& model) {
    (void)model;

    //Add buttons
    auto buttonStart = tgui::Button::create();
    buttonStart->setPosition(490, 400);
    buttonStart->setText("Start");
    buttonStart->setInheritedFont("res/fonts/font.ttf");
    buttonStart->setTextSize(30);
    buttonStart->setSize(300, 50);

    buttonStart->onPress([&]{
        m_draw = false;
    });

    buttonStart->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);


    auto buttonSettings = tgui::Button::create();
    buttonSettings->setPosition(490, 470);
    buttonSettings->setText("Settings");
    buttonSettings->setInheritedFont("res/fonts/font.ttf");
    buttonSettings->setTextSize(30);
    buttonSettings->setSize(300, 50);
    buttonSettings->onPress([&]{ std::cout << " button Settings pressed" << std::endl; });
    buttonSettings->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);



    auto buttonQuit = tgui::Button::create();
    buttonQuit->setPosition(490, 540);
    buttonQuit->setText("Quit");
    buttonQuit->setInheritedFont("res/fonts/font.ttf");
    buttonQuit->setTextSize(30);
    buttonQuit->setSize(300, 50);

    ///buttonQuit->setCallbackId(3);
    //buttonQuit->bindCallback(tgui::Button::LeftMouseClicked);

    buttonQuit->onPress([&]{
        m_renderer->close();
    });

    buttonQuit->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);

    m_gui.add(buttonStart);
    m_gui.add(buttonSettings);
    m_gui.add(buttonQuit);
}

bool GuiModel::shouldDraw() const {
    return m_draw;
}