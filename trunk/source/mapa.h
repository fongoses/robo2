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

//#include "matriz_esparsa.h"
//#include "funcoes.h"
#include	"ponto.h"

using namespace std;

/*-----------------------------------------------------------------------------
 *  Definicao dos tipos para o codigo ficar mais claro
 *-----------------------------------------------------------------------------*/
typedef map<int, Ponto> MapaVertices;
typedef map<pair<int, int>, float> MapaPesos;
typedef pair<int, int> Aresta;
typedef list<int> ListaVertices;
///*
// * =====================================================================================
// *        Class:  Vertice
// *  Description:  Classe que define um vertice
// * =====================================================================================
// */
//class Vertice
//{
//	public:
//
//		/* ====================  LIFECYCLE     ======================================= */
//		Vertice () {                             /* constructor      */
//			noh = -1;
//		}
//		~Vertice () {};                            /* destructor       */
//
//		/* ====================  OPERATORS     ======================================= */
//		const Vertice& operator = ( const Vertice &other ) { /* assignment operator */
//			if ( this != &other ) {
//				noh = other.noh;
//				posicao = other.posicao;
//			}
//			return *this;
//		}  /* -----  end of method Vertice::operator =  (assignment operator)  ----- */
//		/* ====================  METHODS       ======================================= */
//
//		void imprimir() {	printf("(%2i)[%5.2f, %5.2f]", noh, posicao.get_x(), posicao.get_y()); };
//		/* ====================  ACCESS        ======================================= */
//
//		/* ====================  INQUIRY       ======================================= */
//
//		/* ====================  DATA MEMBERS  ======================================= */
//	protected:
//
//	private:
//		int noh;
//		Ponto posicao;
//
//}; /* -----  end of class  Vertice  ----- */


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
//		vector<Vertice> vertice;
		MapaVertices vertice;
		MapaPesos peso;
//		MatrizEsparsa matriz;

}; /* -----  end of class  Mapa  ----- */

//class Mapa_old {
//  private:
//    int total_vertices, maior_vertice;
//
//  public:
//    float x0, y0;
//    Mapa_old(float x, float y, int total_vertices); /* Posicao inicial do Robo */
//
//    void adicionar_vertice(int index, float x, float y);
////		void adicionar_vertice(Vertice v);
//		void adicionar_aresta(int vA, int vB);
//    int *menor_caminho_fator(int origem, int destino);
//    int *dijkstra(int origem, int destino);
//    int *menor_caminho(int origem, int destino, float *peso);
//    int *dijkstra(int origem, int destino, float *peso);
//    int **todos_os_caminhos(int origem, int destino, float **lista_pesos);
//
//    int *salas_adjacentes(int vertice, int *quais);
//    float get_peso(int vA, int vB);
////		Vertice get_vertice(int noh);
//
//    bool adjacente(int vA, int vB);
//    bool eh_sala(int v);
//
//		int extract_min(float *dist, int *ja_foi);
//
////		Vertice *vertices;
//    MatrizEsparsa *matriz;
//};
    
#endif   /* ----- #ifndef MAPA_INC  ----- */
