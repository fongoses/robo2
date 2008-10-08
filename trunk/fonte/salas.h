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

typedef struct _sala {
	int noh;
	int P;
	int U;
}sSala;				/* ----------  end of struct _sala  ---------- */

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
		void adicionarSala(int num, int noh, int P);
		bool existeSala(int num);

		/* ====================  ACCESS        ======================================= */

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		time_t ultima_atualizacao;

		map<int, sSala> sala;

}; /* -----  end of class  Salas  ----- */

