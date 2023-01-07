#ifndef GRAPHEBACKTRACK_HPP
#define GRAPHEBACKTRACK_HPP

#include "../Graphe.hpp"

class GrapheBacktrack: public Graphe {
	public:
		GrapheBacktrack(const unsigned int n);
		~GrapheBacktrack();

        void colorize();

    protected:
        bool colorize(unsigned int nodeIndex);
};

#endif // GRAPHEBACKTRACK_HPP