#include "Grafo.h"
#include "No.h"
#include "stdio.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>
#include <map>
#include <istream>
#include <iostream>

using namespace std;

Grafo::Grafo()
{

}

Grafo::~Grafo()
{

}

int Grafo::getGrau()
{
    return grau;
}

void Grafo::setGrau(int val)
{
    grau = val;
}

int Grafo::getOrdem()
{
    return ordem;
}

void Grafo::setOrdem(int val)
{
    ordem = val;
}

bool Grafo::getNoPonderado()
{
    return noPonderado;
}

void Grafo::setNoPonderado(bool val)
{
    noPonderado = val;
}

void Grafo::matrizAdjacencia(bool direcionado)
{
    int tam = listaNo.size();
    int matriz[tam][tam];
    for(int l = 0 ; l < tam ; l++)
        for(int t = 0 ; t < tam ; t++)
            matriz[l][t] = 0;
    for(int i = 0; i < tam; i++)
    {
        No *elementoi = listaNo[i];
        for(int j = 0; j < tam; j++)
        {
            No *elementoj = listaNo[j];
            if(elementoi->verificaAdjacencia(elementoj))
            {
                matriz[i][j]=1;
                if(direcionado == 1)
                {
                    matriz[j][i] = -1;
                }
            }
            else
            {
                if( i > j )
                {
                    if(matriz[j][i] == 0)
                    {
                        matriz[i][j]=0;
                    }
                }
                else
                {
                    matriz[i][j] = 0;
                }
            }
        }
    }
    for(int i = 0; i < tam; i++)
    {
        if(i == 0)
        {
            cout << "    ";
            for(int i = 0; i < tam; i++)
                cout << " [" << listaNo[i]->id << "] ";
            cout << endl;
        }

        for(int j = 0; j < tam; j++)
        {
            if(j == 0)
                cout << "[" << listaNo[i]->id << "] ";
            cout << " [" << matriz[i][j] << "] ";
        }
        cout << endl;
    }
}
void Grafo::printListaAdjacencia()
{
    int tam = listaNo.size();
    for(int i = 0; i < tam; i++)
    {
        cout << endl;
        No *elemento = listaNo[i];
        vector<No*> adjacentes = elemento->getAdjacentes();
        cout << elemento->id;
        for(int j = 0; j < tam; j++)
        {
            if(elemento->verificaAdjacencia(listaNo[j]))

            {
                cout << " -> " << listaNo[j]->id;
            }
        }
    }
    cout << endl;
}

void Grafo::adicionaVertice(No *no)
{
    if(verificaId(no->id))
    {
        ///cout << "Esse id ja esta sendo utilizado, digite um id valido" << endl;
    }
    else
    {
        listaNo.push_back(no);
        //cout << "****** No adicionado com sucesso *****" << endl;
    }
}

bool Grafo::verificaId(int id)
{
    for(auto no : listaNo)
    {
        if(no->id == id)
        {
            return true;
        }
    }
    return false;
}

No * Grafo::getNo(int id)
{
    if(verificaId(id))
    {
        for(auto no : listaNo)
        {
            if(no->id == id)
                return no;
        }
    }
    return NULL;
}

void Grafo::printNos()
{
    cout << "Lista de vertices do grafo: " << endl;
    for(auto no : listaNo)
    {
        cout << no->id << " ";
    }
    cout << endl;
}

void Grafo::printAdjacentesAoNo()
{
    cout << "Digite o id do no desejado: ";
    int id;
    cin >> id;
    No* noDesejado = getNo(id);
    noDesejado->printAdjacentes();
}



Aresta * Grafo::getAresta(int id1, int id2)
{
    for(auto aresta : this->arestas)
    {
        if((aresta->no1->id == id1 ||
            aresta->no1->id == id2) &&
           (aresta->no2->id == id1 ||
            aresta->no2->id == id2))
            return aresta;
    }
    return NULL;
}

void Grafo::removeAresta()
{
    cout << "Digite o id do vertice de uma das extremidades da aresta a ser excluida: " << endl;

    int idNo1;
    cin >> idNo1;
    No *no1 = getNo(idNo1);

    no1->printAdjacentes();

    cout << "Digite o id da outra extremidade da aresta que voce quer remover: " << endl;

    int idNo2;
    cin >> idNo2;
    No* no2 = getNo(idNo2);

    no1->removeAdjacente(no2);
    no2->removeAdjacente(no1);

    cout << "Aresta removida com sucesso!" << endl;

    if(no1->nosAdjacentes.size() == 0)
    {
        auxRemoveVertice(no1);
        cout << "Como o vertice de id " << no1->id
             << " nao tem mais arestas, ele foi removido! (O grafo nao suporta subgrafos desconexos)" << endl;
    }

    if(no2->nosAdjacentes.size() == 0)
    {
        auxRemoveVertice(no2);
        cout << "Como o vertice de id " << no2->id
             << " nao tem mais arestas, ele foi removido! (O grafo nao suporta subgrafos desconexos)" << endl;
    }
}

