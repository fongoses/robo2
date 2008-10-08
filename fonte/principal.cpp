/*
 * =====================================================================================
 *
 *       Filename:  principal.cpp
 *
 *    Description:  Rotina principal do projeto de monitoramento de ambientes internos
 *									utilizando robos moveis
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
#include	"robo.h"
#include	"ponto.h"

	int
main ( int argc, char *argv[] )
{
	Mapa mapa;
	Robo *robo1;
	Ponto p;

	p = mapa.carregarMapa("/home/heitor/robo2/mapas/rep.txt");
	robo1 = new Robo(p, mapa, true);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
