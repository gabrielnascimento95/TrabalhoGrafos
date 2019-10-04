//
// Created by gabri on 03/10/2019.
//

#ifndef GRAFOS2_ARESTA_H
#define GRAFOS2_ARESTA_H

#include "No.h"

class No;

class Aresta
{
public:

    Aresta();
    ~Aresta();

    explicit Aresta(No* no1, No *no2);
    explicit Aresta(No *no1, No* no2,int peso);

    No *no1;
    No *no2;
    int peso;

};

#endif //GRAFOS2_ARESTA_H
