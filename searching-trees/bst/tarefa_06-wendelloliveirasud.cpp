#include <iostream>

using namespace std;

int TAM_ABB = 0;  //Variável global para contagem de elementos na ABB
bool TEM = false;

//Structs
struct tipoNo {
    int numero;
    struct tipoNo *esq;
    struct tipoNo *dir;
};

struct tipoABB {
    tipoNo *raiz;
};

//Protótipos das Funções
void inicializar_ABB (tipoABB *arvore);
tipoNo *criar_No (int elemento, tipoNo *esq, tipoNo *dir);
void inserir_ABB (tipoNo *noRef, int elemento);
void buscar (tipoNo *noRef, int num);
void pesquisar_inserir (tipoNo *noRef, int num);
void pesquisar_remover (tipoNo *noRef, int num);
bool remover_ABB (tipoNo *noRef);
void buscar_Menor (tipoNo *noRef, tipoNo *prox);
void buscar_Maior (tipoNo *noRef, tipoNo *prox);
int altura_ABB (tipoNo *noRef);

int main() {
    auto *arvore = new tipoABB;
    int aux = 0;
    int ALT_ABB = 0;

    inicializar_ABB(arvore);   //Inicializa a arvore

    while (true) {    //Recebe entradas e coloca na arvore até o -1
        cin >> aux;
        if (aux == -1)
            break;
        if (arvore->raiz == NULL) {
            arvore->raiz = criar_No(aux, NULL, NULL);
        }
        else
            inserir_ABB(arvore->raiz, aux);
    }

    cin >> aux;   //recebe mais um numero, e insere na arvore se não estiver, e remover se estiver

    ALT_ABB = altura_ABB(arvore->raiz);   //Calcula altura da ABB se tiver apenas 1 elemento retorna 0

    cout << TAM_ABB << " " << ALT_ABB + 1 << "\n";

    buscar(arvore->raiz, aux);

    cout << TEM << "\n";

    if (TEM) {
        pesquisar_remover(arvore->raiz, aux);
        if (arvore->raiz->numero == -1)
            inicializar_ABB(arvore);
    } else {
        pesquisar_inserir(arvore->raiz, aux);
    }

    ALT_ABB = altura_ABB(arvore->raiz);
    if (TAM_ABB == 1)
        ALT_ABB++;
    cout << TAM_ABB << " " << ALT_ABB + 1 << "\n";

    return 0;
}

void inicializar_ABB (tipoABB *arvore) {
    arvore->raiz = NULL;
}

tipoNo *criar_No (int elemento, tipoNo *esq, tipoNo *dir) {
    auto *aux = new tipoNo;

    aux->numero = elemento;
    aux->esq = esq;
    aux->dir = dir;

    TAM_ABB++;
    return aux;
}

void buscar (tipoNo *noRef, int num) {

    if (noRef == NULL) {
        TEM = false;
        return;
    }
    if (noRef->numero == num) {
        TEM = true;
        return;
    }
    else if (noRef->numero < num)
        buscar(noRef->dir, num);
    else
        buscar(noRef->esq, num);

    return;
}

void pesquisar_inserir (tipoNo *noRef, int num) {

    if (noRef == NULL) {
        noRef = criar_No(num, NULL, NULL);
        return;
    }
    else if (noRef->numero < num) {
        if (noRef->dir != NULL)
            pesquisar_inserir(noRef->dir, num);
        else {
            noRef->dir = criar_No(num, NULL, NULL);
            return;
        }
    } else {
        if (noRef->esq != NULL)
            pesquisar_inserir(noRef->esq, num);
        else {
            noRef->esq = criar_No(num, NULL, NULL);
            return;
        }
    }
}

void pesquisar_remover (tipoNo *noRef, int num) {
    bool removeu = false;

    if (noRef == NULL) {
        return;
    }

    if (noRef->numero == num) {
        removeu = remover_ABB(noRef);
        if (removeu)
            return;
    }

    else if (noRef->numero < num)
        pesquisar_remover(noRef->dir, num);
    else
        pesquisar_remover(noRef->esq, num);

}

void inserir_ABB (tipoNo *noRef, int elemento) {

    if (elemento < noRef->numero) {
        if (noRef->esq != NULL)
            inserir_ABB(noRef->esq, elemento);
        else
            noRef->esq = criar_No(elemento, NULL, NULL);
    }
    else {
        if (noRef->dir != NULL)
            inserir_ABB(noRef->dir, elemento);
        else
            noRef->dir = criar_No(elemento, NULL, NULL);
    }
}

bool remover_ABB (tipoNo *noRef) {

    if (noRef == NULL)
        return false;

    if (noRef->esq == NULL && noRef->dir == NULL) {
        noRef->numero = -1;
        TAM_ABB--;
        return true;
    }
    else if (noRef->esq != NULL && noRef->dir == NULL) {
        buscar_Maior(noRef, noRef->esq);
        return true;
    }
    else {
        buscar_Menor(noRef, noRef->dir);
        return true;
    }
}

void buscar_Menor (tipoNo *noRef, tipoNo *prox) {

    if (prox->esq == NULL) {
        noRef->numero = prox->numero;
        noRef->dir = prox->dir;
        delete prox;
        TAM_ABB--;
    } else
        buscar_Menor(noRef, prox->esq);
}

void buscar_Maior (tipoNo *noRef, tipoNo *prox) {

    if (prox->dir == NULL) {
        noRef->numero = prox->numero;
        noRef->esq = prox->esq;
        delete prox;
        TAM_ABB--;
    } else
        buscar_Maior(noRef, prox->dir);
}



int altura_ABB (tipoNo *noRef) {


    if (noRef == NULL)
        return -1;
    else {
        int SIZE_SAE = altura_ABB(noRef->esq);
        int SIZE_SAD = altura_ABB(noRef->dir);
        if (SIZE_SAE < SIZE_SAD)
            return SIZE_SAD + 1;
        else
            return SIZE_SAE + 1;
    }
}
