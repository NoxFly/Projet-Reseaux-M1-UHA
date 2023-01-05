#include "mvc/Model/Network/Graphe/Graphe.hpp"

#include <cstdlib>
#include <typeinfo>
#include <iostream>


Graphe::Graphe(const unsigned int n):
    m_size(n),
    m_linkCount(0)
{
    m_adj.resize(m_size); // init adjacents array

    // the 3 primary colors
    // dirty ifs but to be sure it won't make issues in the future with getColors()
    if(m_size > 0) {
        m_colors.push_back(sf::Color(224, 65, 72));

        if(m_size > 1) {
            m_colors.push_back(sf::Color(99, 230, 112));

            if(m_size > 2) {
                m_colors.push_back(sf::Color(76, 89, 235));
            }
        }
    }
}

void Graphe::colorize() {
    // no antenna : no colorization
    if(m_size == 0) {
        return;
    }

    // antennas colors are set to black by default (SFML does it by default)

    // first antenna : associate the first color in the list
    if(m_adj[0].ptr) {
        m_adj[0].ptr->setColor(m_colors[0]); // give first vertex the first gen color
    }

    m_adj[0].colorIdx = 0;

    bool areAvailable[m_size];

	for (unsigned int cr = 0; cr < m_size; cr++) {
        areAvailable[cr] = true;
    }

    unsigned int colorSize = m_colors.size();

    // for each vertex to set up its color
    for(unsigned int y = 0; y < m_size; y++) {
        unsigned int linkCount = m_adj.at(y).edges.size();

        // for each edge
        for(unsigned x = 0; x < linkCount; x++) {
            const int k = m_adj.at(y).edges.at(x);
            const auto color = m_adj[k].colorIdx;
            if(color > -1) {
                areAvailable[color] = false;
            }

        }

        // Find the first available color
        unsigned int cr;

        for (cr = 0; cr < m_size; cr++) {
            if (areAvailable[cr]) {
                break;
            }
        }

        // only happens when cr = colorSize + 1 because the colorSize'th previous ones weren't available
        if(colorSize <= cr) {
            colorSize++;
            addColor();
        }

        // cr is index of smallest available color
        const auto color = m_colors[cr];

        if(m_adj[y].ptr) {
            m_adj[y].ptr->setColor(color);
        }

        m_adj[y].colorIdx = cr;

        // reset dependencies availability for next vertex
        for (cr = 0; cr < m_size; cr++) {
            areAvailable[cr] = true;
        }

    }

#ifdef DEBUG
    
#endif
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

const std::vector<sf::Color>& Graphe::getColors() const {
    return m_colors;
}

void Graphe::addColor() {
    sf::Color newColor;

    newColor.r = (rand() % (255 - 1 + 1)) + 1;
    newColor.b = (rand() % (255 - 1 + 1)) + 1;
    newColor.g = (rand() % (255 - 1 + 1)) + 1;

    m_colors.push_back(newColor);
}