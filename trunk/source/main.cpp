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

#include	"mapa.h"
#include	"ponto.h"

	int
main ( int argc, char *argv[] )
{
	Mapa M;

	M.adicionarVertice(1, *(new Ponto(1, 1)));
	M.adicionarVertice(1, *(new Ponto(1, 2)));
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
