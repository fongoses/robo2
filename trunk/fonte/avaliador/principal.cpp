/*
 * =====================================================================================
 *
 *       Filename:  aval_principal.cpp
 *
 *    Description:  Programa para avaliar o desempenho das estratégias
 *
 *        Version:  1.0
 *        Created:  05/25/2009 03:23:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	"avaliador.h"

	int
main ( int argc, char *argv[] )
{
	string arq_mapa, arq_rota;
	int i, aval, vertice;
	ListaVertices rota;
	vector<int> caminho;
	ifstream file;

	if(argc != 3){
		cout << "AVALIADOR Digite o mapa: ";
//		cin >> arq;
		arq_mapa = "quatro.txt";
		cout << "AVALIADOR Digite a tragetoria: ";
//		cin >> arq;
		arq_rota = "rota.txt";

		argc = 3;
		argv = (char **)malloc(sizeof(char *) * 3);
		for(i = 0; i < 3; i++) {
			argv[i] = (char *)malloc(sizeof(char) * 10);
		}

		strcpy(argv[0], "avaliador.cpp");
		strcpy(argv[1], arq_mapa.c_str());
		strcpy(argv[2], arq_rota.c_str());

		aval = main(argc, argv);
		cout << "AVALIADOR Aval: " << aval << endl;
		return aval;
	} else {
		arq_mapa = argv[1];
		arq_rota = argv[2];
	}



	if(arq_rota == "rota.txt") {
		cout	<< "AVALIADOR Digite a rota: \n";
		cin >> vertice;
		while (vertice != -1){
			rota.push_back(vertice);
			cin >> vertice;
		}
	} else {
		file.open(arq_rota.c_str());
		cout << "AVALIADOR Carregando rota... ";
		if(file.is_open()) {
			file >> vertice;
			while(!file.eof()) {
				rota.push_back(vertice);
				file >> vertice;
			}
		}
	}
	cout << endl;
	while(!rota.empty()) { /* Passando o caminho de ListaVertices (list) para vector */
//		cout << rota.front() << " ";
		caminho.push_back(rota.front());
		rota.pop_front();
	}
//	cout << endl;

	return avaliar(arq_mapa, caminho);
}				/* ----------  end of function main  ---------- */
