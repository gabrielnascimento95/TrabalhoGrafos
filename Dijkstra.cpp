

#include "Dijkstra.h"
#include "Grafo.h"
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

/**
 * Calcula o custo de um caminho mínimo entre dois nos
 * @param Grafo
 * @param int
 * @param int
 * @return void
*/
void Dijkstra::custoCaminhoMinimo(Grafo *grafo, int id1, int id2)
{
    No *NoInicial = grafo->getNo(id1); /// No inicial
    NoInicial->distancia = 0; /// distancia do no = 0
    for(unsigned int i = 0 ; i < grafo->listaNo.size(); i++) ///for para testar as possibilidades
    {
        for(auto  adjacente : grafo->listaNo[i]->nosAdjacentes) ///buscar os adjacentes
        {
            Aresta *aresta = grafo->getAresta(grafo->listaNo[i]->id, adjacente->id); ///achar aresta criada
            if(grafo->listaNo[i]->distancia != numeric_limits<int>::max())///checa se distancia do elemento é igual infinito
            {
                if( adjacente->distancia > aresta->peso + grafo->listaNo[i]->distancia)///checa se distancia atual é menor que a já existente
                {
                    adjacente->distancia = aresta->peso + grafo->listaNo[i]->distancia;///Mudar valor da distancia
                }
            }

        }
    }
    int custo = grafo->listaNo[id2-1]->distancia;
    if( custo < numeric_limits<int>::max()){
        cout<<"A distancia minima e :"<<custo<<endl;///dada a posição, imprime a distancia minima
    }else{
        cout << "Não existe caminho entre os dois vértices." << endl;///aviso ao usuario
    }

    for(unsigned int j =  0; j < grafo->listaNo.size() ; j++)///for para setar a distancia deles sendo inifinito, percorrendo todos os elementos
    {
        grafo->listaNo[j]->distancia = numeric_limits<int>::max();///Retorna o valor das distancias para próxima busca
    }
}