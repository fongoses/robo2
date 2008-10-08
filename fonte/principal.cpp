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
	Salas sala;
	Vertice v;
	time_t tempo, inicio;
	int visitar_sala;

	v = mapa.carregarMapa("/home/heitor/robo2/mapas/rep.txt", &sala);
	robo1 = new Robo(v, mapa, true);

	mapa.imprimir();
	sala.set_ultima_atualizacao(time(&tempo)-1);
	sala.atualizar(tempo);
	inicio = tempo;
	sala.imprimir();

	while(tempo - inicio < 30 * 60) { /* rodar por 30 minutos */
		visitar_sala = sala.get_maiorU();
		cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl; 
		tempo += robo1->irPara(sala.get_vertice(visitar_sala));
//		cout	<< "Demorou no total " << tempo << "s.\n";
		sala.atualizar(tempo);
		sala.visitar(visitar_sala);
		sala.imprimir();
		cout << "Tempo total: " << tempo - inicio << endl;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
