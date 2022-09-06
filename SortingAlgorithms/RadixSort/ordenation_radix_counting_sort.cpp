#include <iostream>
#include <vector>
#include <string>

#define MAX_SIZE 100000

using namespace std;

//Protótipos das Funções
void strTolower (struct Nomes *vet, int tam);
void RadixSort (struct Nomes *vet_Nomes, struct Nomes *vet_Saida, int numNomes);
void CountingSort (struct Nomes *vet_Nomes, struct Nomes *vet_Saida, int numNomes, int posiChar);
void imprimeRadix (int *vet, int tam);
void imprimeNomes (struct Nomes *vet, int ini, int fim);

//Struct para os nomes, com um string para o nome e um inteiro para o tamanho do nome
struct Nomes {
    int size = 0;
    string nome;
};

int main() {
    int N, P, M;  //N para número de entradas, P para ponto de inicio da impressão e M quantidade a ser impressa apos inicio
    Nomes *vet_Nomes = new Nomes[MAX_SIZE];  //vet_Nomes recebe os elementos de entrada
    Nomes *vet_Saida = new Nomes[MAX_SIZE];  //vet_Saida auxilia a ordenar os elementos e resulta no vetor final

    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> vet_Nomes[i].nome;
        vet_Nomes[i].size = vet_Nomes[i].nome.size();
    }

    strTolower(vet_Nomes, N); //Converte os caracteres das strings para minúculo

    cin >> P >> M;

    //Ordena o vetor de strings utilizando os métodos couting-sort a partir do radix-sort
    RadixSort(vet_Nomes, vet_Saida, N);

    imprimeNomes(vet_Saida, P - 1, M);  //Imprime o resultado final


    //Limpa o espaço de memória alocado para os vetores
    delete[] vet_Saida;
    delete[] vet_Nomes;

    return 0;
}

void strTolower (struct Nomes *vet, int tam) {

    //Percorre o vetor de strings convertendo caracteres maiúsculos para minúsculos baseado na tabela ASCII
    for (int i = 0; i < tam; ++i) {
        for (int j = 0; j < vet[i].size; ++j) {
            if (vet[i].nome[j] >= 65 and vet[i].nome[j] <= 90)
                vet[i].nome[j] += 32;
        }
    }
}

void RadixSort (struct Nomes *vet_Nomes, struct Nomes *vet_Saida, int numNomes) {
    int digitos;

    //Acha a string com o maior número de caracteres
    digitos = vet_Nomes[0].size;
    for (int i = 1; i < numNomes; ++i) {
        if (vet_Nomes[i].size > digitos) digitos = vet_Nomes[i].size;
    }

    //Baseado na string com maior número de caracteres executa couting-sort na coluna de número i
    for (int i = digitos - 1; i >= 0; i--) {
        CountingSort(vet_Nomes, vet_Saida, numNomes, i);
    }
}

void CountingSort (struct Nomes *vet_Nomes, struct Nomes *vet_Saida, int numNomes, int posiChar) {

    int *vetAux = new int[27];
    int maior = 26, aux;

    //Inicializa o vetor auxiliar de contagem (vetAux)
    for (int i = 0; i <= maior; i++)
        vetAux[i] = 0;

    //para cada elemento do vetor principar (vet_Nomes), atribui +1 a posição desse elemento no vetor auxiliar
    for (int i = 0; i < numNomes; i++) {
        aux = ((int) vet_Nomes[i].nome[posiChar]) - 96;
        if (vet_Nomes[i].size > posiChar && aux > 0) {
            vetAux[aux]++;
        } else {
            vetAux[0]++;
        }
    }

    //Faz uma soma em pré-ordem, cada elemento recebe ele mesmo + o elemento anterior
    for (int i = 1; i <= maior; i++)
        vetAux[i] += vetAux[i - 1];

    //imprime Radix, o vetor ordenado resultante.
    imprimeRadix(vetAux, maior);


    //Percorre o vet_Nomes de trás pra frente consultando onde o elemento naquela posição deveria estar baseado no vetAux
    for (int i = numNomes - 1; i >= 0; i--) {
        aux = ((int) vet_Nomes[i].nome[posiChar]) - 96;
        if (vet_Nomes[i].size > posiChar && aux > 0) {
            vet_Saida[vetAux[aux] - 1].size = vet_Nomes[i].size;
            vet_Saida[vetAux[aux] - 1].nome = vet_Nomes[i].nome;
            vetAux[aux]--;
        } else {
            vet_Saida[vetAux[0] - 1].size = vet_Nomes[i].size;
            vet_Saida[vetAux[0] - 1].nome = vet_Nomes[i].nome;
            vetAux[0]--;
        }
    }

    //Copia o resultado da ordenação para o vet_Nomes
    for (int i = 0; i < numNomes; ++i) {
        vet_Nomes[i].size = vet_Saida[i].size;
        vet_Nomes[i].nome = vet_Saida[i].nome;
    }

    delete[] vetAux;
}

void imprimeRadix (int *vet, int tam) {

    for (int i = 0; i <= tam; ++i) {
        cout << vet[i] << " ";
    }
    cout << endl;
}

void imprimeNomes (struct Nomes *vet, int ini, int fim) {

    for (int i = ini; i < (fim + ini); ++i) {
        cout << vet[i].nome << endl;
    }
}