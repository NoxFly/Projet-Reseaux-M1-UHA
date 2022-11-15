#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"
#include "Renderer.hpp"
#include "Input.hpp"

class Controller {
	public:
        Controller();
		~Controller();

        void update(Renderer& renderer, Model& model);

    private:
        Input m_input;
};

#endif // CONTROLLER_HPP