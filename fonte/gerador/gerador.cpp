/*
 * =====================================================================================
 *
 *       Filename:  gerador.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/25/2009 06:37:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	"../mapa.h"
#include  "../avaliador/avaliador.cpp"
#include	"gerador.h"

	list<Agente>
gerar(string arq_mapa)
{
	Mapa mapa;
	Salas sala;
	ifstream file;
	int i;
	Vertice v;
	list<Agente> candidatos, melhores;
	Agente agente_atual, novo_agente;
	ListaVertices adjacentes;
	ListaVertices::iterator it_a;
	VetorSalas salas;

	v = mapa.carregarMapa(arq_mapa, &sala);

	salas = sala.get_salas();/*Pegando um vetor com os vertices de todas as salas */
	agente_atual = *(new Agente(v.first));
	candidatos.push_back(agente_atual);

	while(!candidatos.empty())
	{
		agente_atual = candidatos.front();
		candidatos.pop_front();
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
	}
	
	return melhores;
}

