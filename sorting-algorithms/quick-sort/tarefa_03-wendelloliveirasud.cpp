#include <iostream>

using namespace std;

//Protótipos das Funções
void quickSort(struct Pessoa* pessoas, int inicio, int fim);
int particao(struct Pessoa* pessoas, int inicio, int fim);
void swap(struct Pessoa* pessoas, int i, int j);
int verificaEstavel(struct Pessoa* pessoas, string str1, string str2, int N);

//Estrutura utilizada para salvar as info de cada indivíduo
struct Pessoa
{
	string nome;
	int idade;
};

int main() {
	Pessoa* pessoas = new Pessoa[105000];
	Pessoa* ajuda = new Pessoa[105000];
	int N, M, P, cont, flag = 0;

	cin >> N;

	for (cont = 0; cont < N; cont++) {  //Recebe as Entradas
		cin >> pessoas[cont].nome;
		cin >> pessoas[cont].idade; 

		ajuda[cont].idade = pessoas[cont].idade;
		ajuda[cont].nome = pessoas[cont].nome;
	}

	cin >> P >> M;

	quickSort(pessoas, 0, N - 1);   //Chamada da ordenação pelo método Quick-Sort

	for (cont = 0; cont < N - 1; cont++) {
		if (ajuda[cont].idade == ajuda[cont + 1].idade) {
			flag += verificaEstavel(pessoas, ajuda[cont].nome, ajuda[cont + 1].nome, N);
		}
	}

	if (flag == 0) {
		cout << "yes" << "\n";
	}
	else
	{
		cout << "no" << "\n";
	}

	for (cont = P - 1; cont < M + P - 1; cont++) {
		cout << pessoas[cont].nome << " ";
		cout << pessoas[cont].idade << "\n";
	}

	delete[] pessoas;
	return 0;
}

void quickSort(struct Pessoa* pessoas, int inicio, int fim) {  //Quick-Sort recebe o vetor de estrutura com os dados, o indice do inicio e do fim.
	int pivo;
	if (inicio < fim) {
		pivo = particao(pessoas, inicio, fim);  //Pivo é aproximadamente o elemento médio que serve como referência para os demais.
		quickSort(pessoas, inicio, pivo - 1);   //Chamada recursiva um.
		quickSort(pessoas, pivo + 1, fim);      //Chamada recursiva dois.
	}

	return;
}

int particao(struct Pessoa* pessoas, int inicio, int fim) {

	//Define qual é o Pivo e ordena os elementos menores iguais do que o pivo a esquerda e os maiores a direita

	int a, b, c, i, meio, medianadeTres = 0, cont, pivo;

	meio = (inicio + fim) / 2;

	a = pessoas[inicio].idade;
	b = pessoas[meio].idade;
	c = pessoas[fim].idade;


	if (a < b)
	{
		if (b < c)
		{
			medianadeTres = meio;
		}
		else
		{
			if (a < c)
			{
				medianadeTres = fim;
			}
			else
			{
				medianadeTres = inicio;
			}
		}
	}
	else
	{
		if (c < b)
		{
			medianadeTres = meio;
		}
		else
		{
			if (c < a)
			{
				medianadeTres = fim;
			}
			else
			{
				medianadeTres = inicio;
			}
		}
	}

	swap(pessoas, medianadeTres, fim);

	pivo = pessoas[fim].idade;
	i = inicio - 1;
	for (cont = inicio; cont <= fim - 1; cont++) {
		if (pessoas[cont].idade <= pivo) {
			i = i + 1;
			swap(pessoas, i, cont);
		}
	}

	swap(pessoas, i + 1, fim);

	return (i + 1);
}

void swap(struct Pessoa* pessoas, int i, int j) {
	Pessoa aux;

	aux.idade = pessoas[i].idade;
	aux.nome = pessoas[i].nome;
	pessoas[i].idade = pessoas[j].idade;
	pessoas[i].nome = pessoas[j].nome;
	pessoas[j].idade = aux.idade;
	pessoas[j].nome = aux.nome;

	return;
}

int verificaEstavel(struct Pessoa* pessoas, string str1, string str2, int N) {
	int cont, flag = 0;

	for (cont = 0; cont < N - 1; cont++) {
		if (pessoas[cont].nome == str1 && flag == 0) {
			return 0;
		}
		if (pessoas[cont].nome == str2)
			flag++;
	}
	return 1;
}