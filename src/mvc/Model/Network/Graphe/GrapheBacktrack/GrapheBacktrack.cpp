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

bool GrapheBacktrack::colorize(const unsigned int nodeIndex) {
    // if out of bounds or node isn't linked to an entity, we skip
    if(nodeIndex == m_size || !m_adj[nodeIndex].ptr) {
        return true;
    }

    // for each colors (assuming the max color count is the number of vertices)
    for(unsigned int c=0; c < m_size; c++) {
        bool colorIsSafe = true;

        // number of edges with this node
        const unsigned int l = m_adj[nodeIndex].edges.size();

        // for each edge
        for(unsigned int i=0; i < l; i++) {
            const auto neighIdx = m_adj[nodeIndex].edges[i];
            const auto neighbor = m_adj[neighIdx];

            // if the edge exists and has the same color than the current we're checking
            if(neighbor.ptr && (int)c == neighbor.colorIdx) {
                colorIsSafe = false;
                break;
            }
        }

        // if the color is available
        if(colorIsSafe) {
            // color the node
            setNodeColor(nodeIndex, c);

            // then try for the next node
            if(colorize(nodeIndex + 1)) {
                return true;
            }
        }
    }

    return false;
}