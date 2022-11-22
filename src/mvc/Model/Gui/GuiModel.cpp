#include "GuiModel.hpp"
#include <TGUI/TGUI.hpp>
#define THEME_CONFIG_FILE "../../widgets/Black.conf"


GuiModel::GuiModel():
    m_gui()
{

    tgui::Theme::setDefault(tgui::Theme::create("/home/amir/Desktop/tgui/TGUI-0.9.5/themes/BabyBlue.txt"));
    

    // Create the background image
    auto picture = tgui::Picture::create("/home/amir/Desktop/Master1/ProjetReseauMobile/Projet-Reseaux-M1-UHA/src/mvc/Model/Gui/MenuBackground.jpg");
    picture->setSize(1280, 720);


    //Add title(label)
    auto title = tgui::Label::create();
    title->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
    title->setText("Mulhouse Networking");
    title->setPosition(320, 160);
    title->getRenderer()->setFont("/home/amir/Desktop/Master1/ProjetReseauMobile/Projet-Reseaux-M1-UHA/src/mvc/Model/Gui/font.ttf");
    title->getRenderer()->setTextColor(sf::Color(255,255,255));
    //title->getRenderer()->setBackgroundColor(sf::Color(187,226,233));
    title->setTextSize(72);

    //Add buttons
    auto buttonStart = tgui::Button::create();
    buttonStart->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
    buttonStart->setPosition(490, 400);
    buttonStart->setText("Start");
    buttonStart->setSize(300, 50);
    buttonStart->onPress([&]{ std::cout << " button Start pressed" << std::endl; });


    auto buttonSettings = tgui::Button::create();
    buttonSettings->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
    buttonSettings->setPosition(490, 470);
    buttonSettings->setText("Settings");
    buttonSettings->setSize(300, 50);
    buttonSettings->onPress([&]{ std::cout << " button Settings pressed" << std::endl; });

    auto buttonQuit = tgui::Button::create();
    buttonQuit->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, 500);
    buttonQuit->setPosition(490, 540);
    buttonQuit->setText("Quit");
    ///buttonQuit->setCallbackId(3);
    //buttonQuit->bindCallback(tgui::Button::LeftMouseClicked);
    buttonQuit->setSize(300, 50);
    buttonQuit->onPress([&]{ std::cout << " button Quit pressed" << std::endl; });

    m_gui.setOverrideMouseCursor(tgui::Cursor::Type::Hand);
    m_gui.add(picture);
    m_gui.add(title);
    m_gui.add(buttonStart);
    m_gui.add(buttonSettings);
    m_gui.add(buttonQuit);






}

GuiModel::~GuiModel() {

}

tgui::GuiSFML& GuiModel::getTgui(){
    return m_gui;
}

void GuiModel::bindWindow(sf::RenderWindow* window){

    m_gui.setTarget(*window);


}

