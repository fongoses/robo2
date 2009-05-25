/*
 * =====================================================================================
 *
 *       Filename:  agente.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/25/2009 03:28:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */
#include	<vector>

using namespace std;

typedef vector<int> VetorVertices;
typedef vector<int> Caminho;
	/*
	 * =====================================================================================
	 *        Class:  Agente
	 *  Description:  
	 * =====================================================================================
	 */
	class Agente
	{
		public:

			/* ====================  LIFECYCLE     ======================================= */
			Agente ();                             /* constructor      */
			Agente ( int inicial);                             /* constructor      */
			Agente ( const Agente &other );   /* copy constructor */
			~Agente ();                            /* destructor       */

			/* ====================  OPERATORS     ======================================= */
			const Agente& operator = ( const Agente &other ); /* assignment operator */

			/* ====================  OPERATIONS    ======================================= */

			/* ====================  ACCESS        ======================================= */

			/* ====================  INQUIRY       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */
		protected:
			int vertice;
			Caminho caminho;
			int avaliacao;

		private:

	}; /* -----  end of class  Agente  ----- */