void Grafo::removeVertice()
{
    cout << "Digite o id do vertice a ser removido: ";
    int id;
    cin >> id;
    No* noASerRemovido = getNo(id);
    removeTodasAdjacenciasDeUmNo(noASerRemovido);
    auxRemoveVertice(noASerRemovido);
}

void Grafo::auxRemoveVertice(No* noASerRemovido)
{
    for(unsigned int i = 0; i < listaNo.size(); i++)
    {
        if(listaNo[i] == noASerRemovido)
        {
            listaNo.erase(listaNo.begin() + i);
        }
    }
}
void Grafo::removeTodasAdjacenciasDeUmNo(No* noASerRemovido)
{
    while(!noASerRemovido->nosAdjacentes.empty())   /// vai retirando os nos adjacentes ate o vetor nosAdjacentes estiver vazio
    {
        noASerRemovido->nosAdjacentes.pop_back();
    }
}

/**
 * Inicia o caminhamento em profundidade, que chama a função auxiliar aprofunda(No* no)
 * @return void
*/
void Grafo::caminhamentoEmProfundidade() ///funcao principal, que chama a funcao que, de fato, faz o caminhamento
{
    setVisitadoEmTodosNos(false);
    for(auto i : listaNo)
    {
        if(!i->getVisitado())
        {
            aprofunda(i);
        }
    }
    cout << endl;
}

void Grafo::aprofunda(No* no)
{
    no->setVisitado(true);
    cout << "Visitando no " << no->id << endl;
    for(auto adjacente : no->nosAdjacentes)
    {
        No* adjacenteAtual = adjacente;
        if(!adjacenteAtual->getVisitado())
        {
            cout << "\tNo " << adjacenteAtual->id << " nao foi visitado ainda!" << endl;
            aprofunda(adjacenteAtual);
        }
        else
        {
            cout << "\tNo " << adjacenteAtual->id << " ja foi visitado!" << endl;
        }

    }
}

void Grafo::aprofunda_ComponenteConexa(No* no)
{
    no->setVisitado(true);
    cout << no->id << " - ";
    for(auto adjacente : no->nosAdjacentes)
    {
        No* adjacenteAtual = adjacente;
        if(!adjacenteAtual->getVisitado())
        {
            aprofunda_ComponenteConexa(adjacenteAtual);
        }
    }
}

/**
 * Inicia o caminhamento em largura, que chama a função auxiliar caminhaEmLargura(vector<No*> fila)
 * @param id id do nó a partir do qual o caminhamento começa
 * @return void
*/
void Grafo::caminhamentoEmLargura(int id)   ///funcao principal, que chama a funcao que, de fato, faz o caminhamento
{
    setVisitadoEmTodosNos(false);

    No *noInicial = getNo(id);
    vector<No*> *fila = new vector<No*>;
    fila->push_back(noInicial);

    caminhaEmLargura(*fila); ///chama funcao auxiliar, que faz o caminhamento em largura
}

/**
 * Função que faz, de fato, o caminhamento
 * @param fila estrutura que vai armazenar os nós que serão visitados
 * @return void
*/
void Grafo::caminhaEmLargura(vector<No*> fila)
{
    while(!fila.empty())
    {
        No *noAtual = fila.front();
        cout << "Visitando o no " << noAtual->id << endl;
        noAtual->setVisitado(true);

        for(auto adjacenteAoAtual : noAtual->nosAdjacentes)
        {
            if(!adjacenteAoAtual->getVisitado())
            {
                int contador = count(fila.begin(), fila.end(), adjacenteAoAtual); /// verifica se adjacenteAoAtual está na fila
                if(contador == 0) /// nao permite adicionar um mesmo elemento mais de uma vez na fila
                {
                    fila.push_back(adjacenteAoAtual);
                    cout << "Adicionando na fila o no " << adjacenteAoAtual->id << endl;
                }
            }
        }
        fila.erase(fila.begin());
    }
}

void Grafo::setVisitadoEmTodosNos(bool visitado)
{
    for(auto no : listaNo)
    {
        no->setVisitado(visitado);
    }
}

void Grafo::componentesConexas()
{
    cout << "Componentes conexas: " << endl;
    setVisitadoEmTodosNos(false);
    for(auto no : listaNo)
    {
        if(!no->getVisitado())
        {
            cout << endl << "Componente conexa comencando em " << no->id << ": ";
            aprofunda_ComponenteConexa(no);
        }
    }
    cout << endl;
}

