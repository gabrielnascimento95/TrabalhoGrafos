//
// Created by gabri on 03/10/2019.
//

#ifndef GRAFOS2_GRAFO_H
#define GRAFOS2_GRAFO_H

#include "No.h"
#include <vector>
#include <iostream>
#include <stack>
#include <time.h>
#include <fstream>

using namespace std;

struct vertice_nivel
{
    int nivel;
    bool verificado;
};

class Grafo
{
public:

    Grafo();
    ~Grafo();
    vector<No*> listaNo;
    vector<Aresta *> arestas;
    void adicionaVerticePonderado(No *no, int peso);
    int getOrdem();
    void setOrdem(int val);
    int getGrau();
    void setGrau(int val);
    bool getNoPonderado();
    void setNoPonderado(bool val);
    void printMatrizAdjacencia();
    void matrizAdjacencia(bool val);
    void printListaAdjacencia();
    void printNos();
    void adicionaVertice(No *no);
    void removeVertice();
    void auxRemoveVertice(No* noASerRemovido);
    void removeTodasAdjacenciasDeUmNo(No* noASerRemovido);
    void removeAresta();
    void matrizDistancia();
    bool possuiAresta(int id1, int id2);
    Aresta *getAresta(int id1, int id2);
    bool verificaId(int id);
    No * getNo(int id);
    void printAdjacentesAoNo();
    void caminhamentoEmProfundidade();
    void aprofunda_ComponenteConexa(No* no);
    void aprofunda(No* no);
    void caminhamentoEmLargura(int id);
    void setVisitadoEmTodosNos(bool visitado);
    void caminhaEmLargura(vector<No*> fila);
    void componentesConexas();
    void imprimePesoVertice();
    void imprimePesoAresta();
    vector<vector<long int> > mDistancia;
    int auxImprimePesoAresta(int val);
    void ordenacaoTopologica();
    int grauMinimo(int graus[], int n);
    void printSequenciaDeGraus();
    void preenche(No *v, stack<No*>& pilha);
    void floyd();
    void fecho_transitivo(int vertice_inicial, bool direto);
    bool ehConexo();
    vector<vertice_nivel> getVet_transitivo_direto() const;
    void setVet_transitivo_direto(const vector<vertice_nivel> &value);
    vector<vertice_nivel> getVet_transitivo_inverso() const;
    void setVet_transitivo_inverso(const vector<vertice_nivel> &value);

private:
    int ordem;
    int grau;
    bool noPonderado;
    int vertices;
    bool **matriz;
    vector<vertice_nivel> vet_transitivo_direto;
    vector<vertice_nivel> vet_transitivo_inverso;
};


#endif //GRAFOS2_GRAFO_H
