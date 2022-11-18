#include "GuiModel.hpp"
#define THEME_CONFIG_FILE "../../widgets/Black.conf"


GuiModel::GuiModel():
    m_gui()
{

    tgui::Theme::setDefault(tgui::Theme::create("/home/amir/Desktop/tgui/TGUI-0.9.5/themes/BabyBlue.txt"));

    // Create the background image
    auto picture = tgui::Picture::create("/home/amir/Desktop/Master1/ProjetReseauMobile/Projet-Reseaux-M1-UHA/src/mvc/Model/Gui/MenuBackground.jpg");
    picture->setSize(1280, 720);

    //Add buttons
    auto buttonStart = tgui::Button::create();
    buttonStart->setPosition(490, 310);
    buttonStart->setText("Start");
    //buttonStart->setCallbackId(1);
    //buttonStart->bindCallback(tgui::Button::LeftMouseClicked);
    buttonStart->setSize(300, 40);
    auto buttonSettings = tgui::Button::create();
    buttonSettings->setPosition(490, 360);
    buttonSettings->setText("Settings");
    //buttonSettings->setCallbackId(2);
    //buttonSettings->bindCallback(tgui::Button::LeftMouseClicked);
    buttonSettings->setSize(300, 40);
    auto buttonQuit = tgui::Button::create();
    buttonQuit->setPosition(490, 410);
    buttonQuit->setText("Quit");
    //buttonQuit->setCallbackId(3);
    //buttonQuit->bindCallback(tgui::Button::LeftMouseClicked);
    buttonQuit->setSize(300, 40);

    m_gui.add(picture);
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

