#include <iostream>
#include <iomanip>

using namespace std;

//Protótiopos das funções
void inicializaVet(struct Candidatos* vet, int tam);
int Contagem(struct Candidatos* candidatos, struct Eleitor* Eleitores, int numCand, int numElei);
int checaEmpate(struct Candidatos* candidatos, int maisVotado, int segundoVotado);
int segundoTurno(struct Eleitor* vetEleitores, struct Candidatos* candidatos, int maisVotado, int segundoVotado, int V);

//structs utilizadas
struct Eleitor {
	int voto_um = 0, voto_dois = 0, voto_tres = 0;
};

struct Candidatos
{
	int candidato;
	int numVotos;
};

int main() {
	Eleitor* vetEleitores = new Eleitor[10000];
	Candidatos* candidatos = new Candidatos[100];
	int V, C, cont, votosValidos, maisVotado, segundoVotado = 1, candEleito = 0, invalido = 0;
	float resultado;

	cin >> V >> C;

	inicializaVet(candidatos, C);

	//Entrada recebe os 3 votos de cada eleitor (1 <= V <= 10000)
	for (cont = 1; cont <= V; cont++) {
			cin >> vetEleitores[cont].voto_um;
			cin >> vetEleitores[cont].voto_dois;
			cin >> vetEleitores[cont].voto_tres;
	}

	//Apura o resultado do primeiro turno e retorna os votos válidos
	votosValidos = Contagem(candidatos, vetEleitores, C, V);

	//Busca pelos candidatos, mais votado e o segundo mais votado.
	maisVotado = candidatos[1].candidato;
	for (cont = 2; cont <= C; cont++) {
		if (candidatos[cont].numVotos > candidatos[maisVotado].numVotos) {
			maisVotado = candidatos[cont].candidato;
		}
	}
	if (candidatos[1].candidato == candidatos[maisVotado].candidato) {
		segundoVotado = candidatos[2].candidato;
	}
	else
	{
		segundoVotado = candidatos[1].candidato;
	}
	for (cont = 1; cont <= C; cont++) {
		if (candidatos[cont].numVotos > candidatos[segundoVotado].numVotos) {
			if (candidatos[cont].candidato != candidatos[maisVotado].candidato) {
				segundoVotado = candidatos[cont].candidato;
			}
		}
	}

	//Checa se houve empate e retorna o candidato eleito de acordo com o criterio de desempate.
	candEleito = checaEmpate(candidatos, maisVotado, segundoVotado);

	//Calcula a porcentagem de votos válidos em relação ao primeiro turno
	resultado = (float)candidatos[candEleito].numVotos / votosValidos;
	resultado *= 100;
	cout << fixed << setprecision(2);

	if (resultado >= 50.00)  //Se resultado for de 50% ou mais, candidato foi eleito em primeiro turno
	{
		cout << candidatos[candEleito].candidato << " ";
		cout << resultado << endl;
		return(0);
	}
	else if (!votosValidos)  //Caso não haja votos válidos no primeiro turno, retorna 0;
	{
		cout << votosValidos << endl;
		return(0);

	}
	else
	{	//Segundo Turno, faz a recontagem considerando apenas os mais votados no primeiro turno
		cout << candidatos[candEleito].candidato << " ";
		cout << resultado << endl;

		invalido = segundoTurno(vetEleitores, candidatos, maisVotado, segundoVotado, V);

		if (candidatos[maisVotado].numVotos > candidatos[segundoVotado].numVotos) {
			resultado = (float)candidatos[maisVotado].numVotos / (V - invalido);
			resultado *= 100;
			cout << candidatos[maisVotado].candidato << " ";
			cout << resultado << endl;
		}
		else if (candidatos[maisVotado].numVotos < candidatos[segundoVotado].numVotos)
		{
			resultado = (float)candidatos[segundoVotado].numVotos / (V - invalido);
			resultado *= 100;
			cout << candidatos[segundoVotado].candidato << " ";
			cout << resultado << endl;

		}
		else
		{	//Checa se houve empate no segundo turno.
			candEleito = checaEmpate(candidatos, maisVotado, segundoVotado);

			resultado = (float)candidatos[candEleito].numVotos / (V - invalido);
			resultado *= 100;
			cout << candidatos[candEleito].candidato << " ";
			cout << resultado << endl;
		}
	}


	delete[] vetEleitores;
	delete[] candidatos;

	return 0;
}

void inicializaVet(struct Candidatos* vet, int tam) {
	int cont;

	vet[0].numVotos = 0;
	vet[0].candidato = 0;

	for (cont = 1; cont <= tam; cont++) {
		vet[cont].candidato = cont;
		vet[cont].numVotos = 0;
	}

	return;
}

int Contagem(struct Candidatos* candidatos, struct Eleitor* Eleitores, int numCand, int numElei) {
	int cont, votosValidos = 0;

	for (cont = 1; cont <= numElei; cont++) {
		if (Eleitores[cont].voto_um < 1 || Eleitores[cont].voto_um > numCand) {
			continue;
		}
		else
		{
			candidatos[Eleitores[cont].voto_um].numVotos++;
			votosValidos++;
		}
	}

	return votosValidos;
}

int checaEmpate(struct Candidatos* candidatos, int maisVotado, int segundoVotado) {
	int candEleito;

	if (candidatos[maisVotado].numVotos == candidatos[segundoVotado].numVotos) {
		if (candidatos[maisVotado].candidato < candidatos[segundoVotado].candidato) {
			candEleito = maisVotado;
		}
		else
		{
			candEleito = segundoVotado;
		}
	}
	else
	{
		candEleito = maisVotado;
	}

	return candEleito;
}

int segundoTurno(struct Eleitor* vetEleitores, struct Candidatos* candidatos, int maisVotado, int segundoVotado, int V) {
	int cont, invalido = 0;
	for (cont = 1; cont <= V; cont++) {
		if (vetEleitores[cont].voto_um == candidatos[maisVotado].candidato || vetEleitores[cont].voto_um == candidatos[segundoVotado].candidato) {
			continue;
		}
		else if (vetEleitores[cont].voto_dois == candidatos[maisVotado].candidato || vetEleitores[cont].voto_dois == candidatos[segundoVotado].candidato)
		{
			candidatos[vetEleitores[cont].voto_dois].numVotos++;
		}
		else if (vetEleitores[cont].voto_tres == candidatos[maisVotado].candidato || vetEleitores[cont].voto_tres == candidatos[segundoVotado].candidato) {
			candidatos[vetEleitores[cont].voto_tres].numVotos++;
		}
		else
		{
			invalido++;
		}
	}

	return invalido;
}