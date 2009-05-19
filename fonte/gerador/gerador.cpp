/*
 * =====================================================================================
 *
 *       Filename:  gerador.cpp
 *
 *    Description:  Programa para gerar rotas e encontrar a melhor.
 *
 *        Version:  1.0
 *        Created:  05/11/2009 10:25:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	<cstring>

#include	"../mapa.h"

	int
main ( int argc, char *argv[])
{
	Mapa mapa;
	Salas sala;
	ifstream file;
	string arq_mapa;
	int i;
	Vertice v;

	if(argc != 2){
		cout << "GERADOR Digite o mapa: ";
//		cin >> arq;
		arq_mapa = "quatro.txt";

		argc = 2;
		argv = (char **)malloc(sizeof(char *) * 2);
		for(i = 0; i < 2; i++) {
			argv[i] = (char *)malloc(sizeof(char) * 10);
		}

		strcpy(argv[0], "gerador.cpp");
		strcpy(argv[1], arq_mapa.c_str());

		main(argc, argv);
		return EXIT_SUCCESS;
	} else {
		arq_mapa = argv[1];
	}

	v = mapa.carregarMapa(arq_mapa, &sala);
	cout << "GERADOR systam call=";
	float x = system("../../avaliador_loop quatro.txt") / 256;
	cout << x << endl;

	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
