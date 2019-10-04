//
// Created by gabri on 03/10/2019.
//

#ifndef GRAFOS2_DIJKSTRA_H
#define GRAFOS2_DIJKSTRA_H

#include "Grafo.h"
#include <vector>

class Dijkstra
{
public:
    static void custoCaminhoMinimo(Grafo *grafo, int idNo1, int idNo2);
    static No *getNoDistanciaMinima(vector<No *> Nos);
private:

};

#endif //GRAFOS2_DIJKSTRA_H
