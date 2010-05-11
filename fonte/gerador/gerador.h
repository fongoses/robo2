/*
 * =====================================================================================
 *
 *       Filename:  gerador.h
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
#include	<list>
#include	<string>

#include	"agente.h"

#define CAND_MAX 10000
#define CAND_MIN 1000
#define CAND_POR_ARQ 5000

using namespace std;

	list<Agente>
gerar(string arq_mapa);

	void
imprimir_agentes(list<Agente> c);

	void
salvar_loop(string arquivo, list<Agente> agentes);
