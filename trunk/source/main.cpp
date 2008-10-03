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

	M.adicionarCelula(1, 1, 1);
	M.adicionarCelula(5, 5, 5);
	M.adicionarCelula(2, 2, 2);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
