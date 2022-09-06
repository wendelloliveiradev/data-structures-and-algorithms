#include <iostream>

using namespace std;

struct Entity {
    int number;
    struct Entity *prev;
    struct Entity *next;
};

// DCL = Dynamic Chained List
struct Dcl {
    struct Entity *start, *end;
};

// Function Prototypes
void initializeHashTable(Dcl *hashTab, int tamanho);
void insertInHashTable(Dcl *hashTab, int numero, int tamanho);
int hashFunction(int k, int m);
bool searchInHashTable(Dcl *hashTab, int numero, int tamanho);
void removeFromHashTable(Dcl *hashTab, int numero, int tamanho);
void printHashTable(Dcl *hashTab, int tamanho);

int main() {
    int number, size, nums;
    Dcl *hash_table = new Dcl[10000];
    bool is_there_any;

    cin >> size;
    cin >> nums;

    if (size == 0)
        return 0;
    if (nums > size)
        return 0;

    initializeHashTable(hash_table, size);

    for (int i = 0; i < nums; ++i) {
        cin >> number;
        insertInHashTable(hash_table, number, size);
    }

    cin >> number;

    is_there_any = searchInHashTable(hash_table, number, size);

    // In case the element is in the table, remove it, other way insert it
    if (is_there_any)
        removeFromHashTable(hash_table, number, size);
    else
        insertInHashTable(hash_table, number, size);

    printHashTable(hash_table, size);

    delete[] hash_table;

    return 0;
}

void initializeHashTable(Dcl *hash_table, int size) {
    for (int i = 0; i <= size; ++i) {
        hash_table[i].start = NULL;
        hash_table[i].end = NULL;
    }
}

void insertInHashTable(Dcl *hash_table, int number, int size) {
    int position;
    Entity *aux = new Entity;
    aux->number = number;
    aux->prev = NULL;
    aux->next = NULL;

    position = hashFunction(number, size);

    if (hash_table[position].start == NULL) {
        hash_table[position].start = aux;
        hash_table[position].end = aux;
    }
    else {
        aux->prev = hash_table[position].end;
        hash_table[position].end->next = aux;
        hash_table[position].end = aux;
    }
}

int hashFunction(int k, int m) {
    return (k % m);
}

bool searchInHashTable(Dcl *hash_table, int number, int size) {
    int position;
    position = hashFunction(number, size);

    Entity *aux = hash_table[position].start;

    while (aux != NULL) {
        if (aux->number == number)
            return true;
        else
            aux = aux->next;
    }

    return false;
}

void removeFromHashTable(Dcl *hash_table, int number, int size) {
    int position;
    position = hashFunction(number, size);

    Entity *aux = hash_table[position].start;

        while (aux != NULL) {
            if (aux->number == number) {
                if (aux == hash_table[position].start) {
                    hash_table[position].start = aux->next;
                    aux = NULL;
                } else if (aux == hash_table[position].end) {
                    hash_table[position].end = aux->prev;
                    aux = NULL;
                } else {
                    aux->prev->next = aux->next;
                    aux->next->prev = aux->prev;
                    aux = NULL;
                }
            }
            else
                aux = aux->next;
        }
}

void printHashTable(Dcl *hash_table, int size) {
    Entity *aux = hash_table[0].start;

    for (int i = 1; i <= size; ++i) {
        cout << "[" << i - 1 << "]";
        while (aux != NULL) {
            cout << " " << aux->number;
            aux = aux->next;
        }
        cout << endl;
        aux = hash_table[i].start;
    }
}