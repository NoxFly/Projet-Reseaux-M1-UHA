#include "GrapheGreedy.hpp"

GrapheGreedy::GrapheGreedy(const unsigned int n):
    Graphe(n)
{

}

GrapheGreedy::~GrapheGreedy() {

}

void GrapheGreedy::colorize() {
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

    bool* areAvailable = new bool[m_size];

	for (unsigned int cr = 0; cr < m_size; cr++) {
        areAvailable[cr] = true;
    }

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

        // cr is index of smallest available color
        setNodeColor(y, cr);

        // reset dependencies availability for next vertex
        for (cr = 0; cr < m_size; cr++) {
            areAvailable[cr] = true;
        }

    }

    delete[] areAvailable;
}