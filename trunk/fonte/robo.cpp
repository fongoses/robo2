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
Robo::Robo (Vertice v_inicial, Mapa m, bool _simular)
{
	Ponto pos_inicial = v_inicial.second;

	vertice = v_inicial.first;
	simular = _simular;
	mapa = m;
	angulo_sim = 0;
//	cout	<< "Posicao inicial: " << pos_inicial << "[" << mapa.get_vertice(pos_inicial) << "].\n";
	if(!simular) {
		player_client = new PlayerClient(HOST, PORT);
		position = new Position2dProxy(player_client, 1);
		laser = new LaserProxy(player_client, 0);

		position->SetOdometry(pos_inicial.get_x(), pos_inicial.get_y(), 0);
		irPara(vertice);
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
 *							 e retorna o tempo que demorou para chegar (s)
 *--------------------------------------------------------------------------------------
 */
	int
Robo::irPara ( Ponto p )
{
	time_t tempo = 0;
	float ang_dist;

	time(&tempo);
	cout	<< "\nIndo para ponto: " << p << "[" << mapa.get_vertice(p) << "].\n";
//	cout	<< vertice << endl;
	if(!simular) {
		cout	<< "ROBO::irPara Arrumar o tempo\n";
//		time(&tempo);
		position->GoTo(p.get_x(), p.get_y(), 0);

/* MODO BLOQUEANTE */
//		while(!chegou(p));
//		tempo = time(NULL) - tempo;

/* MODO NAO BLOQUEANTE */
		tempo = 0;
//		while(time(NULL) - tempo == 0); /* Espera pelo menos 1s */
//		tempo = time(NULL) - tempo;
	} else {
//		cout	<< "Simulando\n";
		ang_dist = mapa.get_ponto(vertice).distancia_angular(&angulo_sim, p);
//		ang_dist = p.distancia_angular(angulo_sim, mapa.get_ponto(vertice));
		if(ang_dist >= 0)
			tempo = floor(ang_dist / SIMULACAO_ROT + 0.5);
		else
			tempo = floor(-ang_dist / SIMULACAO_ROT + 0.5);
//		cout << endl << ang_dist * GRAD_TO_RAD << " Demorou: " << tempo << endl;
		tempo += floor(p.distancia(mapa.get_ponto(vertice)) / SIMULACAO_VEL + 0.5);
//		cout << "Demorou no total: " << tempo << endl;
//		cout << "Distancia entre: " << p << " e " << mapa.get_ponto(vertice) << " = " << p.distancia(mapa.get_ponto(vertice)); 
//			   << " Velocidade: " <<  SIMULACAO_VEL << " ";
		
//		cout	<< "Demorou " << tempo << "s.\n";
//		getchar();
	}
	vertice = mapa.get_vertice(p);
	return tempo;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  irPara
 * Description:  Vai para o vertice v
 *							 e retorna o tempo que demorou para chegar (s)
 *--------------------------------------------------------------------------------------
 */
	int
Robo::irPara ( int v )
{
//	ListaVertices caminho;
	ListaVertices::iterator it_c;
	int tempo = 0;

	caminho =  mapa.dijkstra(vertice, v);
	caminho.pop_front(); /* Remove o primeiro vertice do caminho que e' onde o robo esta */
	for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
		tempo += irPara(mapa.get_ponto(*it_c));
	}

	return tempo;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  chegou
 * Description:  Retorna se o robo chegou na posicao do ponto p ou nao
 *--------------------------------------------------------------------------------------
 */
	bool
Robo::chegou ( int v )
{
	return chegou(mapa.get_ponto(v));
}

	bool
Robo::chegou ( Ponto p )
{
	Ponto atual;

	if(!simular)
	{
		player_client->Read();
		atual.set_x(position->GetXPos());
		atual.set_y(position->GetYPos());
		//	cout << "Dist: " << atual.distancia(p) << " > " << DISTANCIA_ERRO << endl;
		return atual.distancia(p) < DISTANCIA_ERRO;
	} else {
		return false;
	}
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
Robo::set_vertice ( int v )
{
	vertice = v;
	return ;
}		/* -----  end of method Robo::set_vertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  get_vertice
 * Description:  Retorna o vertice onde o robo se encontra
 *--------------------------------------------------------------------------------------
 */
	int
Robo::get_vertice ( )
{
	return vertice;
}		/* -----  end of method Robo::get_vertice  ----- */


/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
