#include "GrapheBacktrack.hpp"

GrapheBacktrack::GrapheBacktrack(const unsigned int n):
    Graphe(n)
{

}

GrapheBacktrack::~GrapheBacktrack() {

}

void GrapheBacktrack::colorize() {
    if(m_size > 0) {
        colorize(0);
    }
}

bool GrapheBacktrack::colorize(unsigned int nodeIndex) {
    if(nodeIndex == m_size || !m_adj[nodeIndex].ptr) {
        return true;
    }

    for(unsigned int c=1; c <= m_size; c++) {
        bool colorIsSafe = true;

        const unsigned int l = m_adj[nodeIndex].edges.size();

        for(unsigned int i=0; i < l; i++) {
            auto neigh = m_adj[nodeIndex].edges[i];

            if(m_adj[neigh].ptr && (int)c == m_adj[i].colorIdx) {
                colorIsSafe = false;
                break;
            }
        }

        if(colorIsSafe) {
            setNodeColor(nodeIndex, c);
            return colorize(nodeIndex + 1);
        }
    }

    return false;
}