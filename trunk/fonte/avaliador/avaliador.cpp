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
	int vertice, U, aval_ant, aval, retornar;
	bool sair=false;
	unsigned int i;
	time_t tempo, anterior;
	Vertice inicial;
	VetorSalas vsalas;
	map <int, bool> visitou;
	map <int, bool>::iterator it_s;

	inicial = mapa.carregarMapa(arq_mapa, &salas);


	robo1 = new Robo(inicial, mapa, true);

	/* Cria um controle para verificar se todas as salas foram visitadas */
	vsalas = salas.get_salas();
	for(i = 0; i < vsalas.size(); i++)

		visitou[vsalas[i]] = false;


	/* Iniciacao padrao */
	salas.set_ultima_atualizacao(time(&tempo));
	salas.atualizar(tempo);
	anterior = tempo;

//	cout << "AVALIADOR\nAvaliando caminho: ";
//	for(unsigned int i = 0; i < caminho.size(); i++){
//		cout << caminho[i] << " ";
//	}
//	cout << endl;
	aval = 0;
	
	salas_atual.set_salas(salas.get_salas_completo());
	do{
		aval_ant = aval;
		salas_ant.set_salas(salas_atual.get_salas_completo());


		aval = 0;

		/* Simulando a navegação do robô no mapa */
		for(i = 0; i < caminho.size(); i++){
			vertice = caminho[i];
			if(!salas.existeSala(vertice)) {
				return 0;
			}

			if(visitou[vertice] == false) //Inutil?
				visitou[vertice] = true;
			
			tempo += robo1->irPara(vertice);

			cout << "AVAL# TEMPO DE VISITA DA SALA!!!!!\n";

			U = salas.atualizar(tempo);
			if(aval < U)
				aval = U;

			salas_atual.set_salas(salas.get_salas_completo());
			salas.visitar(vertice);
		}
		/* Fim da simulação */

		/* Verificando se o robô visitou todas as salas do mapa */
		for(it_s = visitou.begin(); it_s != visitou.end(); it_s++)
		{
			if(!it_s->second) {
				if(aval == 0) return -1; /* Se não visitou alguma sala e 'aval' = 0, significa que só existia 1 vértice */
				else return -aval; /* Se não visitou alguma sala, retorna o valor calculado da avaliação em negativo */
			}
		}

		/* Verificando se o caminho passado é um loop, ou seja, se começa e termina no mesmo vértice */
		if(caminho[0] != caminho[caminho.size()-1])
		{
			if(aval == 0) return -1;
			else return -aval;
		}

		
		if(aval > limite)
			return 0;

	}while(salas_ant != salas_atual);

	return aval;
}

