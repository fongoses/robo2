/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  só pra ter main
 *
 *        Version:  1.0
 *        Created:  10/03/2008 01:38:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#include	<cstdio>
#include	<iostream>

using namespace std;

#include	"mapa.h"
#include	"ponto.h"

	int
main ( int argc, char *argv[] )
{
	Mapa M;


	M.adicionarVertice(1, *(new Ponto(1, 2)));
	M.adicionarVertice(2, *(new Ponto(2, 2)));
	M.adicionarVertice(3, *(new Ponto(3, 2)));
	M.adicionarVertice(4, *(new Ponto(4, 2)));
	M.adicionarVertice(5, *(new Ponto(5, 2)));
	M.adicionarVertice(6, *(new Ponto(6, 2)));



	M.adicionarAresta(1, 2);
	M.adicionarAresta(1, 3);
	M.adicionarAresta(1, 5);
	M.adicionarAresta(2, 4);
	M.adicionarAresta(2, 5);
	M.adicionarAresta(3, 4);

	if(M.adjacente(1, 2)) cout << "1 adjacente ao 2.\n";
	else cout << "1 não adjacente ao 2.\n";
	if(M.adjacente(1, 4)) cout << "1 adjacente ao 4.\n";
	else cout << "1 não adjacente ao 4.\n";

	M.imprimir();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
