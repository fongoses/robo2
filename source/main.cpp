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

#include	"matriz_esparsa.h"

	int
main ( int argc, char *argv[] )
{
	MatrizEsparsa M;

	M.adicionarCelulaDupla(1, 1, 1);
	M.adicionarCelulaDupla(5, 5, 5);
	M.adicionarCelulaDupla(5, 1, 51);
	M.adicionarCelulaDupla(2, 2, 2);
	M.adicionarCelulaDupla(9, 9, 9);
	M.imprimir();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
