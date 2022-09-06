#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Function Prototypes
void heapSort(vector<int> &heap_vector, vector<int> &output_vector);
void buildMaxHeap(vector<int> &heap_vector);
int extractMaxHeap(vector<int> &heap_vector);
void maxHeapfy(struct vector<int> &vetHeap, int position);
void swapHeapElements(vector<int> &heap_vector, int position, int parent);
void printHeap(vector<int> &output_vector);
void printOutput(vector<int> &output_vector);

int main() {
    int N, aux;
    vector<int> heap_vector;
    vector<int> output_vector;

    heap_vector.reserve(10000);
    output_vector.reserve(10000); 

    cin >> N;

    heap_vector.push_back(0);

    for (int i = 1; i <= N; i++) {
        cin >> aux;
        heap_vector.push_back(aux);
    }

    heapSort(heap_vector, output_vector);

    reverse(output_vector.begin(), output_vector.end());

    output_vector.erase(output_vector.begin());

    printOutput(output_vector);

    heap_vector.clear();
    output_vector.clear();

    return 0;
}

//place in order the elements in the output_vector.
void heapSort(vector<int> &heap_vector, vector<int> &output_vector) {
    buildMaxHeap(heap_vector);
    printHeap(heap_vector);

    int size = heap_vector.size();

    while (size > 0) {
        output_vector.push_back(extractMaxHeap(heap_vector));
        size--;
    }
}

//run from the middle to the begin of the ordered vector applying maxHeapfy.
void buildMaxHeap(vector<int> &heap_vector) {
    for (int count = heap_vector.size() / 2; count > 0; count--)
        maxHeapfy(heap_vector, count);
}

//get the biggest element of heap_vector, which is the element in the position 1.
int extractMaxHeap(vector<int> &heap_vector) {
    int biggest, last;

    if (heap_vector.size() < 1)
        return -1;

    biggest = heap_vector[1];
    last = heap_vector.size();
    heap_vector[1] = heap_vector[last];
    
    heap_vector.erase(heap_vector.cbegin());

    maxHeapfy(heap_vector, 1);

    return last;
}

//identifies which one is the parent and his kids
void maxHeapfy(struct vector<int> &vetHeap, int position) {
    int left, right, parent;

    left = 2 * position;
    right = (2 * position) + 1;

    if (left <= vetHeap.size() && vetHeap[left] > vetHeap[position])
        parent = left;
    else
        parent = position;

    if (right <= vetHeap.size() && vetHeap[right] > vetHeap[parent])
        parent = right;

    if (parent != position) {
        swapHeapElements(vetHeap, position, parent);
        maxHeapfy(vetHeap, parent);
    }

    return;
}

void swapHeapElements(vector<int> &heap_vector, int position, int parent) {
    int aux;

    aux = heap_vector[position];
    heap_vector[position] = heap_vector[parent];
    heap_vector[parent] = aux;

    return;
}

void printHeap(vector<int> &output_vector) {
    for (int i = 1; i < output_vector.size(); i++)
        cout << output_vector[i] << " ";

    cout << endl;

    return;
}

void printOutput(vector<int> &output_vector) {
    for (int i = 0; i < output_vector.size(); i++)
        cout << output_vector[i] << " ";

    cout << endl;

    return;
}