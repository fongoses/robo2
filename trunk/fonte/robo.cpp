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
Robo::Robo (Vertice v_inicial, Mapa m, Salas *s, bool _simular)
{
	Ponto pos_inicial = v_inicial.second;

	vertice = v_inicial.first;
	simular = _simular;
	mapa = m;
	sala = s;
	angulo_sim = 0;
	tempo_viagem = 0;
//	//DEBUG*/cout	<< "Posicao inicial: " << pos_inicial << "[" << mapa.get_vertice(pos_inicial) << "].\n";
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
	//DEBUG*/cout	<< "ROBO#Robo: construtor copia\n";getchar();
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
	void
Robo::irPara ( Ponto p )
{
//	time_t tempo = 0;
	float ang_dist;

//	time(&tempo);
	//DEBUG*/cout	<< "ROBO#ipPara: Indo para ponto: " << p << "[" << mapa.get_vertice(p) << "].\n";getchar();
//	//DEBUG*/cout	<< vertice << endl;
	if(!simular) {
		time(&inicio);
		position->GoTo(p.get_x(), p.get_y(), 0);

/* MODO BLOQUEANTE */
//		while(!chegou(p));
//		tempo = time(NULL) - tempo;

/* MODO NAO BLOQUEANTE */
//		tempo = 0;
//		while(time(NULL) - tempo == 0); /* Espera pelo menos 1s */
//		tempo = time(NULL) - tempo;
	} else {
		inicio = tempo_viagem;
//		cout	<< "Simulando\n";
		ang_dist = mapa.get_ponto(vertice).distancia_angular(&angulo_sim, p);
//		ang_dist = p.distancia_angular(angulo_sim, mapa.get_ponto(vertice));
		if(ang_dist >= 0)
			t_sim = floor(ang_dist / SIMULACAO_ROT + 0.5);
		else
			t_sim = floor(-ang_dist / SIMULACAO_ROT + 0.5);
//		cout << endl << ang_dist * GRAD_TO_RAD << " Demorou: " << tempo << endl;
		t_sim += floor(p.distancia(mapa.get_ponto(vertice)) / SIMULACAO_VEL + 0.5);
//		cout << "Demorou no total: " << tempo << endl;
//		//DEBUG*/cout << "Distancia entre: " << p << " e " << mapa.get_ponto(vertice) << " = " << p.distancia(mapa.get_ponto(vertice)); 
//			   << " Velocidade: " <<  SIMULACAO_VEL << " ";
		
//		cout	<< "Demorou " << tempo << "s.\n";
//		getchar();
	}
	vertice = mapa.get_vertice(p);
//	return tempo;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  irPara
 * Description:  Vai para o vertice v
 *							 e retorna o tempo que demorou para chegar (s)
 *--------------------------------------------------------------------------------------
 */
	void
Robo::irPara ( int v )
{
//	ListaVertices caminho;
//	ListaVertices::iterator it_c;
//	int tempo = 0;

	caminho =  mapa.dijkstra(vertice, v);
//	caminho.pop_front(); /* Remove o primeiro vertice do caminho que e' onde o robo esta */
	irPara(mapa.get_ponto(caminho.front()));
/*	for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
		tempo += irPara(mapa.get_ponto(*it_c));
	}*/

//	return tempo;
}		/* -----  end of method Robo::irPara  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  chegou
 * Description:  Retorna se o robo chegou na posicao do ponto p ou nao
 *--------------------------------------------------------------------------------------
 */
	bool
Robo::chegou ( )
{
	return chegou(caminho.front());
}
	bool
Robo::chegou ( int v )
{
	return chegou(mapa.get_ponto(v));
}

	bool
Robo::chegou ( Ponto p )
{
	Ponto atual;
	bool ir_proximo = false;

	if(!simular)
	{
		player_client->Read();
		atual.set_x(position->GetXPos());
		atual.set_y(position->GetYPos());
//		cout << atual << " " << p << endl;
//			cout << "Dist: " << atual.distancia(p) << " > " << DISTANCIA_ERRO << endl;
		tempo_viagem = time(NULL) - inicio;
		if (atual.distancia(p) < DISTANCIA_ERRO)
		{
			ir_proximo = true;
		}
	} else {
		t_sim--;
		if(t_sim < 0)
			ir_proximo = true;
		else
			tempo_viagem++;
//		//DEBUG*/cout << "ROBO " << tempo_viagem << "-" << t_sim << endl;//getchar();
	}

	if(ir_proximo)
	{
		caminho.pop_front();
//		//DEBUG*/cout << "ROBO Caminho: Faltam " << caminho.size() << endl;getchar();
		if(!caminho.empty())
		{
//			//DEBUG*/cout << "ROBO Caminho não vazio!!" << endl;getchar();
			irPara(mapa.get_ponto(caminho.front()));
			return false;
		}	else {
//			//DEBUG*/cout << "ROBO Caminho vazio!!\n";getchar();
			return true;
		}
	}
}		/* -----  end of method Robo::chegou  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  visitar_sala
 * Description:  Visita a Sala onde o robo se encontra
 *--------------------------------------------------------------------------------------
 */
	time_t
Robo::visitar_sala ( )
{
	time_t inicio, tempo;

	//DEBUG*/cout << "ROBO#visitar_sala: Visitando sala do vertice " << vertice << endl;getchar();

	if(sala->ehSala(vertice))
	{
		if(!simular)
		{
			time(&inicio);
			sleep(VISITAR_SALA); /* Visita da sala simulada por tempo */
			// SUBSTITUIR POR UMA VOLRA DE 360?
			tempo = time(NULL) - inicio;
		} else {
			tempo = VISITAR_SALA;
		}
		sala->visitar(sala->get_sala(vertice));
		return tempo;
	}	else
			cerr << "ROBO#visitar_sala: vertice " << vertice << " não é uma sala!\n";
	return 0;
}		/* -----  end of method Robo::visitar_sala  ----- */

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

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Robo
 *      Method:  get_tempo_viagem
 * Description:  Retorna o vertice onde o robo se encontra
 *--------------------------------------------------------------------------------------
 */
	time_t
Robo::get_tempo_viagem ( )
{
	time_t resp = tempo_viagem;
	tempo_viagem = 0;
	return resp;
}		/* -----  end of method Robo::get_tempo_viagem  ----- */


/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
