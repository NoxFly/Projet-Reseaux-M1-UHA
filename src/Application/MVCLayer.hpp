#ifndef MVCLAYER_HPP
#define MVCLAYER_HPP

#include <memory>

#include "Model.hpp"
#include "Renderer.hpp"
#include "Controller.hpp"

struct MVCLayer {
    std::shared_ptr<Model> model = nullptr;
    std::shared_ptr<Renderer> view = nullptr;
    std::shared_ptr<Controller> controller = nullptr;

    MVCLayer() {
        // nullptr by default
        // just create this constructor to allow anothe way
        // to instance this struct than the 2nd constructor.
    }

    MVCLayer(std::shared_ptr<Model> m, std::shared_ptr<Renderer> v, std::shared_ptr<Controller> c) {
        model = m;
        view = v;
        controller = c;

        // belongs to the same layer : automatically bind it.
        view->bindModel(model);
    }
};

#endif // MVCLAYER_HPP