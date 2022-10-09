#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "MVCLayer.hpp"

/**
 * Main application manager.
 * Loads the configuration, owns the main window, and MVC layers.
 * Has an animate methods that loops to update & render.
 * 
 * @note
 * Using SFML Thread instead of STL Thread
 * It's a bit powerless, using old methods,
 * but it ensure a compatibility / portability.
 */
class Application {
	public:
		Application(int argc, char**argv);
		~Application();

		/**
		 * @returns either the application is still running or not.
		 */
		bool isRunning() const;

		/**
		 * Starts the application if it hasn't.
		 * Hence, generates a new window with loaded configuration.
		 * Starts the main process in another thread, allowing the rest
		 * of the application to proceed some stuff, like loading map, etc...
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
		MVCLayer m_mapLayer, m_guiLayer, m_networkLayer;

		sf::RenderWindow* m_window;
		sf::Thread m_thread;
};

#endif // APPLICATION_HPP