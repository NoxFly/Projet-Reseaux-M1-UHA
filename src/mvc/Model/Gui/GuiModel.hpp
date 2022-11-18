#ifndef GUI_HPP
#define GUI_HPP
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>


class GuiModel {
	public:
		GuiModel();
		~GuiModel();

		tgui::GuiSFML& getTgui();
		void bindWindow(sf::RenderWindow* window);

	private:
		tgui::GuiSFML m_gui;


};

#endif // GUI_HPP