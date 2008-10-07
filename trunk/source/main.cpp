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
	ListaVertices caminho;
	ListaVertices::iterator it_c;



	M.adicionarVertice(1, *(new Ponto(0, 1)));
	M.adicionarVertice(2, *(new Ponto(1, 2)));
	M.adicionarVertice(3, *(new Ponto(1, 0)));
	M.adicionarVertice(4, *(new Ponto(2, 2)));
	M.adicionarVertice(5, *(new Ponto(2, 0)));
	M.adicionarVertice(6, *(new Ponto(3, 1)));



	M.adicionarAresta(1, 2);
	M.adicionarAresta(1, 3);
	M.adicionarAresta(1, 5);
	M.adicionarAresta(1, 6);
	M.adicionarAresta(2, 4);
	M.adicionarAresta(3, 4);
	M.adicionarAresta(4, 6);
	M.adicionarAresta(5, 6);

	M.imprimir();

	caminho = M.dijkstra(1, 6);
	cout << "Caminho: ";
	for(it_c = caminho.begin(); it_c != caminho.end(); it_c++)
		cout << *it_c << " ";
	cout << endl;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
