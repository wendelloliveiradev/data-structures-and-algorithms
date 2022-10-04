#include <iostream>
#include <vector>

using namespace std;

//Function Prototypes
void concatenateVet(vector<int> &vet_a, vector<int> &vet_b, vector<int> &vet_c, int size_a, int size_b);
void bubbleSort(vector<int> &vet, int size);
void swap(vector<int> &vet, int position_1, int position_2);
void printVectors(vector<int> &vet, int size);

int main() {
    int size_a, size_b, in_aux;
    vector<int> vet_a;
    vector<int> vet_b;
    vector<int> vet_c;
    vet_a.reserve(100);
    vet_b.reserve(100);
    vet_c.reserve(100);

    cin >> size_a;

    if (size_a > 100) 
        return 0;

    for (int i = 0; i < size_a; ++i) {
        cin >> in_aux;
        vet_a.push_back(in_aux);
    }

    cin >> size_b;

    if (size_b > 100) 
        return 0;

    for (int i = 0; i < size_b; ++i) {
        cin >> in_aux;   
        vet_b.push_back(in_aux);
    }

    concatenateVet(vet_a, vet_b, vet_c, size_a, size_b);

    bubbleSort(vet_c, size_a + size_b);

    printVectors(vet_c, size_a + size_b);

    return 0;
}

void concatenateVet(vector<int> &vet_a, vector<int> &vet_b, vector<int> &vet_c, int size_a, int size_b) {
    int aux;

    for (int i = 0; i < size_a; i++)
        vet_c[i] = vet_a[i];

    for (int i = 0; i < size_b; i++)
        vet_c[i+(size_a)] = vet_b[i];

    return;
}

//Place in order the elements in the concatenated vector using the Bubble sort ordenation method.
void bubbleSort(vector<int> &vet, int size) {
    int i, j, key = 0;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++)
            if (vet[j + 1] < vet[j]) 
                swap(vet, j, j + 1);
    }

    return;
}

//swap the elements in the positions one and two respectively.
void swap(vector<int> &vet, int position_1, int position_2) {
    int aux;

    aux = vet[position_1];
    vet[position_1] = vet[position_2];
    vet[position_2] = aux;

    return;
}

void printVectors(vector<int> &vet, int size) {
    for (int i = 0; i < size; ++i)
        cout << vet[i] << " ";
    
    cout << endl;

    return;
}