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
avaliar (	string arq_mapa, vector<int> caminho, int limite)
{
	Robo *robo1;
	Mapa mapa;
	Salas salas, salas_ant, salas_atual;
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
	salas.set_ultima_atualizacao(time(&tempo));
	salas.atualizar(tempo);
	anterior = tempo;


	aval = 0;
	
	salas_atual.set_salas(salas.get_salas_completo());
	do{
		aval_ant = aval;
		salas_ant.set_salas(salas_atual.get_salas_completo());


		aval = 0;
		for(unsigned int i = 0; i < caminho.size(); i++){
			vertice = caminho[i];
			if(!salas.existeSala(vertice)) {
				return 0;
			}

			if(visitou[vertice] == false)
				visitou[vertice] = true;
			
			tempo += robo1->irPara(vertice);

			U = salas.atualizar(tempo);
			if(aval < U)
				aval = U;

			salas_atual.set_salas(salas.get_salas_completo());
			salas.visitar(vertice);
		}

		for(it_s = visitou.begin(); it_s != visitou.end(); it_s++)
		{
			if(!it_s->second) {
				if(aval == 0) return -1;
				else return -aval;
			}
		}

		if(caminho[0] != caminho[caminho.size()-1])
			if(aval == 0) return -1;
			else return -aval;

		
		if(aval > limite)
			return 0;

	}while(salas_ant != salas_atual);

	return aval;
}

