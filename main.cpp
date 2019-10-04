#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "No.h"
#include "Aresta.h"
#include "Grafo.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Dijkstra.h"
#include "Floyd.h"
#include <vector>
#include <fstream>
#include <cstdio>
#include <chrono>

int main(int argc, char * argv[]) {

    int pesoAresta = 0;
    bool direcionado = 0;
    vector< No > vertices;
    Grafo *grafo = new Grafo();
    cout << argv[1] << endl;
    ifstream myfile (argv[1]);
    ofstream outfile;
    outfile.open(argv[2], std::ofstream::app);
    string aux;


    while(!myfile.eof())
    {
        getline (myfile, aux, ' ');
        int id1 = atoi (aux.c_str());
        No *vertice = new No(id1);
        grafo->adicionaVertice(vertice);
        aux.clear();
        getline (myfile, aux);
        int id2 = atoi (aux.c_str());
        No *vertice1 = new No(id2);
        grafo->adicionaVertice(vertice1);
        aux.clear();
        grafo->arestas.push_back(grafo->getNo(vertice->id)->adicionaNoAdjacente(grafo->getNo(vertice1->id),direcionado,pesoAresta));
    }

    grafo->printListaAdjacencia();
    return 0;
}