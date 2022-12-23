#include "mvc/Model/Network/Graphe/Graphe.hpp"
#include "mvc/Model/Network/NetworkModel.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>
#include <typeinfo>

Graphe::Graphe(int n) {
   m_size = n;
   m_adj.resize(m_size);//init adjacents array
   for(int i = 0; i < n; i++){
        sf::Color newColor;
        newColor.r = (rand() % (255 - 1 + 1)) + 1;
        newColor.b = (rand() % (255 - 1 + 1)) + 1;
        newColor.g = (rand() % (255 - 1 + 1)) + 1;
        m_colors.push_back(newColor);
   }

}

void Graphe::colorationGraphe(NetworkModel &antennas) {

    //antennas colors are set to black by default
    antennas.getNetworkAt(0).setColor(m_colors[0]);//give first vertex the first gen color

    bool areAvailable[m_size];

	for (int cr = 0; cr < m_size; cr++){
        areAvailable[cr] = true;
    }

    for(unsigned y =  1 ; y < m_adj.size(); y++){

        for(unsigned x = 0; x < m_adj.at(y).size(); x++){
    
            if(antennas.getNetworkAt(m_adj.at(y).at(x)).getColor().r != 0
            && antennas.getNetworkAt(m_adj.at(y).at(x)).getColor().b != 0
            && antennas.getNetworkAt(m_adj.at(y).at(x)).getColor().g != 0){
                areAvailable[m_adj.at(y).at(x)] = false;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 1; cr < m_size; cr++){
            if (areAvailable[cr] == true){
                break; 
            }
        }
        //cr is index of smallest available color
        antennas.getNetworkAt(y).setColor(m_colors[cr]);

        // reset dependencies availability for next vertex
        for (cr = 0; cr < m_size; cr++){
            areAvailable[cr] = true;
        }
    }
}

void Graphe::addEdge(int v, int w)
{
	m_adj[v].push_back(w);
	m_adj[w].push_back(v); // Note: the graph is undirected
}