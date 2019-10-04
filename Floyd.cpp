#include "Grafo.h"
#include <vector>
#include "Floyd.h"
#include <limits>
using namespace std;

/**
 * Gera uma matriz Distancia que será utilizada como input no algoritmo de Floyd Warshall
 * @param Grafo
 * @return void
*/

void Floyd::matrizDistancia(Grafo *grafo)
{
    int n = grafo->listaNo.size(); ///vértices
    int id1, id2;
    id1=id2=0;
    Aresta* aresta;
    int pesoAresta=0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j)
            {
                mDistancia[i][j]=0;
            }
            else if(grafo->listaNo[i]->verificaAdjacencia(grafo->listaNo[j]) && i!=j)
            {
                id1=grafo->listaNo[i]->id;
                id2=grafo->listaNo[j]->id;
                aresta = grafo->getAresta(id1, id2);
                pesoAresta= aresta->peso;
                mDistancia[i][j]=pesoAresta;
            }
            else
            {
                mDistancia[i][j] = numeric_limits<int>::max();
            }
        }
    }
}

/**
 * Encontra o menor caminho entre todos os pares usando o algoritmo de Floyd Warshall
 * @param Grafo
 * @return void
*/

///
void Floyd::floyd(Grafo *grafo)
{
    int V = grafo->listaNo.size();

    ///popular a matriz mDistancia
    matrizDistancia(grafo);

    ///matriz com menores distancias entre tuplas de vértices
    int dist[V][V], i, j, k;

    ///inicializa os valores de dist com os mesmos valores de mDistancia
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = mDistancia[i][j];

    for (k = 0; k < V; k++)
    {
        ///todos os vertices como fonte
        for (i = 0; i < V; i++)
        {
            ///todos os vertices como destinacao para a fonte
            for (j = 0; j < V; j++)
            {
                ///verifica se k é o caminho mais curto entre i e j, se sim, atualizamos o valor da distancia
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    ///atulizar os valores de mDistancia
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            mDistancia[i][j] = dist[i][j];
}

/**
 * imprimie a solucao de Floyd - funcao que é chamada pelo menu principal
 * @param
 * @return void
*/
void Floyd::imprimeFloyd(Grafo *grafo)
{
    ///montar a matriz com as menores distancias - floyd()
    floyd(grafo);

    ///a impressao
    cout<<"A seguinte matriz apresenta as menores distancias entre cada par de vertices" << endl;

    int V = grafo->listaNo.size();

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (mDistancia[i][j] == 99999)
                cout<<"inf"<<"   ";
            else
                cout<<mDistancia[i][j]<<"  ";
        }
        cout<<endl;
    }
}