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
		peso = other.peso;
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
	cout	<< "Adicionando o vertice " << noh << ".\n";
 /* Verifica se o vertice ja existe */
	if (vertice.find(noh) == vertice.end()) {
		vertice[noh] = p;
		cout << "Feito.\n";
	} else {
		cerr << "Vertice " << noh << " já existe.\n";
	}
	return ;
}		/* -----  end of method Mapa::adicionarVertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  adicionarAresta
 * Description:  Adiciona duas arestas entre os vertices vA e vB. (ida e volta)
 *							 O peso e' a distancia euclidiana entre os pontos dos vertices
 *--------------------------------------------------------------------------------------
 */
	void
Mapa::adicionarAresta ( int vA, int vB )
{
	Aresta aresta;
	cout	<< "Adicionando a aresta " << vA << "-" << vB << ".\n";

	/* Veriticando se o vertice vA existe */
	if ( vertice.find(vA) != vertice.end()) {
		aresta.first = vA;
	} else {
		cerr << "Vertice " << vA << " não existe.\n";
		return ;
	}

	/* Veriticando se o vertice vB existe */
	if ( vertice.find(vB) != vertice.end()) {
		aresta.second = vB;
	} else {
		cerr << "Vertice " << vB << " não existe.\n";
		return ;
	}


 /* Verifica se o vertice ja existe */
	if (peso.find(aresta) == peso.end()) {
		peso[aresta] = vertice[vA].distancia(vertice[vB]);
		cout	<< "Feito.\n";

		aresta.first = vB;
		aresta.second = vA;

		cout	<< "Adicionando a aresta " << vB << "-" << vA << ".\n";
		peso[aresta] = vertice[vB].distancia(vertice[vA]);
		cout	<< "Feito.\n";
	} else {
		cerr << "Aresta " << vA << "-" << vB << " já existe.\n";
	}
	return ;
}		/* -----  end of method Mapa::adicionarAresta  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  salasAdjacentes
 * Description:  Retorna uma lista de vertes adjacentes ao vertice v
 *--------------------------------------------------------------------------------------
 */
	ListaVertices
Mapa::verticesAdjacentes ( int v )
{
	ListaVertices resp;
	MapaVertices::iterator it_v;
	Aresta aresta;
	int v2;

	aresta.first = v;
	for( it_v = vertice.begin(); it_v != vertice.end(); it_v++)
	{
		v2 = (*it_v).first;
		aresta.second = v2;
		if ( peso.find(aresta) != peso.end()) {
			cout << v2 << " adjacente ao " << v << ",\n";
			resp.push_back(v2);
		}
	}
	return resp;
}		/* -----  end of method Mapa::salasAdjacentes  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  adjacente
 * Description:  Retorna se o vertice vA e' adjacente ao vB
 *--------------------------------------------------------------------------------------
 */
	bool
Mapa::adjacente ( int vA, int vB )
{
	Aresta aresta;

	aresta.first = vA;
	aresta.second = vB;

	return (peso.find(aresta) != peso.end());
}		/* -----  end of method Mapa::adjacente  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  get_peso
 * Description:  Retorna o peso de ir de vA para vB
 *--------------------------------------------------------------------------------------
 */
	float
Mapa::get_peso ( int vA, int vB )
{
	Aresta aresta;

	aresta.first = vA;
	aresta.second = vB;

	if (peso.find(aresta) != peso.end()) {
		return peso[aresta];
	} else {
		cerr << "Aresta " << vA << "-" << vB << " não existe.\n";
		return -1;
	}
}		/* -----  end of method Mapa::get_peso  ----- */

