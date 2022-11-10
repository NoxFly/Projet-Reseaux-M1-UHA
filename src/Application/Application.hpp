#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "config_interfaces.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "Controller.hpp"


/**
 * Main application manager.
 * Loads the configuration, owns the main window, and MVC layers.
 * Has an animate methods that loops to update & render.
 */
class Application {
	public:
		Application(int argc, char**argv);
		~Application();

		/**
		 * @returns Either the application is still running or not.
		 */
		bool isRunning() const;

		/**
		 * Starts the application if it hasn't.
		 * Calls the launch method.
		 */
		void start();

		/**
		 * Allows to force the application to stop at any time.
		 */
		void stop();

	private:
		/**
		 * Updates the user's entries (mouse, keyboard, joystick, ...)
		 * Then, updates the controllers.
		 */
		void update();

		/**
		 * Renders the models on the window.
		 */
		void render();

		/**
		 * Used in a new sf::Thread, allowing the rest
		 * of the application to proceed some stuff, like loading map, etc...
		 * Generates a new window with loaded configuration.
		 * Then calls the animate method.
		 */
		void launch();

		/**
		 * Main loop.
		 * Calls update, render.
		 * The body of this method should'nt really change.
		 * Launched in another thread so it does not block any potential further instructions.
		 */
		void animate();

		/**
		 * Creates a new Window with loaded configuration.
		 * If the configuration mention a position, then place the window.
		 * If the position is -1,-1, then center the window.
		 * Makes the window active.
		 */
		void generateNewWindow();

		bool m_running;
		AppConfig m_config;
		Model m_model;
		Renderer m_renderer;
		Controller m_controller;

		sf::RenderWindow* m_window;
};

#endif // APPLICATION_HPP