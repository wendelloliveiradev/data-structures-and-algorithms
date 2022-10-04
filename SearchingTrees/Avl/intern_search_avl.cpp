#include <iostream>

using namespace std;

//Structs
struct tipoNo {
    int fb;
    int chave;
    struct tipoNo *esq;
    struct tipoNo *dir;
};

struct tipoABB {
    tipoNo *raiz;
};

//Protótipos das Funções
void inicializar_ABB (tipoABB *arvore);
tipoNo *criar_No (int elemento, tipoNo *esq, tipoNo *dir);
void fbPorNo (tipoNo *&noRef);
void buscar (tipoNo *noRef, int elemento);
void inserir_ABB (tipoNo *&noRef, int elemento);
void buscar_inserir (tipoNo *&noRef, int elemento);
void buscar_remover (tipoNo *&noRef, int elemento);
void remover_AVL (tipoNo *&noRef);
void buscar_Menor (tipoNo *&noRef, tipoNo *&prox);
void buscar_Maior (tipoNo *&noRef, tipoNo *&prox);
int altura_ABB (tipoNo *noRef);
int FB (tipoNo *noRef);
void checaBalanceamento (tipoNo *&noRef);
void BalancaNo (tipoNo *&noRef);
void Imprimir(tipoNo *noRef);

bool TEM = false;

int main() {
    tipoABB *arvore = new tipoABB;  //alocação dinâmica da árvore
    int num, elemento;

    inicializar_ABB(arvore);   //Inicializa a arvore

    cin >> num; //Pega o número de elementos a serem inseridos na AVL

    for (int i = 0; i < num; ++i) {  //Insere elementos na AVL
        cin >> elemento;

        if (arvore->raiz == NULL)
            arvore->raiz = criar_No(elemento, NULL, NULL);
        else
            inserir_ABB(arvore->raiz, elemento);
    }

    num = 0;
    cin >> num;  //Pega número a ser inserido ou removido da AVL

    TEM = false;
    buscar(arvore->raiz, num);  //Checa se o número já está na AVL

    if (TEM) {  //Se sim, Remove e refatora os FB's
        buscar_remover(arvore->raiz, num);
        fbPorNo(arvore->raiz);
        checaBalanceamento(arvore->raiz);
    }
    else {  //Se não, Insere e refatora os FB's
        buscar_inserir(arvore->raiz, num);
        fbPorNo(arvore->raiz);
        checaBalanceamento(arvore->raiz);
    }

    Imprimir(arvore->raiz); //Imprime o resultado final

    delete arvore;
    return 0;
}

void inicializar_ABB (tipoABB *arvore) {
    arvore->raiz = NULL;
}

tipoNo *criar_No (int elemento, tipoNo *esq, tipoNo *dir) {
    tipoNo *aux = new tipoNo;

    aux->fb = 0;
    aux->chave = elemento;
    aux->esq = esq;
    aux->dir = dir;

    return aux;
}

void fbPorNo (tipoNo *&noRef) {

    if (noRef == NULL)
        return;
    else {
        noRef->fb = FB(noRef);  //FB é dado pela Altura da SubArvore Esquerda - Altura da SubArvore Direita
        fbPorNo(noRef->esq);
        fbPorNo(noRef->dir);
    }
}

void buscar (tipoNo *noRef, int elemento) {

    if (noRef == NULL) {
        TEM = false;
        return;
    }
    if (noRef->chave == elemento) {  //Caso elemento esteja na AVL a variável global 'TEM' recebe 'true'
        TEM = true;
        return;
    }
    else if (noRef->chave < elemento)
        buscar(noRef->dir, elemento);
    else
        buscar(noRef->esq, elemento);

}

void inserir_ABB (tipoNo *&noRef, int elemento) {

    if (noRef == NULL)
        noRef = criar_No(elemento, NULL, NULL);

    if (elemento < noRef->chave) {

        if (noRef->esq != NULL)
            inserir_ABB(noRef->esq, elemento);
        else
            noRef->esq = criar_No(elemento, NULL, NULL);
    }
    else if (elemento > noRef->chave) {

        if (noRef->dir != NULL)
            inserir_ABB(noRef->dir, elemento);
        else
            noRef->dir = criar_No(elemento, NULL, NULL);
    }

    noRef->fb = FB(noRef);
    checaBalanceamento(noRef);
}

void buscar_inserir (tipoNo *&noRef, int elemento) {

    if (noRef == NULL)
        noRef = criar_No(elemento, NULL, NULL);

    else if (noRef->chave < elemento) {
        if (noRef->dir != NULL)
            buscar_inserir(noRef->dir, elemento);
        else
            noRef->dir = criar_No(elemento, NULL, NULL);
    } else {
        if (noRef->esq != NULL)
            buscar_inserir(noRef->esq, elemento);
        else
            noRef->esq = criar_No(elemento, NULL, NULL);
    }

    noRef->fb = FB(noRef);
    checaBalanceamento(noRef);
}

