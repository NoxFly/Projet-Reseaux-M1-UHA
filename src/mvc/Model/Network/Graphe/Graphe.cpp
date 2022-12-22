#include "Graphe.hpp"

Graphe::Graphe(std::vector<Arrete> &Arretes, int n) {
    liste_adj.resize(n);
    for(Arrete arrete : Arretes) {
        int source = arrete.source;
        int destination = arrete.destination;

        liste_adj[source].push_back(destination);
        liste_adj[destination].push_back(source);
    }
}

void Graphe::colorationGraphe(int n) {
    std::string couleur[] = {
            "", "BLEU", "VERT", "ROUGE", "JAUNE", "ORANGE", "ROSE", "NOIR", "BRUN", "BLANC", "VIOLET"
    };
    std::unordered_map<int, int> resultat;
    for (int i = 0; i < n; i++) {
        std::set<int> assign;
        for (int j : liste_adj[i]) {
            if(resultat[j]) {
                assign.insert(resultat[j]);
            }
        }

        int couleur = 1;
        for (auto &col : assign) {
            if (couleur != col) {
                break;
            }
            couleur++;
        }

        resultat[i] = couleur;
    }

    for (int i = 0; i < n; i++) {
        std::cout << "La couleur assigné au noeud " << i << " est " << couleur[resultat[i]] << std::endl;
    }
}