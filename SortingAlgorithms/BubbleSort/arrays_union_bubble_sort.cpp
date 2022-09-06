#include <iostream>
#include <vector>

using namespace std;

//Protótipos das Funções
void concatenaVet(int *vetA, int *vetB, int *vetC, int tamA, int tamB);
void bubbleSort(int *vet, int tam);
void swap(int *vet, int posi1, int posi2);
void printVectors(int *vet, int tam) ;

int main() {
    int A, B;  //A para o num de elementos do vetA, e B para vetB
    int *vet_A = new int[100];  //vet_A recebe os elementos do primeiro vetor
    int *vet_B = new int[100];  //vet_B recebe os elementos do segundo vetor
    int *vet_C = new int[100];  //vet_C é a concatenação dos vetores vet_A e vet_B

    cin >> A;
    if (A > 100) return 0;

    for (int i = 0; i < A; ++i)
        cin >> vet_A[i];

    cin >> B;
    if (B > 100) return 0;

    for (int i = 0; i < B; ++i)
        cin >> vet_B[i];

    //Concatena os vetores vet_A e vet_B resultando no vetor vet_C
    concatenaVet(vet_A, vet_B, vet_C, A, B);

    //Ordena o vetor resultante da concatenação utilizando o método couting-sort
    bubbleSort(vet_C, A + B);

    printVectors(vet_C, A + B);

    //Libera a memória alocada para os vet A, B e C
    delete[] vet_A;
    delete[] vet_B;
    delete[] vet_C;

    return 0;
}

void concatenaVet (int *vetA, int *vetB, int *vetC, int tamA, int tamB) {
    int aux;

    //percorre o vetor vet_A atribuindo os valores ao final do vet_C
    for (int i = 0; i < tamA; i++)
        vetC[i] = vetA[i];


    //percorre o vetor vet_B atribuindo os valores ao final do vet_C
    for (int i = 0; i < tamB; i++)
        vetC[i+(tamA)] = vetB[i];

    return;
}

void bubbleSort(int *vet, int tam) {
    int i, j, key = 0;

    //Percorre o vetor comparando a cada duas posições, troca caso as posições estejam decrescente.
    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - 1 - i; j++)
            if (vet[j + 1] < vet[j]) 
                swap(vet, j, j + 1);
    }

    return;
}

void swap(int *vet, int posi1, int posi2) {
    int aux;

    //faz a troca entre as posições
    aux = vet[posi1];
    vet[posi1] = vet[posi2];
    vet[posi2] = aux;

    return;
}


void printVectors(int *vet, int tam) {

    //Imprime o vetor de saida
    for (int i = 0; i < tam; ++i) {
        cout << vet[i] << " ";
    }
    cout << endl;

    return;
}