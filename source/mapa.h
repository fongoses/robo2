/*
 * =====================================================================================
 *
 *       Filename:  mapa.h
 *
 *    Description:  Definicao da classe Mapa
 *
 *        Version:  1.0
 *        Created:  10/05/2008 10:16:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#ifndef  MAPA_INC
#define  MAPA_INC
#include	<cstdio>
#include	<iostream>

#include	<map>
#include	<list>

#include	"ponto.h"

using namespace std;

/*-----------------------------------------------------------------------------
 *  Definicao dos tipos para o codigo ficar mais claro
 *-----------------------------------------------------------------------------*/
typedef map<int, Ponto> MapaVertices;
typedef map<pair<int, int>, float> MapaPesos;
typedef pair<int, int> Aresta;
typedef list<int> ListaVertices;

/*
 * =====================================================================================
 *        Class:  Mapa
 *  Description:  Definicao da classe Mapa
 * =====================================================================================
 */
class Mapa
{
	public:

		/* ====================  LIFECYCLE     ======================================= */
		Mapa ();                             /* constructor      */
		Mapa ( const Mapa &other );   /* copy constructor */
		~Mapa ();                            /* destructor       */

		/* ====================  OPERATORS     ======================================= */
		const Mapa& operator = ( const Mapa &other ); /* assignment operator */

		/* ====================  METHODS       ======================================= */
		void adicionarVertice (int noh, Ponto p );
		void adicionarAresta (int vA, int vB);
		ListaVertices verticesAdjacentes (int v );
		bool adjacente (int vA, int vB);

		/* ====================  ACCESS        ======================================= */
		float get_peso ( int vA, int vB );

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		MapaVertices vertice;
		MapaPesos peso;

}; /* -----  end of class  Mapa  ----- */
    
#endif   /* ----- #ifndef MAPA_INC  ----- */
