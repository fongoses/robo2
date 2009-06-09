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

/* Insere somente um agente na posição inicial */
//	agente_atual = *(new Agente(v.first));

/* Insere um agente para cada sala */
	for(i = 0; (unsigned int)i < salas.size(); i++)
	{
		agente_atual = *(new Agente(salas[i]));
		candidatos.push_back(agente_atual);
	}

//	imprimir_agentes(candidatos);

	melhor.set_avaliacao(INT_MAX);
	while(!candidatos.empty())
	{
		agente_atual = candidatos.front();
//		cout << "ATUAL ";
//		agente_atual.imprimir();
		candidatos.pop_front();
		for(i = 0; (unsigned int)i < salas.size(); i++) /*Criando candidatos a partir do agente atual */
		{
			if(salas[i] != agente_atual.get_vertice())
			{
				novo_agente = agente_atual;
				novo_agente.set_vertice(salas[i]);
				novo_agente.adicionarVertice(salas[i]);
//				cout << "NOVO ";
//				novo_agente.imprimir();getchar();
				novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho()));
//				cout << "NOVO ";
//				novo_agente.imprimir();getchar();
//				cout << "MELHOR ";
//				melhor.imprimir();
				
				
				if	(((novo_agente.get_avaliacao() < 0) && (-novo_agente.get_avaliacao()/2 <= melhor.get_avaliacao())) 
						|| ((novo_agente.get_avaliacao() > 0) && (novo_agente.get_avaliacao()/2 <= melhor.get_avaliacao()) && (novo_agente > melhor)))
				{
					candidatos.push_back(novo_agente);			/* Adiciona o agente na lista de candidator */
//					cout << "ADICIONADO!\n";getchar();
				} else if (novo_agente == melhor)
				{
//					cout	<< "IGUAL!\n";getchar();
					melhores.push_back(novo_agente);
				} else if ((novo_agente.get_avaliacao() > 0 ) && (novo_agente < melhor))
				{
//					cout << "MELHOR!" << endl;getchar();
					melhor = novo_agente;		/* E atualiza a avaliacao atual */
					while(!melhores.empty())
					{
						candidatos.push_back(melhores.front());
						melhores.pop_front();
					}
//					melhores.clear();
					melhores.push_back(novo_agente);
				} else 
				{
					novo_agente.imprimir();
					cout << "DESCARTADO!" << endl;getchar();
				}

			}

		}
		cout << "Candidatos:" << endl;
		imprimir_agentes(candidatos);
		cout << endl << "Melhores:" << endl;
		imprimir_agentes(melhores);
		cout << "Avaliação: " << melhor.get_avaliacao() << endl;
		getchar();
	}
	return melhores;
}		/* -----  end of function gerar  ----- */

	void
imprimir_agentes(list<Agente> candidatos)
{
	list<Agente>::iterator it;
	Caminho caminho;
	unsigned int i;
	
	cout << "Tamanho: " << candidatos.size() << endl;
	for(it = candidatos.begin(); it != candidatos.end(); it++)
	{
		caminho = it->get_caminho();
		cout << "(";
		for(i = 0; i < caminho.size(); i++)
		{
			if(i > 0) cout << " ";
			cout << caminho[i];
		}
		cout << ") ";
	}
	
	cout << endl;
}		/* -----  end of function imprimir_agentes  ----- */
