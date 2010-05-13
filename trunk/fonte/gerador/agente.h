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
#ifndef  AGENTE_INC
#define  AGENTE_INC

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
			void novo();

			/* ====================  OPERATORS     ======================================= */
			const Agente& operator = ( const Agente &other ); /* assignment operator */

			bool operator> (Agente &ag);
			bool operator>= (Agente &ag);
			bool operator< (Agente &ag);
			bool operator<= (Agente &ag);
			bool operator== (Agente &ag);

			/* ====================  OPERATIONS    ======================================= */
			void imprimir();

			/* ====================  ACCESS        ======================================= */
			int get_vertice();
			 void set_vertice( int value );
			 float get_avaliacao();
			 void set_avaliacao( float value );
			 Caminho get_caminho();
			 void set_caminho( Caminho value );
			 int get_tamanho();


			void adicionarVertice( int vertice );

			/* ====================  INQUIRY       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */
		protected:
			int vertice;
			Caminho caminho;
			float avaliacao;
			int tempo;


		private:

	}; /* -----  end of class  Agente  ----- */

#endif   /* ----- #ifndef AGENTE_INC  ----- */
