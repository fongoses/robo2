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

/*-----------------------------------------------------------------------------
 * ====================  LIFECYCLE     =======================================
 *-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * ====================  OPERATORS     ======================================= *
 *-----------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------
 * ====================  METHODS       ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  adicionarVertice
 * Description:  Adiciona um vertice no mapa
 *--------------------------------------------------------------------------------------
 */
	int
Mapa::adicionarVertice ( int noh, Ponto p )
{
	cout	<< "Adicionando o vertice " << noh << ".\n";
 /* Verifica se o vertice ja existe */
	if (!existeVertice(noh)) {
		vertice[noh] = p;
		cout << "Feito.\n";
	} else {
		cerr << "Vertice " << noh << " já existe.\n";
		return 0;
	}
	return 1;
}		/* -----  end of method Mapa::adicionarVertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  adicionarAresta
 * Description:  Adiciona duas arestas entre os vertices vA e vB. (ida e volta)
 *							 O peso e' a distancia euclidiana entre os pontos dos vertices
 *--------------------------------------------------------------------------------------
 */
	int
Mapa::adicionarAresta ( int vA, int vB )
{
	Aresta aresta;
	cout	<< "Adicionando a aresta " << vA << "-" << vB << ".\n";

	/* Veriticando se o vertice vA existe */
	if (existeVertice(vA)) {
		aresta.first = vA;
	} else {
		cerr << "Vertice " << vA << " não existe.\n";
		return 0;
	}

	/* Veriticando se o vertice vB existe */
	if (existeVertice(vB)) {
		aresta.second = vB;
	} else {
		cerr << "Vertice " << vB << " não existe.\n";
		return 0;
	}


 /* Verifica se o vertice ja existe */
	if (!existeAresta(aresta)) {
		peso[aresta] = vertice[vA].distancia(vertice[vB]);
		cout	<< "Feito.\n";
	} else {
		cerr << "Aresta " << vA << "-" << vB << " já existe.\n";
		return 0;
	}

	aresta.first = vB;
	aresta.second = vA;

	if (!existeAresta(aresta)) {
		cout	<< "Adicionando a aresta " << vB << "-" << vA << ".\n";
		peso[aresta] = vertice[vB].distancia(vertice[vA]);
		cout	<< "Feito.\n";
	} else {
		cerr << "Aresta " << vB << "-" << vA << " já existe.\n";
		return 0;
	}
	return 1;
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
		if (existeAresta(aresta)) {
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

	return (existeAresta(aresta));
}		/* -----  end of method Mapa::adjacente  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  existeAresta
 * Description:  Retorna se a aresta a existe ou nao
 *--------------------------------------------------------------------------------------
 */
	bool
Mapa::existeAresta ( Aresta a )
{
	return peso.find(a) != peso.end();
}		/* -----  end of method Mapa::existeAresta  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  existeVertice
 * Description:  Retorna se o vertice v existe
 *--------------------------------------------------------------------------------------
 */
	bool
Mapa::existeVertice ( int v )
{
	return vertice.find(v) != vertice.end();
}		/* -----  end of method Mapa::existeVertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  dijkstra
 * Description:  Calcula o menor caminho entre os vertices origem e destino
 *							 usando Dijkstra
 *--------------------------------------------------------------------------------------
 */
	ListaVertices
Mapa::dijkstra ( int origem, int destino )
{
	int u, v, menor_d;
//	VetorVertices d(qtde_vertices, INT_MAX), antec(qtde_vertices, -1);
	VetorVertices::iterator it_v;
	ListaVertices resp, adj;
	ListaVertices::iterator it_adj;
	MapaVertices Q(vertice);
	map<int, float> d;
	map<int, float>::iterator it_d, it_menor;
	map<int, int> antec;
	map<int, int>::iterator it_a;
	MapaVertices::iterator it_m;
	Aresta aresta;

	for (it_m = Q.begin(); it_m != Q.end(); it_m++) 
		d[(*it_m).first] = FLT_MAX;
	d[origem] = 0.0;

	while(Q.size() > 0) {
		/* extract_min */
//		cout	<< "Vetor: ";
//		for (it_d = d.begin(); it_d != d.end(); it_d++) 
//			cout << (*it_d).first << "=>" << (*it_d).second << " ";
//		cout << endl;
//
//		cout	<< "Q: ";
//		for (it_m = Q.begin(); it_m != Q.end(); it_m++) 
//			cout << (*it_m).first << " ";
//		cout << endl;getchar();

		menor_d = INT_MAX;
		for (it_d = d.begin(); it_d != d.end(); it_d++) {/* Procura o menor d que existe em Q */
//			cout << "Menor: " << menor_d << " Procurando: " << (*it_d).first << "=>" << (*it_d).second << endl;getchar();
			if(Q.find((*it_d).first) != Q.end()) {/* se existe em ! */
				if((*it_d).second < menor_d) {
					menor_d = (*it_d).second;
					it_menor = it_d;
				}
			}
		}
		u = (*it_menor).first;

//		cout	<< "Retirando " << u << endl;getchar();
		Q.erase(u);
		/* fim extract_min */

		adj = verticesAdjacentes(u);
		for ( it_adj = adj.begin(); it_adj != adj.end(); it_adj++) {
			v = *it_adj;

			aresta.first = u;
			aresta.second = v;
			if(d[v] > d[u] + peso[aresta]) {
				d[v] = d[u] + peso[aresta];
				antec[v] = u;
			}
		}
	}
	for(it_a = antec.begin(); it_a != antec.end(); it_a++) {
		cout << (*it_a).first << "=>" << (*it_a).second << endl;
	}

	u = destino;
	resp.push_front(destino);
	while(u != origem) {
		resp.push_front(antec[u]);
		u = antec[u];
	}

	return resp;
}		/* -----  end of method Mapa::dijkstra  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  imprimir
 * Description:  Imprimi todo o mapa
 *--------------------------------------------------------------------------------------
 */
	void
Mapa::imprimir ()
{
	MapaVertices::iterator it_v;
	MapaPesos::iterator it_a;
	Aresta a;

	cout	<< "Vertices:\n";
	for( it_v = vertice.begin(); it_v != vertice.end(); it_v++) {
		cout << (*it_v).first /* noh */ << " -> " 
			   << (*it_v).second /* ponto */ << endl;
	}

	cout	<< "Arestas:\n";
	for( it_a = peso.begin(); it_a != peso.end(); it_a++) {
		a = (*it_a).first; /* aresta */
		cout << a.first /* vA */ << "-" 
			   << a.second /* vB */ << " => " 
				 << (*it_a).second /* peso */ << endl;
	}
	return ;
}		/* -----  end of method Mapa::imprimir  ----- */

/*-----------------------------------------------------------------------------
 * ====================  ACCESS        ======================================= *
 *-----------------------------------------------------------------------------*/
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

	if(vA == vB ) {
		return 0;
	}
	aresta.first = vA;
	aresta.second = vB;

	if (existeAresta(aresta)) {
		return peso[aresta];
	} else {
		cerr << "Aresta " << vA << "-" << vB << " não existe.\n";
		return -1;
	}
}		/* -----  end of method Mapa::get_peso  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Mapa
 *      Method:  get_vertice
 * Description:  Retorna o ponto do vertice v
 *--------------------------------------------------------------------------------------
 */
	Ponto
Mapa::get_vertice ( int v )
{
	if (existeVertice(v)) {
		return vertice[v];
	} else {
		cerr << "Vertice " << v << " não existe.\n";
		return *(new Ponto);
	}
}		/* -----  end of method Mapa::get_vertice  ----- */

/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
