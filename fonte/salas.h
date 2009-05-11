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
#include	<map>
#include	<iostream>
#include	<ctime>

using namespace std;

#define	VISITAR_SALA 5			/* Tempo para visitar uma sala (s) */
#define ATUALIZACAO 10

typedef struct _sala {
	int vertice;
	int P;
	int U;
}sSala;				/* ----------  end of struct _sala  ---------- */
		
typedef map<int, sSala> MapaSala;

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

		/* ====================  METHODS       ======================================= */
		void adicionarSala(int num, int vertice, int P);
		bool existeSala(int num);
		int atualizar(time_t t);
		void visitar(int s);

		void imprimir();

		/* ====================  ACCESS        ======================================= */
		int get_maiorU(int *U = NULL);
		int get_vertice( int s );

		void set_ultima_atualizacao(time_t t);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		time_t ultima_atualizacao;

		MapaSala sala;

}; /* -----  end of class  Salas  ----- */