void Grafo::adicionaVerticePonderado(No *no, int peso)
{

    if(verificaId(no->id))
    {
        cout << "Esse id ja esta sendo utilizado, digite um id valido" << endl;
    }
    else
    {
        listaNo.push_back(no);
        cout << "****** No adicionado com sucesso *****" << endl;
        no->setPeso(peso);
        cout << "****** Peso no vertice adicionado com sucesso *****"<<endl;

    }
}

void Grafo::imprimePesoVertice()
{
    No *peso;
    int conferePeso;
    cout<<"Digite o vertice que deseja saber o peso"<<endl;
    cin>> conferePeso;
    if(verificaId(conferePeso))
    {
        peso = getNo(conferePeso);
        cout<<"O peso do vertice "<<conferePeso<<" e: "<<peso->getPeso()<<endl;
    }
    else
    {
        cout<<"O Vertice inserido nao existe no grafo"<<endl;
    }
}
void Grafo::imprimePesoAresta()
{
    int confereIdADj = 0;
    int confereId = 0 ;
    cout<<"Digite o primeiro vertice"<<endl;
    cin>>confereId;
    cout<<"Digite o segundo vertice"<<endl;
    cin>>confereIdADj;
    if(possuiAresta(confereId, confereIdADj))
    {
        cout<<"O peso da aresta entra os vertices ["<<confereId
            <<"] ["<<confereIdADj<<"] e: "<<auxImprimePesoAresta(confereId)<<endl;
    }
    else
    {
        cout<<"Um dos vertices inseridos no programa nao possui aresta"<<endl;
    }
}

int Grafo::auxImprimePesoAresta(int id1)
{
    // No *elemento = getNo(id1);
//   return elemento->getPesoAresta();
    return 2;
}

bool Grafo::possuiAresta(int id1, int id2)
{
    No *elemento = getNo(id1);
    for(unsigned int i = 0; i< elemento->nosAdjacentes.size(); i++)
    {
        if(elemento->nosAdjacentes[i]->id == id2)
        {
            return true;
        }
    }
    return false;

}



void Grafo::ordenacaoTopologica()
{
    int n = listaNo.size(); //vertices
    int m =0; // arestas
    int grafo[n];
    int grau[n];
    int lista[n]; // dos vï¿½rtices de grau zero
    int listaPos = 0; //posiï¿½ï¿½o de inserï¿½ï¿½o na lista
    No *atual;
    atual = NULL;
    for(int i = 0; i<n; i++)
    {
        m = m+ listaNo[i]->getGrau();
        grafo[i] = listaNo[i]->id;
        grau[i]=listaNo[i]->getGrau();
        lista[i]=0;
    }

    while(listaPos < n)
    {
        ///--------------------------------quando o grau minimo nï¿½o ï¿½ 0 -------------------------------------------///
        while(grauMinimo(grau,n)!= 0 && grauMinimo(grau,n)>0)
        {
            for(int i = 0; i< n; i++)
            {
                if(grau[i] == grauMinimo(grau,n))  /// se o grau for o grau minimo
                {
                    lista[listaPos] = grafo[i]; ///coloco o vertice na posiï¿½ï¿½o listaPos da lista
                    listaPos++; /// atualizo listaPos para a proxima inserï¿½ï¿½o
                    for(int t = 0; t < n; t++)
                    {
                        if(listaNo[t]->id == grafo[i])
                            atual = listaNo[t]; /// No atual recebe o No com o id
                    }

                    for(unsigned int j = 0; j< atual->nosAdjacentes.size(); j++) /// para todos os adjacentes ao no com grau mï¿½nimo
                    {
                        for(int k =0; k<n; k++)  ///percorro todos os vevrtices do grafo[] procurando alguem com aquele id
                        {
                            if(grafo[k] == atual->nosAdjacentes[j]->id)/// se o vetice tiver aquele id
                                grau[k] = grau[k]- 1;///diminuo 1 do grau do vertice que estï¿½ na posiï¿½ï¿½o k, sabendo que recebia uma aresta do vertce atual
                        }

                    }

                    grafo[i] = -1; // retiro o vertice do grafo[]
                    grau[i] = -1; // coloco um grau nulo para as proximas iteraï¿½ï¿½es
                }
            }
        }


        ///--------------------------------quando o grau minimo ï¿½ 0 -------------------------------------------///
        for(int i = 0; i< n; i++)
        {
            if(grau[i] == 0)  /// se o grau for 0
            {
                lista[listaPos] = grafo[i]; ///coloco o vertice na posiï¿½ï¿½o listaPos da lista
                listaPos++; /// atualizo listaPos para a proxima inserï¿½ï¿½o
                for(int t = 0; t < n; t++)
                {
                    if(listaNo[t]->id == grafo[i])
                        atual = listaNo[t]; /// No atual recebe o No com o id
                }

                for(unsigned int j = 0; j< atual->nosAdjacentes.size(); j++) /// para todos os adjacentes ao no com grau 0
                {
                    for(int k =0; k<n; k++)  ///percorro todos os vevrtices do grafo[] procurando alguem com aquele id
                    {
                        if(grafo[k] == atual->nosAdjacentes[j]->id)/// se o vetice tiver aquele id
                            grau[k] = grau[k]- 1;///diminuo 1 do grau do vertice que estï¿½ na posiï¿½ï¿½o k, sabendo que recebia uma aresta do vertce atual
                    }

                }


                grafo[i] = -1; // retiro o vertice do grafo[]
                grau[i] = -1; // coloco um grau nulo para as proximas iteraï¿½ï¿½es
            }
        }
    }
    cout << "lista em ordenacao topologica: [ ";
    for(int i =0; i<n; i++)
    {
        cout << lista[i] << " ";
    }
    cout << "]"<<endl;

}


