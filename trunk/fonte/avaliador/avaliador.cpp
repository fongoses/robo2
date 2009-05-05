/*
 * =====================================================================================
 *
 *       Filename:  avaliador.cpp
 *
 *    Description:  Programa para avaliar o desempenho das estratégias
 *
 *        Version:  1.0
 *        Created:  05/05/2009 02:41:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	"../mapa.h"

	int
main ( int argc, char *argv[] )
{
	Mapa mapa;
	Salas sala;
	Vertice v;
	int vertice;
	string arq;
	ListaVertices rota;
	ifstream file;

	if(argc != 2){
		cout << "Digite o mapa: ";
//		cin >> arq;
		arq = "tres.txt";
		v = mapa.carregarMapa(arq, &sala);
		cout << "Digite a tragetoria: ";
//		cin >> arq;
		arq = "rota.txt";
		file.open(arq.c_str());
		cout << "Carregando rota..." << endl;
		if(file.is_open()) {
			file >> vertice;
			while(!file.eof()) {
				cout << vertice << " ";
				rota.push_back(vertice);
				file >> vertice;
			}
		}
	} else {
		v = mapa.carregarMapa(argv[1], &sala);
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
