//
// Created by gabri on 03/10/2019.
//

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
    No *NoInicial = grafo->getNo(id1);///Pega o no inicial
    NoInicial->distancia = 0;///Coloca a distancia do No sendo igual a zero
    for(unsigned int i = 0 ; i < grafo->listaNo.size(); i++)///Loop para testar todas as possíveis possibilidades
    {
        for(auto  adjacente : grafo->listaNo[i]->nosAdjacentes)///Pega somenten os nos adjacentes
        {
            Aresta *aresta = grafo->getAresta(grafo->listaNo[i]->id, adjacente->id); ///busca uma aresta ja criada
            if(grafo->listaNo[i]->distancia != numeric_limits<int>::max())///Testa para ver se a distancia do elemento é igual a infinito
            {
                if( adjacente->distancia > aresta->peso + grafo->listaNo[i]->distancia)///Verifica se a distancia atual e menor que a salva no sistema
                {
                    adjacente->distancia = aresta->peso + grafo->listaNo[i]->distancia;///Troca o valor da distancia
                }
            }

        }
    }
    int custo = grafo->listaNo[id2-1]->distancia;
    if( custo < numeric_limits<int>::max()){
        cout<<"A distancia minima e :"<<custo<<endl;///Imprime a distancia minima na posição referida
    }else{
        cout << "Não existe caminho entre os dois vértices." << endl;///Imprime um aviso ao usuario
    }

    for(unsigned int j =  0; j < grafo->listaNo.size() ; j++)///Loop para percorrer todos os elementos e depois colocar a distancia deles sendo inifinito
    {
        grafo->listaNo[j]->distancia = numeric_limits<int>::max();///Retorna o valor das distancia pra proxima busca
    }
}