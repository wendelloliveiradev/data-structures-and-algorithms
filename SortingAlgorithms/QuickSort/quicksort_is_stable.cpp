#include <iostream>

using namespace std;

//Function Prototypes
void quickSort(struct Person* people, int start, int end);
int partition(struct Person* people, int start, int end);
void swap(struct Person* people, int i, int j);
int verifyStability(struct Person* people, string str1, string str2, int N);

struct Person {
	string name;
	int age;
};

int main() {
	Person* people = new Person[105000];
	Person* aux_people = new Person[105000];
	int N, M, P, i, is_stable = 0;
	
	cin >> N;

	for (i = 0; i < N; i++) {
		cin >> people[i].name;
		cin >> people[i].age; 

		aux_people[i] = people[i];
	}

	cin >> P >> M;

	quickSort(people, 0, N - 1);

	for (i = 0; i < N - 1; i++)
		if (aux_people[i].age == aux_people[i + 1].age)
			is_stable += verifyStability(people, aux_people[i].name, aux_people[i + 1].name, N);

	if (is_stable == 0)
		cout << "yes" << "\n";
	else
		cout << "no" << "\n";

	for (i = P - 1; i < M + P - 1; i++) {
		cout << people[i].name << " ";
		cout << people[i].age << "\n";
	}

	delete[] people;
	delete[] aux_people;
	return 0;
}

void quickSort(struct Person* people, int start, int end) {
	//pivot is about the middle element in the people struct
	int pivot;

	if (start < end) {
		pivot = partition(people, start, end);
		quickSort(people, start, pivot - 1);
		quickSort(people, pivot + 1, end);
	}

	return;
}

int partition(struct Person* people, int start, int end) {
	//Defines which is the pivot, and sort the element
	//smaller than pivot to the left
	//bigger than pivot to the right

	int a, b, c, i, middle, three_median = 0, pivot;

	middle = (start + end) / 2;

	a = people[start].age;
	b = people[middle].age;
	c = people[end].age;

	if (a < b) {
		if (b < c)
			three_median = middle;
		else {
			if (a < c)
				three_median = end;
			else
				three_median = start;
		}
	}
	else {
		if (c < b)
			three_median = middle;
		else {
			if (c < a)
				three_median = end;
			else
				three_median = start;
		}
	}

	swap(people, three_median, end);

	pivot = people[end].age;
	i = start - 1;
	
	for (int j = start; j < end; j++)
		if (people[j].age <= pivot) {
			i = i + 1;
			swap(people, i, j);
		}

	swap(people, i + 1, end);

	return (i + 1);
}

void swap(struct Person* people, int i, int j) {
	Person aux;

	aux = people[i];
	people[i] = people[j];
	people[j] = aux;
}

int verifyStability(struct Person* people, string str1, string str2, int N) {
	int i, is_stable = 0;

	for (i = 0; i < N - 1; i++) {
		if (people[i].name == str1 && is_stable == 0) 
			return 0;

		if (people[i].name == str2)
			is_stable++;
	}

	return 1;
}