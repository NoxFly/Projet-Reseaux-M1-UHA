#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include "mvc/Model/Network/NetworkModel.hpp"


#ifndef GRAPHE_HPP
#define GRAPHE_HPP

class Graphe {
    public :
        Graphe(int n);
        void colorationGraphe(NetworkModel &antennas);
        // function to add an edge to graph
	    void addEdge(int v, int w); 
    private :
        std::vector<std::vector<int>> m_adj;
        std::vector<sf::Color> m_colors;
        int m_size;
};

#endif // GRAPHE_HPP