int Grafo::grauMinimo(int graus[], int n)
{
    int grauMin =numeric_limits<int>::max();

    for (int i =0; i<n ; i++)
    {
        if(graus[i]<grauMin)
            grauMin = graus[i];
    }

    return grauMin;
}

void Grafo::printSequenciaDeGraus()
{
    vector<int> graus;

    for(auto no : listaNo) ///preenche o vector graus com o grau de cada no
    {
        graus.push_back(no->getGrau());
    }

    sort(graus.begin(), graus.end(), greater<int>()); ///ordena o vector graus

    cout << "Sequencia de graus: " << endl;

    cout << "<";
    for(auto grau : graus)
    {
        cout << grau << ", ";
    }
    cout << ">" << endl;
}


void Grafo::preenche(No  *v, stack<No*>& pilha)
{
    v->setVisitado(true);
    for(unsigned int i=0; i < v->nosAdjacentes.size(); i++)
    {
        No* adjacenteAtual = v->nosAdjacentes[i];
        if(!adjacenteAtual->getVisitado())
        {
            /// cout << "\tNo " << adjacenteAtual->id << " nao foi visitado ainda!" << endl; *BUSCANORMAL*
            preenche(adjacenteAtual, pilha);
        }

    }
    pilha.push(v);

}

void Grafo::matrizDistancia()
{
    int n = listaNo.size(); ///numero devertices
    int id1, id2;
    id1=id2=0;
    Aresta* aresta;
    int pesoAresta=0;

    /// ------------------------Entendendo o cÃ³digo abaixo -----------------------------------------------------------------
    /// caso seja adjacente, pega a distancia (peso) da aresta entre 2 nohs, caso nao seja, seta 9999999999
    /// com grafos orientados, quando um nÃ³ a, Ã© direcionado ao b, se tentarmos pegar a adjacencia de b para a, seria como se
    /// fossem nÃ£o adjacentes, sendo assim, a distancia serÃ¡ setada como 9999999999
    /// caminho de um noh ao mesmo noh recebem 0
    /// --------------------------------------------------------------------------------------------------------------------
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j)
            {
                mDistancia[i][j]=0;
            }
            else if(listaNo[i]->verificaAdjacencia(listaNo[j]) && i!=j) /// no caso, ainda precisamos implementar uma funcao que
            {
                /// verifica se existe um caminho entre 2 nohs, e nao apenas
                id1=listaNo[i]->id;                               /// se os 2 sao adjacentes... sendo assim, este metodo
                id2=listaNo[j]->id;                               /// matrizDistancia, ainda nao funciona como deveria
                aresta = getAresta(id1, id2);
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




/// Encontra o menor caminho entre todos os pares usando o algorÃ­tmo de Floyd Warshall
void Grafo:: floyd()
{
    int V = listaNo.size();

    ///primeiro chamamos a funÃ§Ã£o matrizDistancia para popular a matriz mDistancia
    matrizDistancia();

    ///matriz que conterÃ¡ as menores distÃ¢ncias entre todos os pares de vÃ©rtices
    int dist[V][V], i, j, k;

    ///inicializando os valores de dist com os mesmos valores de mDistancia
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = mDistancia[i][j];

    for (k = 0; k < V; k++)
    {
        /// pega todos os vertices como fonte, um a um
        for (i = 0; i < V; i++)
        {
            /// pega todos os vertices como destinacao para a fonte selecionada
            for (j = 0; j < V; j++)
            {
                /// se o indice k eh o caminho mais curto de i a j, entao atualizamos o valor de dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    ///imprimie a solucao de Floyd
    cout<<"A seguinte matriz apresenta as menores distancias entre cada par de vertices" << endl;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == 99999)
                cout<<"inf"<<"   ";
            else
                cout<<dist[i][j]<<"  ";
        }
        cout<<endl;
    }
}

/// Verifica se um grafo eh conexo ou nao
bool Grafo::ehConexo()
{
    for(auto no : this->listaNo)
    {
        if(no->arestas.empty())
            return false;
        else
            return true;
    }
    return true;
}