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
#include	<fstream>

using namespace std;

#include	"mapa.h"
#include	"robo.h"
#include	"ponto.h"


#define	ATUALIZACAO 10			/* Tempo de atualizacao(s) */
#define	TOTAL	3*60			/* Tempo de execucao total(m) */
#define	VISITAR_SALA 5			/* Tempo para visitar uma sala (s) */

	int
main ( int argc, char *argv[] )
{
	Mapa mapa;
	Robo *robo1;
	Salas sala;
	Vertice v;
	time_t tempo, inicio, anterior;
	int visitar_sala, U, algoritmo;
	ofstream arq;

	v = mapa.carregarMapa("/home/heitor/robo2/mapas/rep.txt", &sala);
	robo1 = new Robo(v, mapa, true);

	/* Iniciacao padrao */
	sala.set_ultima_atualizacao(time(&tempo)-1);
	sala.atualizar(tempo);
	inicio = tempo;
	sala.imprimir();
	arq.open("/home/heitor/robo2/curva.txt", ifstream::trunc);
	if(!arq.is_open()) {
		cout << "Problemar para abrir curva.txt.\n";getchar();
	}
	anterior = tempo;/* Usado para simulacao */
	/* Fim da iniciacao padrão */

	algoritmo = 1;

	switch(algoritmo) {
		/*-----------------------------------------------------------------------------
		 * Algoritmo 1: Estrategia greedy, vai para a sala com maior grau de urgencia
		 *-----------------------------------------------------------------------------*/
		case 1: {
//			cout << "Algoritmo 1\n"; getchar();
			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
				visitar_sala = sala.get_maiorU();
//				sala.imprimir();
//				cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl;getchar();
				tempo += robo1->irPara(sala.get_vertice(visitar_sala));
//				cout << "Diferenca: " << tempo - anterior << endl;getchar();
				while( tempo - anterior > ATUALIZACAO) {
					anterior += ATUALIZACAO;
					U = sala.atualizar(anterior);
//					cout << U; getchar();
					arq << anterior - inicio << "\t" << U << endl;
				}
				sala.atualizar(tempo);
				sala.visitar(visitar_sala);
//				sala.imprimir();getchar();
				tempo += VISITAR_SALA;
//				sala.imprimir();
//				cout << "Tempo total: " << tempo - inicio << endl;
			}
		};break;
		/*-----------------------------------------------------------------------------
		 * Algoritmo 2: Estrategia greedy, vai para a sala com maior grau de urgencia
		 *							visitando as salas adjacentes (um vertice de distancia) ao caminho
		 *-----------------------------------------------------------------------------*/
		case 2: {
			ListaVertices caminho, adjacentes;
			ListaVertices::iterator it_c, it_a;
			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
				visitar_sala = sala.get_maiorU();
//				cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl; 
				caminho = mapa.dijkstra(robo1->get_vertice(), visitar_sala);
				caminho.pop_front(); /* Removendo o vertice atual do caminho */
				for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
					adjacentes = mapa.verticesAdjacentes(robo1->get_vertice()); /* Verifica se existe salas adjacentes ao vertice atual */
					for(it_a = adjacentes.begin(); it_a != adjacentes.end(); it_a++) { 
						if(sala.existeSala(*it_a)) {
//							cout << "Visitando sala adjacente " << *it_a << endl;
							tempo += robo1->irPara(*it_a); /* Visita todas as salas adjacentes ao vertice atual */
							sala.visitar(*it_a);
						}
					}
					tempo += robo1->irPara(*it_c);
				}
				while( tempo - anterior > ATUALIZACAO) {
					anterior += ATUALIZACAO;
					U = sala.atualizar(anterior);
					arq << anterior - inicio << "\t" << U << endl;
				}
				sala.visitar(visitar_sala);
				tempo += VISITAR_SALA;
//				sala.imprimir();
//				cout << "Tempo total: " << tempo - inicio << endl;
			}
		};break;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
