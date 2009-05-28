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
	Salas salas;
	int vertice, U, aval_ant, aval, i;
	time_t tempo, anterior;
	Vertice inicial;
	VetorSalas vsalas;
	map <int, bool> visitou;
	map <int, bool>::iterator it_s;

	inicial = mapa.carregarMapa(arq_mapa, &salas);


	robo1 = new Robo(inicial, mapa, true);

	vsalas = salas.get_salas();
	for(i = 0; (unsigned int)i < vsalas.size(); i++)

		visitou[vsalas[i]] = false;


	/* Iniciacao padrao */
	salas.set_ultima_atualizacao(time(&tempo)-10);
	salas.atualizar(tempo);
	anterior = tempo;


	aval = 0;

	do{
		aval_ant = aval;
		aval = 0;
		for(unsigned int i = 0; i < caminho.size(); i++){
//			cout << "Vertice " << caminho[i] << endl;
			vertice = caminho[i];
			if(!salas.existeSala(vertice)) {
				cerr << "O vertice " << vertice << " não é uma sala válida!" << endl;
				return 0;
			}

			if(visitou[vertice] == false)
				visitou[vertice] = true;
			
			tempo += robo1->irPara(vertice);

//			cout << "tempo " << tempo - anterior << " ATU " << ATUALIZACAO << endl;getchar();
			while( tempo - anterior > ATUALIZACAO) {
				anterior += ATUALIZACAO;
				U = salas.atualizar(anterior);
//  			salas.imprimir();	getchar();
				if(aval < U)
					aval = U;
			}

			U = salas.atualizar(tempo);
//			if(aval < U)
//				aval = U;

//			cout << "Antes: " << U << endl;
//			salas.imprimir();

			salas.visitar(vertice);
//			U = salas.atualizar(tempo);
//			aval = U;

//			cout << "U: " << U << endl; 
//			salas.imprimir();			getchar();
//			tempo += VISITAR_SALA;
		}


	for(it_s = visitou.begin(); it_s != visitou.end(); it_s++)
		if(!it_s->second) {
			cerr << "A rota não visita todos as salas!" << endl;
			return -aval;
		}



//		cout	<< "AVALIADOR Aval = " << aval << endl; //getchar();
	}while(aval_ant != aval);

//	return EXIT_SUCCESS;
	return aval;
}

