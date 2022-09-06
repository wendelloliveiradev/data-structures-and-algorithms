#include <iostream>
#include <string>
#include <vector>

#define SIZE 1000

using namespace std;

//Function Prototypes
void getInputStr(vector<string> &str_matrix);
void countDiamonds(vector<string> &str_matrix, vector<int> &output, int& N);
void printNumDiamonds(vector<int> &output);

int main() {
    int N;
    vector<int> output;
    vector<string> str_matrix;
    output.reserve(SIZE);
    str_matrix.reserve(SIZE);

    cin >> N;

    for (int i = 0; i < N; ++i)
        getInputStr(str_matrix);

    countDiamonds(str_matrix, output, N);

    printNumDiamonds(output);

    return 0;
}

void getInputStr(vector<string> &str_matrix) {
    string aux;
    cin >> aux;
    str_matrix.push_back(aux);
}

void countDiamonds(vector<string> &str_matrix, vector<int> &output, int& N) {
    for (int i = 0; i < N; i++) {
        // lts = less than sign, gts = greater than sign 
        int lts = 0, gts = 0, j = 0;

        while (str_matrix[i][j] != '\0') {
            if  (str_matrix[i][j] == '<')
                lts++;
            else if (str_matrix[i][j] == '>') {
                if (lts > 0) {
                    lts--;
                    gts++;
                }
            }

            j++;
        }

        output.push_back(gts);
    }
}

void printNumDiamonds(vector<int> &output) {
    for (auto itr : output)
        cout << itr << endl;
}