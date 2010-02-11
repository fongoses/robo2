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


#define	TOTAL	3*60			/* Tempo de execucao total(m) */
#define SIMULACAO true
//#define SIMULACAO true

//	void
//Sleep (int segundos)
//{
//	if(!SIMULACAO)
//		sleep(segundos);
//}

	int
main ( int argc, char *argv[] )
{
	Mapa mapa;
	Robo *robo1;
	Salas sala;
	Vertice v;
	time_t tempo, inicio, anterior, t_aux;
	int visitar_sala, U, algoritmo;
	map<int, unsigned int> chances; /* PENSAR NUM NOME MELHOR */
	VetorSalas v_salas;
	unsigned int i, aux;
	ofstream arq;

	system("clear");
	v = mapa.carregarMapa("/home/heitor/robo2/mapas/ap.txt", &sala);
	robo1 = new Robo(v, mapa, &sala, SIMULACAO);

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

	v_salas = sala.get_salas();

	srand(time(NULL));

	/* Gerando aleatoriamente a chances de um chamado de emergência V2*/
	for(i = 0; i < v_salas.size(); i++)
	{
		chances[v_salas[i]] = 0;
	}

	for(i = 0; i < 100; i++)
	{
		aux = rand() % v_salas.size();
		chances[v_salas[aux]]++;
//		//DEBUG*/cout << "sala: " << v_salas[aux] << " %: " << chances[v_salas[aux]] << endl;getchar();
	}

	for(i = 0; i < v_salas.size(); i++)
	{
		cout << "sala: " << v_salas[i] << " %: " << chances[v_salas[i]] << endl;
	}

	algoritmo = 1;

	switch(algoritmo) {
		/*-----------------------------------------------------------------------------
		 * Algoritmo 1: Estrategia greedy, vai para a sala com maior grau de urgencia
		 *-----------------------------------------------------------------------------*/
		case 1: {
//			cout << "Algoritmo 1\n"; getchar();
			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
				sala.atualizar(tempo);
				visitar_sala = sala.get_maiorU();
//				sala.imprimir();
				//DEBUG*/cout << "PRINCIPAL#main: Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl;getchar();
				t_aux = tempo;
				robo1->irPara(sala.get_vertice(visitar_sala));
				while(!robo1->chegou())
				{
					tempo += robo1->get_tempo_viagem();
					if(t_aux < tempo - 10)
					{
						//Chance pra emergencia
						cout << "ER!!\n";
						t_aux = tempo;
					}
				}
//				cout << "Diferenca: " << tempo - inicio << endl;getchar();
				while( tempo - anterior > ATUALIZACAO) {
					anterior += ATUALIZACAO;
					U = sala.atualizar(anterior);
//					cout << U; getchar();
					arq << anterior - inicio << "\t" << U << endl;
				}
//				if(!SIMULACAO)
//					sleep(VISITAR_SALA);
//				else
//					tempo += VISITAR_SALA;
//				sala.visitar(visitar_sala);

				tempo += robo1->visitar_sala();
				//DEBUG*/cout << "PRINCIPAL:main\n";
				sala.imprimir();
				//DEBUG*/getchar();
//				tempo += VISITAR_SALA;
//				sala.imprimir();
//				cout << "Tempo total: " << tempo - inicio << endl;
			}
		};break;
//		/*-----------------------------------------------------------------------------
//		 * Algoritmo 2: Estrategia greedy, vai para a sala com maior grau de urgencia
//		 *							visitando as salas adjacentes (um vertice de distancia) ao caminho
//		 *-----------------------------------------------------------------------------*/
//		case 2: {
//			ListaVertices caminho, adjacentes;
//			ListaVertices::iterator it_c, it_a;
//			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
//				visitar_sala = sala.get_maiorU();
////				cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl; 
//				caminho = mapa.dijkstra(robo1->get_vertice(), visitar_sala);
//				caminho.pop_front(); /* Removendo o vertice atual do caminho */
//				for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
//					adjacentes = mapa.verticesAdjacentes(robo1->get_vertice()); /* Verifica se existe salas adjacentes ao vertice atual */
//					for(it_a = adjacentes.begin(); it_a != adjacentes.end(); it_a++) { 
//						if(sala.existeSala(*it_a)) {
////							cout << "Visitando sala adjacente " << *it_a << endl;
//							robo1->irPara(*it_a); /* Visita todas as salas adjacentes ao vertice atual */
//							sala.visitar(*it_a);
//						}
//					}
//					robo1->irPara(*it_c);
//				}
//				while( tempo - anterior > ATUALIZACAO) {
//					anterior += ATUALIZACAO;
//					U = sala.atualizar(anterior);
//					arq << anterior - inicio << "\t" << U << endl;
//				}
//				sala.visitar(visitar_sala);
//				tempo += VISITAR_SALA;
////				sala.imprimir();
////				cout << "Tempo total: " << tempo - inicio << endl;
//			}
//		};break;
//		/*-----------------------------------------------------------------------------
//		 * Algoritmo 3: Segue um caminho pre definido
//		 *-----------------------------------------------------------------------------*/
//		case 3: {
//			ListaVertices loop;
//			ListaVertices::iterator it_l;
//			int sala_loop;
//			ifstream arq_loop;
//			time_t tempo_ER = tempo, t_simu;
//
//			arq_loop.open("gerador/loop.txt");
////			arq_loop.open(argv[1]);
//
//			arq_loop >> sala_loop;
//			while(!arq_loop.eof())
//			{
//				loop.push_back(sala_loop);
//				arq_loop >> sala_loop;
//			}
//
//			it_l = loop.begin();
//
//			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
//				cout << "Faltam " << TOTAL * 60 - (tempo - inicio) << "s\n";
//				visitar_sala = *it_l;
///* MODO BLOQUEANTE */
////				tempo += robo1->irPara(sala.get_vertice(visitar_sala));
///* MODO NAO BLOQUEANTE */
//				robo1->irPara(sala.get_vertice(visitar_sala));
//				while(!robo1->chegou(mapa.get_ponto(sala.get_vertice(visitar_sala))) && t_simu > 0)
//				{
//					if(SIMULACAO)
//					{
//						t_simu--;
//						tempo++;
//					} else {
//						time(&tempo);
//					}
//					/* Gerador aleatorio de emergencia */
//					while( tempo - tempo_ER > 60 ) /* USAR DEFINE */
//					{
//						tempo_ER+=60;
//						for(i = 0; i < v_salas.size(); i++)
//						{
//							aux = rand() % 100;
////							cout << "sala " << v_salas[i] << " " << chances[v_salas[i]] << "% " << aux << "%\n";
//							if(chances[v_salas[i]] >= aux)//rand() % 100)
//							{
//								cout << "Emergencia na sala: " << v_salas[i] << endl;
//								robo1->irPara(sala.get_vertice(v_salas[i]));
//								if(SIMULACAO)
//								{
//									tempo += t_simu;
//								} else {
//									while(!robo1->chegou(mapa.get_ponto(sala.get_vertice(v_salas[i]))));
//									time(&tempo);
//								}
//							}
//						}
//					}
//					robo1->irPara(sala.get_vertice(visitar_sala));
//					if(SIMULACAO)
//					{
//						tempo += t_simu;
//					} else {
//						time(&tempo);
//					}
//				}
//
//				while( tempo - anterior > ATUALIZACAO) {
//					anterior += ATUALIZACAO;
//					U = sala.atualizar(anterior);
//					arq << anterior - inicio << "\t" << U << endl;
//				}
//				sala.atualizar(tempo);
//				sala.visitar(visitar_sala);
////				tempo += VISITAR_SALA;
//				cout << "Visitando sala: " << visitar_sala << endl;
//				Sleep(VISITAR_SALA);
//				if(SIMULACAO)
//				{
//					tempo += VISITAR_SALA;
//				} else {
//					time(&tempo);
//				}
//				if(++it_l == loop.end())
//					it_l = loop.begin();
//
//	
//			}
//		};break;
//
//		/*-----------------------------------------------------------------------------
//		 * Algoritmo 4: Prioridades dinamicas
//		 *-----------------------------------------------------------------------------*/
//		case 4: {
//			time_t tempo_ER;
//
////			getchar();
//			sala.zerar_prioridades();
//			tempo_ER = tempo;
//			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
//
//				do {
//
//					while( tempo - tempo_ER > 60 ) /* USAR DEFINE */
//					{
//						tempo_ER+=60;
//						for(i = 0; i < v_salas.size(); i++)
//						{
//							aux = rand() % 100;
////							cout << "sala " << v_salas[i] << " " << chances[v_salas[i]] << "% " << aux << "%\n";
//							if(chances[v_salas[i]] >= aux)//rand() % 100)
//							{
//								sala.incrementar_prioridade(v_salas[i]);
//							
////								cout << "!!\n";
//							}
//						}
//					}
//
//					tempo++;
//					sala.atualizar(tempo);
//					visitar_sala = sala.get_maiorU();
////					cout << "Tempo total: " << tempo - tempo_ER << endl;
////					sala.imprimir();//getchar();
//
//				}while (visitar_sala == -1);
//
//				sala.imprimir();
//				cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl; //getchar();
///* MODO BLOQUEANTE */
////				tempo += robo1->irPara(sala.get_vertice(visitar_sala));
///* MODO NAO BLOQUEANTE */
//				robo1->irPara(sala.get_vertice(visitar_sala));
//				while(!robo1->chegou(mapa.get_ponto(sala.get_vertice(visitar_sala))))
//				{
//					;
//				}
//				time(&tempo);
//				cout << "Tempo: " << tempo - inicio << endl;
//				while( tempo - anterior > ATUALIZACAO) {
//					anterior += ATUALIZACAO;
//					U = sala.atualizar(anterior);
//					arq << anterior - inicio << "\t" << U << endl;
//				}
//
//				sala.atualizar(tempo);
//				sala.visitar(visitar_sala);
//				cout << "Visitando sala: " << visitar_sala << endl;
//				Sleep(VISITAR_SALA);
////				tempo += VISITAR_SALA;
//			}
//		};break;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
