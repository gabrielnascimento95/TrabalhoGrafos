//
// Created by gabri on 03/10/2019.
//
#ifndef GRAFOS2_FLOYD_H
#define GRAFOS2_FLOYD_H

class Floyd {

public:
    void imprimeFloyd(Grafo *grafo);

private:
    vector<vector<long int> > mDistancia; /// matriz para armazenar as distâncias
    void matrizDistancia(Grafo *grafo);
    void floyd(Grafo *grafo);

};


#endif //GRAFOS2_FLOYD_H
