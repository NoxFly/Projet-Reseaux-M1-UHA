#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "mvc/Model/Model.hpp"
#include "mvc/Renderer/Renderer.hpp"
#include "Input/Input.hpp"

class Controller {
	public:
        Controller();
		~Controller();

        void update(Renderer& renderer, Model& model);

    private:
        Input m_input;
};

#endif // CONTROLLER_HPP