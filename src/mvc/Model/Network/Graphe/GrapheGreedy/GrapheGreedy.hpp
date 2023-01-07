#ifndef GRAPHEGREEDY_HPP
#define GRAPHEGREEDY_HPP

#include "../Graphe.hpp"

class GrapheGreedy: public Graphe {
	public:
		GrapheGreedy(const unsigned int n);
		~GrapheGreedy();

        void colorize();
};

#endif // GRAPHEGREEDY_HPP