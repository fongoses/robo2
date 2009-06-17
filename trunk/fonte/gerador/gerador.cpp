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
	time_t tempo, tempo_ant, inicio;

	v = mapa.carregarMapa(arq_mapa, &sala);

	salas = sala.get_salas();/*Pegando um vetor com os vertices de todas as salas */

/* Insere somente um agente na posição inicial */

	time(&tempo);
	inicio = tempo_ant = tempo;
/* Insere um agente para cada sala */
	for(i = 0; (unsigned int)i < salas.size(); i++)
	{
		agente_atual = *(new Agente(salas[i]));
		candidatos.push_back(agente_atual);
		if(i == 0)
			melhor = *(new Agente(salas[i]));
		else
			melhor.adicionarVertice(salas[i]);
	}
	melhor.adicionarVertice(salas[0]);
	melhor.set_avaliacao(avaliar(arq_mapa, melhor.get_caminho()));
	melhores.push_back(melhor);

//	melhor.set_avaliacao(INT_MAX);
	while(!candidatos.empty())
	{
		agente_atual = candidatos.front();
		candidatos.pop_front();
		for(i = 0; (unsigned int)i < salas.size(); i++) /*Criando candidatos a partir do agente atual */
		{
			if(salas[i] != agente_atual.get_vertice())
			{
				novo_agente = agente_atual;
				novo_agente.set_vertice(salas[i]);
				novo_agente.adicionarVertice(salas[i]);
				novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho()));
	
					novo_agente.imprimir();//getchar();
				if	((novo_agente.get_avaliacao() < 0) && (-novo_agente.get_avaliacao() <= melhor.get_avaliacao())) 
				{
					candidatos.push_back(novo_agente);			/* Adiciona o agente na lista de candidator */
//					candidatos.push_front(novo_agente);			/* Adiciona o agente na lista de candidator */
				} else if (novo_agente == melhor)
				{
					melhores.push_back(novo_agente);
				} else if ((novo_agente.get_avaliacao() > 0 ) && (novo_agente < melhor))
				{
					melhor = novo_agente;		/* E atualiza a avaliacao atual */
					while(!melhores.empty()) /* Readiciona os antigos melhores como candidatos */
					{
						candidatos.push_back(melhores.front());
//						candidatos.push_front(melhores.front());
						melhores.pop_front();
					}
					melhores.push_back(novo_agente);
				} else 
				{
//					novo_agente.imprimir();
				}
			}
		}
	
		if(1)
		{
//			system("clear");
			cout << "Candidatos:" << endl;
			imprimir_agentes(candidatos);
			cout << endl << "Melhores:" << endl;
			imprimir_agentes(melhores);
			cout << "Avaliação: " << melhor.get_avaliacao() << endl;
			getchar();
		}

		time(&tempo);
		if(tempo - tempo_ant >= 1)
		{
			system("clear");
			cout << "Candidatos:" << endl;
			imprimir_agentes(candidatos);
			cout << endl << "Melhores:" << endl;
			imprimir_agentes(melhores);
			cout << "Avaliação: " << melhor.get_avaliacao() << endl;
			cout << "Tempo: " << tempo - inicio << endl;
			tempo_ant = tempo;
		}
	}
	return melhores;
}		/* -----  end of function gerar  ----- */

	void
imprimir_agentes(list<Agente> candidatos)
{
	list<Agente>::iterator it;
	Caminho caminho;
	unsigned int i, max = 0;
	
	cout << "Tamanho: " << candidatos.size() << " MAX: " << candidatos.max_size()<< endl;
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
		max++;
		if(max > 100) break;
	}
	
	cout << endl;
}		/* -----  end of function imprimir_agentes  ----- */
