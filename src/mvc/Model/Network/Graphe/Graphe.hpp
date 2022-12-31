#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "mvc/Model/Network/NetworkModel.hpp"
#include "Colorable/Colorable.hpp"


struct GrapheVertex {
    std::vector<int> edges = {};
    Colorable* ptr = nullptr;
    int colorIdx = -1; // the index of the color this vertex is binded to, from its graphe's colors vector.
};


class Graphe {
    public:
        Graphe(const unsigned int n);

        void colorize();

        /**
         * Creates a new vertex in the graph of value v.
         * Under the hood, the vertex is already created, but the pointer is by default equals to null.
         * If v is already present, just update the ptr associated with.
         * If v is highter than the size of the graph (defined by n in the constructor) nothing's done.
         */
        void addVertex(const unsigned int v, Colorable* ptr);

        /**
         * Function to add an edge to graph from 2 vertices.
         * V and W are vertices of the graph, and are the index of the antennas in the NetworkModel.
         * @param v - The index of the first antenna
         * @param a - The first antenna which has for index v
         * @param w - The index of the second antenna
         * @param b - The second antenna which has for index w
         */
	    void addEdge(const unsigned int v, const unsigned int w);

    private:
        /*
        
        2D squared array where the y is the index of the antenna and x is the index of the antennas linked to this one.
        antenna = vertice, link = edge.
        The maximum size of the 2D array is NxN where N is the maximum count of entities in the graph, as the vertex.

        For example :

        v/w| ...   |
        ---|-------|
        0  | 1 | 3 |
        1  | 0     |
        2  |       |
        3  | 0     |
        
        */
        std::vector<GrapheVertex> m_adj;
        std::vector<sf::Color> m_colors;
        unsigned int m_size, m_linkCount;
};

#endif // GRAPHE_HPP