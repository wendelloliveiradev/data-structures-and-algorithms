#include <iostream>
#include <string>

#define MAX_SIZE 100000

using namespace std;

//Function Prototypes
void strTolower(struct Names *names_vector, int size);
void RadixSort(struct Names *names_vector, struct Names *output_vector, int number_names);
void CountingSort(struct Names *names_vector, struct Names *output_vector, int number_names, int char_position);
void printRadix(int *names_vector, int size);
void printNames(struct Names *names_vector, int start, int end);

//Struct
struct Names {
    int size = 0;
    string name;
};

int main() {
    int N, P, M;
    Names *names_vector = new Names[MAX_SIZE];
    Names *output_vector = new Names[MAX_SIZE];

    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> names_vector[i].name;
        names_vector[i].size = names_vector[i].name.size();
    }

    strTolower(names_vector, N);

    cin >> P >> M;

    RadixSort(names_vector, output_vector, N);

    printNames(output_vector, P - 1, M);

    delete[] output_vector;
    delete[] names_vector;

    return 0;
}

void strTolower (struct Names *names_vector, int size) {
    //change characters from uppercase to lowercase
    //using ascii integers values
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < names_vector[i].size; ++j)
            if (names_vector[i].name[j] >= 65 && names_vector[i].name[j] <= 90)
                names_vector[i].name[j] += 32;
}

void RadixSort (struct Names *names_vector, struct Names *output_vector, int number_names) {
    int digitos;

    //Finds the string with the biggest number of chars
    digitos = names_vector[0].size;
    for (int i = 1; i < number_names; ++i)
        if (names_vector[i].size > digitos) 
            digitos = names_vector[i].size;

    //based on the string with the biggest number of chars runs couting-sort in the column of number i
    for (int i = digitos - 1; i >= 0; i--)
        CountingSort(names_vector, output_vector, number_names, i);
}

void CountingSort (struct Names *names_vector, struct Names *output_vector, int number_names, int char_position) {
    int *auxiliar_vector = new int[27];
    int maior = 26, aux;

    for (int i = 0; i <= maior; i++)
        auxiliar_vector[i] = 0;

    for (int i = 0; i < number_names; i++) {
        //casting char to int and subtracting 96
        //we get the position in which it should be placed
        //to sort the strings.
        aux = ((int) names_vector[i].name[char_position]) - 96;

        if (names_vector[i].size > char_position && aux > 0)
            auxiliar_vector[aux]++;
        else
            auxiliar_vector[0]++;
    }

    for (int i = 1; i <= maior; i++)
        auxiliar_vector[i] += auxiliar_vector[i - 1];

    printRadix(auxiliar_vector, maior);

    for (int i = number_names - 1; i >= 0; i--) {
        aux = ((int) names_vector[i].name[char_position]) - 96;

        if (names_vector[i].size > char_position && aux > 0) {
            output_vector[auxiliar_vector[aux] - 1] = names_vector[i];
            auxiliar_vector[aux]--;
        } else {
            output_vector[auxiliar_vector[0] - 1] = names_vector[i];
            auxiliar_vector[0]--;
        }
    }

    for (int i = 0; i < number_names; ++i)
        names_vector[i] = output_vector[i];

    delete[] auxiliar_vector;
}

void printRadix (int *names_vector, int size) {
    for (int i = 0; i <= size; ++i)
        cout << names_vector[i] << " ";

    cout << endl;
}

void printNames (struct Names *names_vector, int start, int end) {
    for (int i = start; i < (end + start); ++i)
        cout << names_vector[i].name << endl;
}