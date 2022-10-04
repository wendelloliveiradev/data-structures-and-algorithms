#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Structs
struct tipoNo {
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
void inserir_ABB (tipoNo *&noRef, int elemento);
int altura_ABB (tipoNo *noRef);
int FB (tipoNo *noRef);
void BalancaNo (tipoNo *noRef);
void LL (tipoNo *noRef);
void LR (tipoNo *noRef);
void RR (tipoNo *noRef);
void RL (tipoNo *noRef);
bool ArvoreAVL (tipoNo *noRef);
void Imprimir(tipoNo *noRef);

string tipoRotacao;   //Variável para salvar o tipo da Rotacao aplicada

int main() {
    tipoABB *arvore = new tipoABB;  //alocação dinâmica da árvore
    string str;
    bool EhAVL, flagSide = true;
    int ALT_ABB, numero = 0, numParent = -3, numElemento = -1;


    inicializar_ABB(arvore);   //Inicializa a arvore

    cin >> str;     //Entrada principal pega a árvore aninhada em uma única STRING

    int i = 0;
    while (i < str.size()) {   //Este loop auxilia na manutenção da ABB conforme a representação aninhada
        if (str[i] == 40 || str[i] == 41)
            numParent++;
        if (str[i] == 'C')
            numElemento++;

        if (numParent == (numElemento * 4))
            break;
        i++;
    }

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 40 || str[i] == 41)  //Quando o numero de parenteses for = 0, muda o lado da subarvore
            numParent--;
        if (numParent == 0)
            flagSide = false;    //Caso 'flagSide' for = true, coloca os elementos na SAE, SAD caso contrario

        char *aux = new char[10000];    //Setando uma string auxiliar com os numeros de cada elemento para converter para inteiro
        if (str[i] == 40 && str[i + 1] == 67) {
            int j = i + 2;
            int k = 0;
            while (str[j] != 40 && str[j] != 41) {
                aux[k] = str[j];
                j++;
                k++;
            }
            aux[k + 1] = '\0';
            stringstream intValue(aux); //Conversão da string para inteiro
            intValue >> numero;

            if (arvore->raiz == NULL)   //Adiciona o primeiro elemento da árvore
                arvore->raiz = criar_No(numero, NULL, NULL);
            else {
                if (flagSide)
                    inserir_ABB(arvore->raiz->esq, numero);
                else
                    inserir_ABB(arvore->raiz->dir, numero);
            }
        }
        delete[] aux;
    }

    EhAVL = ArvoreAVL(arvore->raiz);

    ALT_ABB = altura_ABB(arvore->raiz);     //retorna a altura da árvore a partir de um dado Nó

    cout << ALT_ABB << endl;
    Imprimir(arvore->raiz);
    cout << endl;

    BalancaNo(arvore->raiz);    //Faz o processo de rotação na Raiz e devolve o resultado

    cout << endl;

    delete arvore;
    return 0;
}

void inicializar_ABB (tipoABB *arvore) {
    arvore->raiz = NULL;
}

tipoNo *criar_No (int elemento, tipoNo *esq, tipoNo *dir) {
    tipoNo *aux = new tipoNo;

    aux->chave = elemento;
    aux->esq = esq;
    aux->dir = dir;

    return aux;
}

void inserir_ABB (tipoNo *&noRef, int elemento) {

    if (noRef == NULL) {
        noRef = criar_No(elemento, NULL, NULL);
        return;
    }
    if (elemento < noRef->chave) {
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

int FB (tipoNo *noRef) {
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

void BalancaNo (tipoNo *noRef) {
    int balancaA, balancaB, balancaC;

    balancaA = FB(noRef);
    balancaB = FB(noRef->esq);
    balancaC = FB(noRef->dir);

    if (balancaA < -1) {
        if (balancaC < 0) {
            tipoRotacao = "RR";
            RR(noRef);
        }
        else if (balancaC > 0) {
            tipoRotacao = "RL";
            RL(noRef);
        }
    } else if (balancaA > 1){
        if (balancaB > 0) {
            tipoRotacao = "LL";
            LL(noRef);
        }
        else if (balancaB < 0) {
            tipoRotacao = "LR";
            LR(noRef);
        }
    }
}

void LL (tipoNo *noRef) {
    int ALT_ABB;

    tipoNo *pA = noRef;
    tipoNo *pB = pA->esq;
    pA->esq = pB->dir;
    pB->dir = pA;

    ALT_ABB = altura_ABB(pB);

    cout << tipoRotacao << endl;
    cout << ALT_ABB << endl;
    Imprimir(pB);
}

void LR (tipoNo *noRef) {
    int ALT_ABB;

    tipoNo *pA = noRef;
    tipoNo *pB = pA->esq;
    tipoNo *pC = pB->dir;
    pB->dir = pC->esq;
    pC->esq = pB;
    pA->esq = pC->dir;
    pC->dir = pA;

    ALT_ABB = altura_ABB(pC);

    cout << tipoRotacao << endl;
    cout << ALT_ABB << endl;
    Imprimir(pC);
}

void RR (tipoNo *noRef) {
    int ALT_ABB;

    tipoNo *pA;
    tipoNo *pB;
    pA = noRef;
    pB = pA->dir;
    pA->dir = pB->esq;
    pB->esq = pA;

    ALT_ABB = altura_ABB(pB);

    cout << tipoRotacao << endl;
    cout << ALT_ABB << endl;
    Imprimir(pB);
}

void RL (tipoNo *noRef) {
    int ALT_ABB;

    tipoNo *pA = noRef;
    tipoNo *pB = pA->dir;
    tipoNo *pC = pB->esq;
    pB->esq = pC->dir;
    pC->dir = pB;
    pA->dir = pC->esq;
    pC->esq = pA;

    ALT_ABB = altura_ABB(pC);

    cout << tipoRotacao << endl;
    cout << ALT_ABB << endl;
    Imprimir(pC);
}

bool ArvoreAVL (tipoNo *noRef) {
    int BALANCA;

    BALANCA = FB(noRef);

    if (noRef->esq == NULL && noRef->dir == NULL)
        return true;
    if (BALANCA <= 1)
        return true;

    return false;
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
