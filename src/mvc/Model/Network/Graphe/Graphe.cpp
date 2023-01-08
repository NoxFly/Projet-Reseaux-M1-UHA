#include "mvc/Model/Network/Graphe/Graphe.hpp"

#include <cstdlib>
#include <typeinfo>
#include <iostream>
#include <random>

// for random colors index between 0 and 255
std::random_device dev;
std::mt19937 rng(dev());

std::uniform_int_distribution<std::mt19937::result_type> randomColor0_255(0, 255);


Graphe::Graphe(const unsigned int n):
    m_size(n),
    m_linkCount(0),
    m_colorSize(0)
{
    m_adj.resize(m_size); // init adjacents array

    // the 3 primary colors
    // dirty ifs but to be sure it won't make issues in the future with getColors()
    if(m_size > 0) {
        addColor(sf::Color(224, 65, 72));

        if(m_size > 1) {
            addColor(sf::Color(99, 230, 112));

            if(m_size > 2) {
                addColor(sf::Color(76, 89, 235));
            }
        }
    }
}

Graphe::~Graphe() {

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

    newColor.r = randomColor0_255(rng);
    newColor.b = randomColor0_255(rng);
    newColor.g = randomColor0_255(rng);

    addColor(newColor);
}

void Graphe::addColor(const sf::Color& color) {
    m_colors.push_back(color);
    m_colorSize++;
}

void Graphe::setNodeColor(const unsigned int nodeIndex, const unsigned int colorIndex) {
    if(m_colorSize <= colorIndex) {
        addColor();
    }

    if(m_adj[nodeIndex].ptr) {
        m_adj[nodeIndex].ptr->setColor(m_colors[colorIndex]);
        m_adj[nodeIndex].colorIdx = colorIndex;
    }
}