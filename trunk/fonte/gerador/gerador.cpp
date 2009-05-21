/*
 * =====================================================================================
 *
 *       Filename:  gerador.cpp
 *
 *    Description:  Programa para gerar rotas e encontrar a melhor.
 *
 *        Version:  1.0
 *        Created:  05/11/2009 10:25:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	<cstring>

#include	"../mapa.h"

typedef struct _agente {
	int vertice;
	vector<int> rota;
	int aval;
} Agente;

	int
main ( int argc, char *argv[])
{
	Mapa mapa;
	Salas sala;
	ifstream file;
	string arq_mapa;
	int i;
	Vertice v;
	list<Agente> candidatos;
	Agente agente_atual, novo_agente
	ListaVertices adjacentes;
	ListaVertices::iterator it_a;
	VetorSalas salas;


	if(argc != 2){
		cout << "GERADOR Digite o mapa: ";
//		cin >> arq;
		arq_mapa = "quatro.txt";

		argc = 2;
		argv = (char **)malloc(sizeof(char *) * 2);
		for(i = 0; i < 2; i++) {
			argv[i] = (char *)malloc(sizeof(char) * 10);
		}

		strcpy(argv[0], "gerador.cpp");
		strcpy(argv[1], arq_mapa.c_str());

		main(argc, argv);
		return EXIT_SUCCESS;
	} else {
		arq_mapa = argv[1];
	}

	v = mapa.carregarMapa(arq_mapa, &sala);

	salas = sala.get_salas();/*Pegando um vetor com os vertices de todas as salas */
	agente_atual.vertice = v.first; /*Cria um agente no vertice inicial*/
	agente_atual.rota.push_back(agente_atual.vertice);
	agente_atual.aval = 0;
	candidatos.push_back(agente_atual);

	while(!candidatos.empty())
	{
		agente_atual = candidatos.pop_front();
		for(i = 0; (unsigned int)i < salas.size(); i++) /*Criando candidatos a partir do agente atual */
		{
			if(salas[i] != agente_atual.vertice)
			{
				novo_agente = agente_atual;
				novo_agente.vertice = salas[i];
				novo_agente.rota.push_back(salas[i]);
				novo_agente.aval = /*Chamar o avaliador*/

		}
	}









	cout << "GERADOR systam call=";
	float x = system("../../avaliador_loop quatro.txt") / 256;
	cout << x << endl;

	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
