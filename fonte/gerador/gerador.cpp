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
#include	<cstdlib>

#include	"../mapa.h"
#include  "../avaliador/avaliador.h"
#include	"gerador.h"

	list<Agente>
gerar ( string arq_mapa)
{
	Mapa mapa;
	Salas sala;
	ifstream file;
	int i;
	Vertice v;
	list<Agente> candidatos, melhores;
	Agente agente_atual, novo_agente, melhor;
	ListaVertices adjacentes;
	ListaVertices::iterator it_a;
	VetorSalas salas;

	v = mapa.carregarMapa(arq_mapa, &sala);

	salas = sala.get_salas();/*Pegando um vetor com os vertices de todas as salas */
	agente_atual = *(new Agente(v.first));
	candidatos.push_back(agente_atual);

	melhor.set_avaliacao(INT_MAX);
	while(!candidatos.empty())
	{
		agente_atual = candidatos.front();
		cout << "ATUAL ";
		agente_atual.imprimir();getchar();
		candidatos.pop_front();
		for(i = 0; (unsigned int)i < salas.size(); i++) /*Criando candidatos a partir do agente atual */
		{
			if(salas[i] != agente_atual.get_vertice())
			{
				novo_agente = agente_atual;
				novo_agente.set_vertice(salas[i]);
				novo_agente.adicionarVertice(salas[i]);
				novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho()));
				cout << "NOVO ";
				novo_agente.imprimir();
				cout << "MELHOR ";
				melhor.imprimir();getchar();

				if(novo_agente.get_avaliacao() == 0 ) /* Se a avaliacao do agente for 0 significa que não é um caminho valido */
					candidatos.push_back(novo_agente);			/* Adiciona o agente na lista de candidator */
				else if(novo_agente < melhor) /* Se a avaliacao do agente for melhor que a atual */
				{
					candidatos.push_back(novo_agente);			/* Adiciona o agente na lista de candidator */
					melhor = novo_agente;		/* E atualiza a avaliacao atual */
					cout << "Melhor!" << endl;getchar();
				}
			}

		}
		cout << "Candidatos: " << candidatos.size() << endl;getchar();
	}
	
	return melhores;
}		/* -----  end of function gerar  ----- */
