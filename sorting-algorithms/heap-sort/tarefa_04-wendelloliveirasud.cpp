#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Cabeçalho das Funções
void max_heapfy(struct vector<int> &vetHeap, int posi);
void build_max_heap(vector<int> &vetHeap);
int heap_extract_max(vector<int> &vetHeap);
void heapSort(vector<int> &vetHeap, vector<int> &vetSaida);
void swap(vector<int> &vetHeap, int posi, int pai);
void printHeap(vector<int> &Vet);
void printSaida(vector<int> &Vet);

int main()
{
    int N, cont, aux;
    vector<int> vetHeap;
    vector<int> vetSaida;

    vetHeap.reserve(10000);  //reserva espaço de memória para 100000 int.
    vetSaida.reserve(10000); //reserva espaço de memória para 100000 int.

    cin >> N; //pega o número de elementos a serem inseridos no vetor

    vetHeap.push_back(0); //o primeiro indice do vetor, não será utilizado

    for (cont = 1; cont <= N; cont++)
    { //insere os elementos no vetor vetHeap
        cin >> aux;
        vetHeap.push_back(aux);
    }

    //Chama o metódo de ordenação heapsort
    heapSort(vetHeap, vetSaida);

    //inverte o vetor de saída
    reverse(vetSaida.begin(), vetSaida.end());

    //remove o elemento no começo do vetor de saida vetSaida
    vetSaida.erase(vetSaida.begin());

    //printa o vertor devidamente ordenado na saida
    printSaida(vetSaida);

    //limpa os vetores e libera a memória
    vetHeap.clear();
    vetSaida.clear();

    return 0;
}

void heapSort(vector<int> &vetHeap, vector<int> &vetSaida)
{ //ordena e insere os elementos no vetor de saída
    int tam;

    build_max_heap(vetHeap);
    printHeap(vetHeap);

    tam = vetHeap.size();

    while (tam > 0)
    {
        vetSaida.push_back(heap_extract_max(vetHeap));
        tam--;
    }

    return;
}

void build_max_heap(vector<int> &vetHeap)
{
    int cont, tam = vetHeap.size();

    //pecorre do meio até o inicio do vetor ordenando os pais com seus respectivos filhos.
    for (cont = tam / 2; cont >= 1; cont--)
        max_heapfy(vetHeap, cont);

    return;
}

int heap_extract_max(vector<int> &vetHeap)
{ //pega o maior elemento do vetor (1) vetHeap
    int maior, ultimo;

    if (vetHeap.size() < 1)
        exit(0);

    maior = vetHeap[1];
    ultimo = vetHeap.size();
    vetHeap[1] = vetHeap[ultimo];
    vetHeap.erase(vetHeap.end() - 1); //apaga último elemento do vetHeap e diminui o tamanho do vetor
    max_heapfy(vetHeap, 1);

    return maior;
}

void max_heapfy(struct vector<int> &vetHeap, int posi)
{ //verifica qual das opções é o 'pai' e seus respectivos filhos
    int esq, dir, pai;

    esq = 2 * posi;
    dir = (2 * posi) + 1;

    if (esq <= vetHeap.size() and vetHeap[esq] > vetHeap[posi])
        pai = esq;
    else
        pai = posi;

    if (dir <= vetHeap.size() && vetHeap[dir] > vetHeap[pai])
        pai = dir;

    if (pai != posi)
    {
        swap(vetHeap, posi, pai);
        max_heapfy(vetHeap, pai);
    }

    return;
}

void swap(vector<int> &vetHeap, int posi, int pai)
{ //faz a troca de posição
    int aux;

    aux = vetHeap[posi];
    vetHeap[posi] = vetHeap[pai];
    vetHeap[pai] = aux;

    return;
}

void printHeap(vector<int> &Vet)
{ //printa o vetor vetHeap
    int cont;

    for (cont = 1; cont < Vet.size(); cont++)
    {
        cout << Vet[cont] << " ";
    }

    cout << endl;

    return;
}

void printSaida(vector<int> &Vet)
{ //printa o vetor vetSaida
    int cont;

    for (cont = 0; cont < Vet.size(); cont++)
    {
        cout << Vet[cont] << " ";
    }

    cout << endl;

    return;
}