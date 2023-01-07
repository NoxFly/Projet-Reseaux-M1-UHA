#ifndef GRAPHEBACKTRACK_HPP
#define GRAPHEBACKTRACK_HPP

#include "../Graphe.hpp"

class GrapheBacktrack: public Graphe {
	public:
		GrapheBacktrack(const unsigned int n);
		~GrapheBacktrack();

        void colorize();

    protected:
        /**
         * Colorize the graph recursivly.
         * Returns either it colored all the nodes or not.
         */
        bool colorize(unsigned int nodeIndex);
};

#endif // GRAPHEBACKTRACK_HPP