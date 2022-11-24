#ifndef GUI_HPP
#define GUI_HPP

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>


class Renderer;
class Model;

class GuiModel {
	public:
		GuiModel();
		~GuiModel();

		tgui::GuiSFML& getTgui();

        void bindRenderer(Renderer* renderer);

        void setup(Model& model);

        bool shouldDraw() const;

	private:

		tgui::GuiSFML m_gui;
        sf::RenderWindow* m_window;
        Renderer* m_renderer;

        // debug
        bool m_draw;

};

#endif // GUI_HPP