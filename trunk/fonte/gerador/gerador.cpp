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
#include	<fstream>

#include	"../mapa.h"
#include  "../avaliador/avaliador.h"
#include	"gerador.h"

	list<Agente>
gerar ( string arq_mapa)
{
	Mapa mapa;
	Salas sala;
	ifstream file;
	unsigned int i;
	Vertice v;
	list<Agente> candidatos, melhores;
	Agente agente_atual, novo_agente;//, melhor;
	ListaVertices adjacentes;
	ListaVertices::iterator it_a;
	VetorSalas salas;
	time_t tempo, tempo_ant, inicio;

    list<int> arquivos;
    char arq_nome[50];
    ofstream arq_o;
    ifstream arq_i;
    Agente a_aux;
    Caminho cam;
    int arq_sala, arq_cam;

	unsigned int debug_salas = 0, debug_candidatos, total_aval = 0, total_descartados = 0;

	v = mapa.carregarMapa(arq_mapa, &sala);

	salas = sala.get_salas();/*Pegando um vetor com os vertices de todas as salas */

	time(&tempo);
	inicio = tempo_ant = tempo;
/* Insere um agente para cada sala */
	for(i = 0; i < salas.size(); i++)
	{
		agente_atual = *(new Agente(salas[i]));
		candidatos.push_back(agente_atual);
		if(i == 0)
			novo_agente = *(new Agente(salas[i]));
		else
			novo_agente.adicionarVertice(salas[i]);
	}
	novo_agente.adicionarVertice(salas[0]);
	novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho()));
	total_aval += salas.size();
	melhores.push_back(novo_agente);
		if(0)
		{
			system("clear");
			cout << "Candidatos:" << endl;
			imprimir_agentes(candidatos);
			cout << endl << "Melhores:" << endl;
			imprimir_agentes(melhores);
			cout << "Avaliação: " << melhores.front().get_avaliacao() << endl;
			getchar();
		}
	while(!candidatos.empty())
	{
		{
			agente_atual = candidatos.front();
			candidatos.pop_front();
			total_descartados++;
//			agente_atual.imprimir();
//			getchar();
		}

		for(i = 0; i < salas.size(); i++) /*Criando candidatos a partir do agente atual */
		{
			if(salas[i] != agente_atual.get_vertice())
			{
				novo_agente = agente_atual;
				novo_agente.set_vertice(salas[i]);
				novo_agente.adicionarVertice(salas[i]);
				novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho(), melhores.front().get_avaliacao()));
				total_aval++;

//			cout<<"GERADOR\n;novo_agente.imprimir();//getchar();

				{
				if	((novo_agente.get_avaliacao() < 0) && (-novo_agente.get_avaliacao() <= melhores.front().get_avaliacao()))
				{
					candidatos.push_back(novo_agente);			/* Adiciona o agente na lista de candidatos */
//					candidatos.push_front(novo_agente);			/* Adiciona o agente na lista de candidatos */
				} else if (novo_agente == melhores.front())
				{
					melhores.push_back(novo_agente);
				} else if ((novo_agente.get_avaliacao() > 0 ) && (novo_agente < melhores.front()))
				{
//					melhor = novo_agente;		/* E atualiza a avaliacao atual */
//					while(!melhores.empty()) /* Readiciona os antigos melhores como candidatos */
//					{
//						candidatos.push_back(melhores.front());
//						candidatos.push_front(melhores.front());
//						melhores.pop_front();
//					}
                    total_descartados+= melhores.size();
					melhores.clear();
					melhores.push_back(novo_agente);
				} else
				{
				    total_descartados++;
//					novo_agente.imprimir();
				}
				}
			}
		}

		debug_candidatos = candidatos.size();
		if(candidatos.size() > CAND_MAX + CAND_MIN)
		while(candidatos.size() > CAND_POR_ARQ)
		{
            if(arquivos.size() > 0)
                arquivos.push_back(arquivos.back() + 1);
            else
                arquivos.push_back(0);
		    sprintf(arq_nome, "cand%i.txt", arquivos.back());
            arq_o.open(arq_nome, fstream::trunc);

            for(int ci = 0; ci < CAND_POR_ARQ; ci++)
            {
                a_aux = candidatos.back();
                candidatos.pop_back();
//                arq_o << a_aux.get_vertice() << endl;
                cam = a_aux.get_caminho();
                for(unsigned int cci = 0; cci < cam.size(); cci++)
                {
                    if(cci > 0) arq_o << " ";
                    arq_o << cam[cci];
                }
                arq_o << " " << a_aux.get_avaliacao() << endl;
                debug_candidatos = candidatos.size();
            }
            arq_o.close();
        }
        if(candidatos.empty() && !arquivos.empty())
        {
		    sprintf(arq_nome, "cand%i.txt", arquivos.front());

		    arq_i.open(arq_nome, fstream::in);

            for(int ci = 0; ci < CAND_POR_ARQ; ci++)
            {
                novo_agente = *(new Agente());
//                arq_i >> arq_sala;

                arq_i >> arq_cam;
                do {
                    novo_agente.adicionarVertice(arq_cam);
                    arq_sala = arq_cam;
                    arq_i >> arq_cam;
                }while (arq_cam >= 0);
                novo_agente.set_vertice(arq_sala);
				novo_agente.set_avaliacao(arq_cam);
//				novo_agente.set_avaliacao(avaliar(arq_mapa, novo_agente.get_caminho(), melhores.front().get_avaliacao()));


				if(novo_agente.get_avaliacao()*-1 < melhores.front().get_avaliacao())
                    candidatos.push_back(novo_agente);
                else total_descartados++;
            }
            sprintf(arq_nome, "rm cand%i.txt", arquivos.front());
            arquivos.pop_front();
            system(arq_nome);
            arq_i.close();
        }
		if(0)
		{
//			if((debug_candidatos + 1000 <= candidatos.size())) /*|| (debug_salas >= 9)*/// || (debug_salas != candidatos.front().get_tamanho()))
			{
			system("clear");
			cout << "Candidatos:" << endl;
			imprimir_agentes(candidatos);
			cout << "Avaliação: " << candidatos.front().get_avaliacao() << endl;
			cout << endl << "Melhores:" << endl;
			imprimir_agentes(melhores);
			cout << "Avaliação: " << melhores.front().get_avaliacao() << endl;
//			}
//			if(/*(candidatos.front().get_tamanho() >= 9)) || */(debug_salas != candidatos.front().get_tamanho()))
//			{
                getchar();
			}
		}

		time(&tempo);
		if((tempo - tempo_ant >= 10) ||0)
		{
			system("clear");
			cout << "Candidatos: " << arquivos.size() * CAND_POR_ARQ + candidatos.size() << " Avaliados: " << total_aval  << " Descartados: " << total_descartados << "(" << total_aval - total_descartados - candidatos.size() - arquivos.size() * CAND_POR_ARQ<< ")" << endl;
			imprimir_agentes(candidatos);
			cout << "Avaliação: " << candidatos.front().get_avaliacao() << endl;
			cout << endl << "Melhores:" << endl;
			imprimir_agentes(melhores);
			cout << "Avaliação: " << melhores.front().get_avaliacao() << endl;
			cout << "Tempo: " << tempo - inicio << endl;
			tempo_ant = tempo;
//			getchar();
		}
	}
	system("rm cand*.txt");
	return melhores;
}		/* -----  end of function gerar  ----- */

	void
imprimir_agentes(list<Agente> agentes)
{
	list<Agente>::iterator it;
	Caminho caminho;
	unsigned int i, max = 0;

	cout << "Tamanho: " << agentes.size() << " MAX: " << agentes.max_size()<< endl;
	cout << "Salas: " << agentes.front().get_tamanho();
	for(it = agentes.begin(); it != agentes.end(); it++)
	{
		caminho = it->get_caminho();
		cout << endl << "(";
		for(i = 0; i < caminho.size(); i++)
		{
			if(i > 0) cout << " ";
			cout << caminho[i];
		}
		cout << ") ";
		max++;
		if(max > 5) break;
	}

	cout << endl;
}		/* -----  end of function imprimir_agentes  ----- */

	void
salvar_loop(char arquivo[], list<Agente> agentes)
{
	ofstream arq;
	Caminho caminho;
	unsigned int i;

	arq.open(arquivo, ifstream::trunc);

	caminho = agentes.front().get_caminho();
	for(i = 0; i < caminho.size()-1; i++)
	{
		arq << caminho[i] << endl;
	}

	arq.close();

}		/* -----  end of function imprimir_agentes  ----- */