void buscar_remover (tipoNo *&noRef, int elemento) {

    if (noRef == NULL)
        return;

    if (noRef->chave == elemento) {
        remover_AVL(noRef);
        if (noRef != NULL) {
            noRef->fb = FB(noRef);
            checaBalanceamento(noRef);
        }
        return;
    }
    else if (noRef->chave < elemento)
        buscar_remover(noRef->dir, elemento);
    else
        buscar_remover(noRef->esq, elemento);

    noRef->fb = FB(noRef);
    checaBalanceamento(noRef);
}

void remover_AVL (tipoNo *&noRef) {

    if (noRef == NULL)
        return;

    if (noRef->esq == NULL && noRef->dir == NULL) {
        noRef = noRef->esq;
        delete noRef;
        return;
    }
    else if (noRef->esq != NULL && noRef->dir == NULL) {
        buscar_Maior(noRef, noRef->esq);
        return;
    }
    else {
        buscar_Menor(noRef, noRef->dir);
        return;
    }
}

void buscar_Menor (tipoNo *&noRef, tipoNo *&prox) {  //Busca o menor valor da SubArvore Direita

    if (prox->esq == NULL) {
        noRef->chave = prox->chave;
        prox = prox->dir;
    } else
        buscar_Menor(noRef, prox->esq);
}

void buscar_Maior (tipoNo *&noRef, tipoNo *&prox) {  //Busca o maior valor da SubArvore Esquerda

    if (prox->dir == NULL) {
        noRef->chave = prox->chave;
        prox = prox->esq;
    } else
        buscar_Maior(noRef, prox->dir);
}

int altura_ABB (tipoNo *noRef) {  //Retorna a Altura de um determinado Nó

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

int FB (tipoNo *noRef) {  //Retorna o Fator de Balanceamento de um dado Nó
    int ALT_SAE = 0;
    int ALT_SAD = 0;
    int FATOR;

    if (noRef == NULL)
        return 0;

    ALT_SAE = altura_ABB(noRef->esq);
    ALT_SAD = altura_ABB(noRef->dir);

    FATOR = ALT_SAE - ALT_SAD;

    return FATOR;
}
void checaBalanceamento (tipoNo *&noRef) {

    if (noRef == NULL)
        return;
    else if (noRef->fb > 1 || noRef->fb < -1) {  //Se a AVL precisa ser balanceada chama BalancaNo e refatora os FB's
        BalancaNo(noRef);
        fbPorNo(noRef);
    }

    //Percorrimento recursivo da AVL
    checaBalanceamento(noRef->esq);
    checaBalanceamento(noRef->dir);
}

void BalancaNo (tipoNo *&noRef) {   //Aplica a rotaçao adequada, onde necessario


    if (noRef->fb < -1) {
        if (noRef->dir->fb < 0) {  //Rotação do tipo RR (rotaçao simples a esquerda)
            tipoNo *pA = noRef;
            tipoNo *pB = pA->dir;
            pA->dir = pB->esq;
            pB->esq = pA;
            noRef = pB;
        }
        else if (noRef->dir->fb > 0) {   //Rotação do tipo RL (rotaçao dupla a esquerda)
            tipoNo *pA = noRef;
            tipoNo *pB = pA->dir;
            tipoNo *pC = pB->esq;
            pB->esq = pC->dir;
            pC->dir = pB;
            pA->dir = pC->esq;
            pC->esq = pA;
            noRef = pC;
        }
    } else if (noRef->fb > 1){
        if (noRef->esq->fb > 0) {   //Rotação do tipo LL (rotaçao simples a direita)
            tipoNo *pA = noRef;
            tipoNo *pB = pA->esq;
            pA->esq = pB->dir;
            pB->dir = pA;
            noRef = pB;
        }
        else if (noRef->esq->fb < 0) {   //Rotação do tipo LR (rotaçao dupla a direita)
            tipoNo *pA = noRef;
            tipoNo *pB = pA->esq;
            tipoNo *pC = pB->dir;
            pB->dir = pC->esq;
            pC->esq = pB;
            pA->esq = pC->dir;
            pC->dir = pA;
            noRef = pC;
        }
    }
}

void Imprimir(tipoNo *noRef)
{
    if (noRef != NULL) {
        cout << "(C" << noRef->chave;
        Imprimir(noRef->esq);
        Imprimir(noRef->dir);
        cout << ")";
    }
    else
        cout << "()";
}
