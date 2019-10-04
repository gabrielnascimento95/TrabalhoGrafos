//
// Created by gabri on 03/10/2019.
//

#ifndef GRAFOS2_KRUSKAL_H
#define GRAFOS2_KRUSKAL_H

#include "Grafo.h"

using namespace std;

class Kruskal {
public:

    static void arvoreGeradoraMinima(Grafo *grafo);
    static bool arestaFormaCiclo(No *no1, No *no2);
    static void imprimirSolucao(Grafo *grafo);
};


#endif //GRAFOS2_KRUSKAL_H
