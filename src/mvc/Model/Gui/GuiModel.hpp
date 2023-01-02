#ifndef GUI_HPP
#define GUI_HPP

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include <map>

#include "mvc/Model/Network/Antenna/Antenna.hpp"


class Renderer;
class Model;

class GuiModel {
	public:
		GuiModel();
		~GuiModel();

		void draw();
        void handleEvent(const sf::Event& event);

        void bindRenderer(Renderer* renderer);

        bool isDrawingFullscreenMenu() const;

        bool noMenuOpened() const;

        void showHomeMenu();
        void hideHomeMenu();

        void showAntennaDetailsMenu(Antenna* antenna);
        void hideAntennaDetailsMenu();

        // dev
        bool isShowingDetails() const;
        bool isShowingHomeMenu() const;
        Antenna* getAntennaDetails() const;

	private:

		tgui::GuiSFML m_gui;
        Renderer* m_renderer;

        // dev
        Antenna* m_antenna;

        // debug
        bool m_drawFsMenu;
        bool m_showHome;
        bool m_hasAnyMenuOpened;
};

#endif // GUI_HPP