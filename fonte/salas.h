/*
 * =====================================================================================
 *
 *       Filename:  salas.h
 *
 *    Description:  Definicao da classe Salas
 *
 *        Version:  1.0
 *        Created:  10/08/2008 11:06:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#ifndef  SALAS_INC
#define  SALAS_INC

#include	<map>
#include	<iostream>
#include	<ctime>
#include	<vector>
#include	<climits>
#include	<cstdio>

using namespace std;

#define	VISITAR_SALA 5			/* Tempo para visitar uma sala (s) */
#define ATUALIZACAO 1
#define FATOR_ER 1000


/*
 * =====================================================================================
 *        Class:  Sala
 *  Description:  Classe de uma sala
 * =====================================================================================
 */
class Sala
{
	public:

		/* ====================  LIFECYCLE     ======================================= */
		Sala ();                             /* constructor      */
		Sala ( const Sala &other );   /* copy constructor */
		~Sala ();                            /* destructor       */

		/* ====================  OPERATORS     ======================================= */
		const Sala& operator = ( const Sala &other ); /* assignment operator */

		bool operator == (Sala &other);
		bool operator != (Sala &other);

		/* ====================  OPERATIONS    ======================================= */

		/* ====================  ACCESS        ======================================= */

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
		int vertice;
		unsigned int P;
		unsigned int U;
		unsigned int visitas;
	protected:

	private:

}; /* -----  end of class  Sala  ----- */

typedef map<int, Sala> MapaSala;
typedef vector<int> VetorSalas;
typedef vector<int> VetorVertices;

/*
 * =====================================================================================
 *        Class:  Salas
 *  Description:
 * =====================================================================================
 */
class Salas
{
	public:

		/* ====================  LIFECYCLE     ======================================= */
		Salas ();                             /* constructor      */
		Salas ( const Salas &other );   /* copy constructor */
		~Salas ();                            /* destructor       */

		/* ====================  OPERATORS     ======================================= */
		const Salas& operator = ( const Salas &other ); /* assignment operator */

		bool operator == (Salas &other);
		bool operator != (Salas &other);

		/* ====================  METHODS       ======================================= */
		void adicionarSala(int num, int vertice, int P);
		bool existeSala(int num);
		bool ehSala(int v);
		int atualizar(time_t t);
		void visitar(int s);

		void imprimir();
		void zerar_prioridades();
		void zerar_visitas();
		void incrementar_prioridade(int s);
		void emergencia(int s);

		/* ====================  ACCESS        ======================================= */
		VetorVertices get_salas_vertices();
		VetorSalas get_salas();
		int get_maiorU(int *U = NULL);
		int get_vertice( int s );
		int get_sala( int v );

		void set_ultima_atualizacao(time_t t);

		MapaSala get_salas_completo();
		void set_salas(MapaSala s);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
		time_t ultima_atualizacao;
	protected:

	private:

		MapaSala sala;

}; /* -----  end of class  Salas  ----- */


#endif
