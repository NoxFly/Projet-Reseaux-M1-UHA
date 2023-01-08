#include "GuiModel.hpp"
#include <iostream>
#include <TGUI/TGUI.hpp>

#include "mvc/Renderer/Renderer.hpp"
#include "mvc/Model/Model.hpp"

GuiModel::GuiModel():
    m_gui(),
    m_renderer(nullptr),
    m_antenna(nullptr),
    m_drawFsMenu(false),
    m_showHome(false),
    m_showShortcuts(false),
    m_hasAnyMenuOpened(false)
{
    tgui::Theme::setDefault(tgui::Theme::create("res/themes/BabyBlue.txt"));
}

GuiModel::~GuiModel() {

}

void GuiModel::handleEvent(const sf::Event& event) {
    m_gui.handleEvent(event);
}

void GuiModel::bindRenderer(Renderer* renderer) {
    m_renderer = renderer;
    m_gui.setTarget(*(m_renderer->getWindow()));
}

bool GuiModel::isDrawingFullscreenMenu() const {
    return m_drawFsMenu;
}

void GuiModel::draw() {
    m_gui.draw();
}

bool GuiModel::noMenuOpened() const {
    return !m_hasAnyMenuOpened;
}

/* ===================================== */
/* ============== MENUS ================ */
/* ===================================== */

void GuiModel::showHomeMenu() {
    // Create the background image
    auto homePic = tgui::Picture::create("res/images/menu/MenuBackground.jpg");
    homePic->setSize(1280, 720);

    //Add title(label)
    auto homeTitle = tgui::Label::create();
    homeTitle->setText("Mulhouse Networking");
    homeTitle->setPosition(225, 160);
    homeTitle->getRenderer()->setFont("res/fonts/font.ttf");
    homeTitle->getRenderer()->setTextColor(sf::Color(255,255,255));
    homeTitle->getRenderer()->setTextOutlineThickness(3);
    homeTitle->getRenderer()->setTextOutlineColor(sf::Color(80,80,80));
    homeTitle->getRenderer()->setBackgroundColor(sf::Color(187,226,233));
    homeTitle->setTextSize(92);

    // homeTitle->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);

    //Add buttons
    auto buttonStart = tgui::Button::create();
    buttonStart->setPosition(490, 400);
    buttonStart->setText("Commencer");
    buttonStart->setInheritedFont("res/fonts/font.ttf");
    buttonStart->setTextSize(30);
    buttonStart->setSize(300, 50);

    buttonStart->onPress([&]{
        hideHomeMenu();
    });

    // buttonStart->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);


    auto buttonSettings = tgui::Button::create();
    buttonSettings->setPosition(490, 470);
    buttonSettings->setText("Raccourcis");
    buttonSettings->setInheritedFont("res/fonts/font.ttf");
    buttonSettings->setTextSize(30);
    buttonSettings->setSize(300, 50);

    // buttonSettings->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);

    buttonSettings->onPress([&]{
        showShortcutMenu();
    });



    auto buttonQuit = tgui::Button::create();
    buttonQuit->setPosition(490, 540);
    buttonQuit->setText("Quitter");
    buttonQuit->setInheritedFont("res/fonts/font.ttf");
    buttonQuit->setTextSize(30);
    buttonQuit->setSize(300, 50);

    ///buttonQuit->setCallbackId(3);
    //buttonQuit->bindCallback(tgui::Button::LeftMouseClicked);

    buttonQuit->onPress([&]{
        m_renderer->close();
    });

    // buttonQuit->showWithEffect(tgui::ShowEffectType::SlideFromTop, 500);

    m_gui.add(homePic);
    m_gui.add(homeTitle);
    m_gui.add(buttonStart);
    m_gui.add(buttonSettings);
    m_gui.add(buttonQuit);

    m_drawFsMenu = true;
    m_showHome = true;
    m_hasAnyMenuOpened = true;
}

void GuiModel::hideHomeMenu() {
    m_gui.removeAllWidgets();
    m_drawFsMenu = false;
    m_showHome = false;
    m_hasAnyMenuOpened = false;
}

void GuiModel::showAntennaDetailsMenu(Antenna* antenna) {
    m_antenna = antenna;
    m_hasAnyMenuOpened = true;
}

void GuiModel::hideAntennaDetailsMenu() {
    m_antenna = nullptr;
    m_hasAnyMenuOpened = false;
}

bool GuiModel::isShowingDetails() const {
    return m_antenna != nullptr;
}

bool GuiModel::isShowingHomeMenu() const {
    return m_showHome;
}

Antenna* GuiModel::getAntennaDetails() const {
    return m_antenna;
}

void GuiModel::showShortcutMenu() {
    m_showShortcuts = true;
    m_drawFsMenu = true;
    m_gui.removeAllWidgets();
}

void GuiModel::hideShortcutMenu() {
    m_showShortcuts = false;

    if(m_showHome) {
        showHomeMenu();
        return;
    }

    m_drawFsMenu = false;
    m_hasAnyMenuOpened = false;
}

bool GuiModel::isShowingShortcutMenu() const {
    return m_showShortcuts;
}