/*
 * =====================================================================================
 *
 *       Filename:  robo.cpp
 *
 *    Description:  Descricao da classe Robo
 *
 *        Version:  1.0
 *        Created:  10/07/2008 02:02:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */

#include "robo.h"

/*-----------------------------------------------------------------------------
 * ====================  LIFECYCLE     =======================================
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  Robo
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Robo::Robo ()
{
}  /* -----  end of method Robo::Robo  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  Robo
 * Description:  constructor com o vertice inicial do robô
 *--------------------------------------------------------------------------------------
 */
Robo::Robo (Ponto pos_inicial, Mapa m, bool _simular)
{
	simular = _simular;
	mapa = m;
	cout	<< "Posicao inicial: " << pos_inicial << ".\n";
	if(!simular) {
		player_client = new PlayerClient(HOST, PORT);
		position = new Position2dProxy(player_client, 1);
		laser = new LaserProxy(player_client, 0);

		position->SetOdometry(pos_inicial.get_x(), pos_inicial.get_y(), 0);
	}
}  /* -----  end of method Robo::Robo  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  Robo
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Robo::Robo ( const Robo &other )
{
	cout	<< "ROBO construtor copia\n";getchar();
}  /* -----  end of method Robo::Robo  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  ~Robo
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Robo::~Robo ()
{
}  /* -----  end of method Robo::~Robo  (destructor)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  OPERATORS     ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Robo&
Robo::operator = ( const Robo &other )
{
	if ( this != &other ) {
	}
	return *this;
}  /* -----  end of method Robo::operator =  (assignment operator)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  METHODS       ======================================= *
 *-----------------------------------------------------------------------------*/

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  irPara
 * Description:  Vai para a posicao do ponto p 
 *--------------------------------------------------------------------------------------
 */
	void
Robo::irPara ( Ponto p )
{
	cout	<< "Indo para ponto: " << p << endl;
	if(!simular) {
		position->GoTo(p.get_x(), p.get_y(), 0);
	} else {
		cout	<< "Simulando\n";
	}
	return ;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  irPara
 * Description:  Vai para o vertice v
 *--------------------------------------------------------------------------------------
 */
	void
Robo::irPara ( int v )
{
	ListaVertices caminho;
	ListaVertices::iterator it_c;

	caminho =  mapa.dijkstra(vertice.first, v);
	for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
		irPara(*it_c);
		while(!chegou(*it_c));
	}

	return ;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  chegou
 * Description:  Retorna se o robo chegou na posicao do ponto p ou nao
 *--------------------------------------------------------------------------------------
 */
	bool
Robo::chegou ( Ponto p )
{
	Ponto atual;

	player_client.Read();
	atual.set_x(position.GetXPos());
	atual.set_y(position.GetYPos());
	return atual.distancia(p) < DISTANCIA_ERRO;
}		/* -----  end of method Robo::chegou  ----- */

/*-----------------------------------------------------------------------------
 * ====================  ACCESS        ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  set_vertice
 * Description:  Atribui o vertice v ao vertice do robo, incluindo sua posicao no mapa
 *--------------------------------------------------------------------------------------
 */
	void
Robo::set_vertice ( Vertice v )
{
	vertice = v;
	return ;
}		/* -----  end of method Robo::set_vertice  ----- */


/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
