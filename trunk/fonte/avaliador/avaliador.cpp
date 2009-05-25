/*
 * =====================================================================================
 *
 *       Filename:  avaliador.cpp
 *
 *    Description:  Programa para avaliar o desempenho das estratégias
 *
 *        Version:  1.0
 *        Created:  05/05/2009 02:41:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	"avaliador.h"

	int
avaliar (	string arq_mapa, vector<int> caminho)
{
	Robo *robo1;
	Mapa mapa;
	Salas sala;
	int vertice, U, aval_ant, aval, i;
	time_t tempo, anterior;
	Vertice inicial;
	VetorSalas salas;
	map <int, bool> visitou;
	map <int, bool>::iterator it_s;

	inicial = mapa.carregarMapa(arq_mapa, &sala);


	robo1 = new Robo(inicial, mapa, true);

	salas = sala.get_salas();
	for(i = 0; (unsigned int)i < salas.size(); i++)

		visitou[salas[i]] = false;


	/* Iniciacao padrao */
	sala.set_ultima_atualizacao(time(&tempo)-10);
	sala.atualizar(tempo);
	anterior = tempo;


	aval = 0;

	do{
		aval_ant = aval;
		aval = 0;
		for(unsigned int i = 0; i < caminho.size(); i++){
//			cout << "Vertice " << caminho[i] << endl;
			vertice = caminho[i];
			if(visitou[vertice] == false)
				visitou[vertice] = true;
			
			tempo += robo1->irPara(vertice);

//			cout << "tempo " << tempo - anterior << " ATU " << ATUALIZACAO << endl;getchar();
			while( tempo - anterior > ATUALIZACAO) {
				anterior += ATUALIZACAO;
				U = sala.atualizar(anterior);
//  			sala.imprimir();	getchar();
				if(aval < U)
					aval = U;
			}

			U = sala.atualizar(tempo);
//			if(aval < U)
//				aval = U;

//			cout << "Antes: " << U << endl;
//			sala.imprimir();

			sala.visitar(vertice);
//			U = sala.atualizar(tempo);
//			aval = U;

//			cout << "U: " << U << endl; 
//			sala.imprimir();			getchar();
//			tempo += VISITAR_SALA;
		}


	for(it_s = visitou.begin(); it_s != visitou.end(); it_s++)
		if(!it_s->second) {
			printf("A rota não visita todos as salas!\n");
			return 0;
		}



//		cout	<< "AVALIADOR Aval = " << aval << endl; //getchar();
	}while(aval_ant != aval);

//	return EXIT_SUCCESS;
	return aval;
}

