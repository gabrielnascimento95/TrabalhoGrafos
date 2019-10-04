//
// Created by gabri on 03/10/2019.
//
#ifndef GRAFOS2_PRIM_H
#define GRAFOS2_PRIM_H

#include "Grafo.h"

using namespace std;

class Prim
{
public:

    void arvoreGeradoraMinima(Grafo *grafo);
    void imprimeSolucao(Grafo *grafo);
    Aresta * getArestaMenorPeso(Grafo *grafo, Grafo *arvoreGeradoraMinima);
};

#endif //GRAFOS2_PRIM_H
