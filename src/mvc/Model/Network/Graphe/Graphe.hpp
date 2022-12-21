#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <string>

#ifndef GRAPHE_HPP
#define GRAPHE_HPP

struct Arrete {
    int source, destination;
};

class Graphe {
    public :
        Graphe(std::vector<Arrete> &Arretes, int n);
        void colorationGraphe(int n);
    private :
        std::vector<std::vector<int>> liste_adj;
};

#endif // GRAPHE_HPP