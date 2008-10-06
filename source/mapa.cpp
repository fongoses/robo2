/*
 * =====================================================================================
 *
 *       Filename:  mapa.cpp
 *
 *    Description:  Implementacao da classe Mapa
 *
 *        Version:  1.0
 *        Created:  10/05/2008 10:25:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */

#include	"matriz_esparsa.h"
#include	"mapa.h"


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  Mapa
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Mapa::Mapa ()
{
}  /* -----  end of method Mapa::Mapa  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  Mapa
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Mapa::Mapa ( const Mapa &other )
{
	printf("Construtor copia\n");getchar();
}  /* -----  end of method Mapa::Mapa  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  ~Mapa
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Mapa::~Mapa ()
{
}  /* -----  end of method Mapa::~Mapa  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Mapa&
Mapa::operator = ( const Mapa &other )
{
	printf("Mapa operator=\n");getchar();
	if ( this != &other ) {
		vertice = other.vertice;
		pesos = other.pesos;
	}
	return *this;
}  /* -----  end of method Mapa::operator =  (assignment operator)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  adicionarVertice
 * Description:  Adiciona um vertice no mapa
 *--------------------------------------------------------------------------------------
 */
	void
Mapa::adicionarVertice ( int noh, Ponto p )
{
 /* Verifica se o vertice ja existe */
	if (vertice.find(noh) == vertice.end()) {
		vertice[noh] = p;
	} else {
		cerr << "Vertice " << noh << " já existe.\n";
	}
	return ;
}		/* -----  end of method Mapa::adicionarVertice  ----- */

