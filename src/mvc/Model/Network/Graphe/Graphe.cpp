#include "mvc/Model/Network/Graphe/Graphe.hpp"

#include <cstdlib>
#include <typeinfo>


Graphe::Graphe(const unsigned int n):
    m_size(n),
    m_linkCount(0)
{
    m_adj.resize(m_size); // init adjacents array

    // the 3 primary colors
    m_colors.push_back(sf::Color(255, 0, 0));
    m_colors.push_back(sf::Color(0, 255, 0));
    m_colors.push_back(sf::Color(0, 0, 255));

    // some others if needed
    for(unsigned int i = 3; i < n; i++) {
        sf::Color newColor;

        newColor.r = (rand() % (255 - 1 + 1)) + 1;
        newColor.b = (rand() % (255 - 1 + 1)) + 1;
        newColor.g = (rand() % (255 - 1 + 1)) + 1;

        m_colors.push_back(newColor);
    }
}

void Graphe::colorize() {
    // antennas colors are set to black by default
    if(m_adj[0].ptr) {
        m_adj[0].ptr->setColor(m_colors[0]); // give first vertex the first gen color
    }

    bool areAvailable[m_size];

	for (unsigned int cr = 0; cr < m_size; cr++) {
        areAvailable[cr] = true;
    }

    // for each vertex to set up its color
    for(unsigned int y = 1; y < m_size; y++) {
        unsigned int linkCount = m_adj.at(y).edges.size();

        // for each edge
        for(unsigned x = 0; x < linkCount; x++) {
            const int k = m_adj.at(y).edges.at(x);
            const auto color = m_adj[k].colorIdx;

            if(color > -1) {
                areAvailable[k] = false;
            }

        }

        // Find the first available color
        unsigned int cr;

        for (cr = 1; cr < m_size; cr++) {
            if (areAvailable[cr]) {
                break;
            }
        }

        // cr is index of smallest available color
        m_adj[y].ptr->setColor(m_colors[cr]);
        m_adj[y].colorIdx = cr;

        // reset dependencies availability for next vertex
        for (cr = 0; cr < m_size; cr++) {
            areAvailable[cr] = true;
        }

    }
}


void Graphe::addVertex(const unsigned int v, Colorable* ptr) {
    if(v < m_size) {
        m_adj[v].ptr = ptr;
    }
}

void Graphe::addEdge(const unsigned int v, const unsigned int w) {
    // Note: the graph is undirected

	m_adj[v].edges.push_back(w);
	m_adj[w].edges.push_back(v);

    // To be upgraded :
    // no verification done : we can call 2 times addEdge(0, 1) and it will increment.
    m_linkCount++;
}