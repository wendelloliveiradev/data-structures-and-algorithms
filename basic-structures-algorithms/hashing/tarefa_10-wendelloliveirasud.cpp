#include <iostream>

using namespace std;

struct elemento {
    int numero;
    struct elemento *ant;
    struct elemento *prox;
};

struct LDE {
    struct elemento *inicio, *fim;
};

/* PROTOTIPOS DAS FUNCOES */
void InicializarLDE (LDE *hashTab, int tamanho);
void Inserir (LDE *hashTab, int numero, int tamanho);
int hashFUN (int k, int m);
bool Pesquisar (LDE *hashTab, int numero, int tamanho);
void Remover (LDE *hashTab, int numero, int tamanho);
void Imprimir (LDE *hashTab, int tamanho);

int main() {
    int numero, tamanho, nums;
    LDE *hashTab = new LDE[10000];
    bool TEM;

    cin >> tamanho;
    cin >> nums;

    if (tamanho == 0)
        return 0;
    if (nums > tamanho)
        return 0;

    InicializarLDE(hashTab, tamanho);  //Inicializa a tabela hash

    for (int i = 0; i < nums; ++i) {
        cin >> numero;
        Inserir(hashTab, numero, tamanho);  //Insere elementos na tabela hash
    }

    cin >> numero;

    TEM = Pesquisar(hashTab, numero, tamanho); //Pesquisa se o número já esta na tabela hash

    if (TEM)  //Caso já esteja na tabela remove da tabela hash
        Remover(hashTab, numero, tamanho);
    else      //Se não insere na tabela hash
        Inserir(hashTab, numero, tamanho);

    Imprimir(hashTab, tamanho);   //Imprime tabela hash final

    delete [] hashTab;
    return 0;
}

void InicializarLDE (LDE *hashTab, int tamanho) {

    for (int i = 0; i <= tamanho; ++i) {
        hashTab[i].inicio = NULL;
        hashTab[i].fim = NULL;
    }
}

void Inserir (LDE *hashTab, int numero, int tamanho) {
    int hashNum;
    elemento *aux = new elemento;

    hashNum = hashFUN(numero, tamanho);

    if (hashTab[hashNum].inicio == NULL) {
        aux->numero = numero;
        aux->ant = NULL;
        aux->prox = NULL;
        hashTab[hashNum].inicio = aux;
        hashTab[hashNum].fim = aux;
    }
    else {
        aux->numero = numero;
        aux->ant = hashTab[hashNum].fim;
        aux->prox = NULL;
        hashTab[hashNum].fim->prox = aux;
        hashTab[hashNum].fim = aux;
    }
}

int hashFUN (int k, int m) {
    return (k % m);
}

bool Pesquisar (LDE *hashTab, int numero, int tamanho) {
    int i;
    i = hashFUN(numero, tamanho);

    elemento *aux = hashTab[i].inicio;

    while (aux != NULL) {
        if (aux->numero == numero)
            return true;
        else
            aux = aux->prox;
    }

    return false;
}

void Remover (LDE *hashTab, int numero, int tamanho) {
    int i;
    i = hashFUN(numero, tamanho);

    elemento *aux = hashTab[i].inicio;

        while (aux != NULL) {
            if (aux->numero == numero) {
                if (aux == hashTab[i].inicio) {
                    hashTab[i].inicio = aux->prox;
                    aux = NULL;
                } else if (aux == hashTab[i].fim) {
                    hashTab[i].fim = aux->ant;
                    aux = NULL;
                } else {
                    aux->ant->prox = aux->prox;
                    aux->prox->ant = aux->ant;
                    aux = NULL;
                }
            }
            else
                aux = aux->prox;
        }
}

void Imprimir (LDE *hashTab, int tamanho) {
    elemento *aux = hashTab[0].inicio;

    for (int i = 1; i <= tamanho; ++i) {
        cout << "[" << i - 1 << "]";
        while (aux != NULL) {
            cout << " " << aux->numero;
            aux = aux->prox;
        }
        cout << endl;
        aux = hashTab[i].inicio;
    }
}
