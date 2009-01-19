/*
 * =====================================================================================
 *
 *       Filename:  salas.cpp
 *
 *    Description:  Descricao dda classe Salas
 *
 *        Version:  1.0
 *        Created:  10/08/2008 11:06:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */

#include	"salas.h"

/*-----------------------------------------------------------------------------
 * ====================  LIFECYCLE     =======================================
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  Salas
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Salas::Salas ()
{
	ultima_atualizacao = 0;
}  /* -----  end of method Salas::Salas  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  Salas
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Salas::Salas ( const Salas &other )
{
}  /* -----  end of method Salas::Salas  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  ~Salas
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Salas::~Salas ()
{
}  /* -----  end of method Salas::~Salas  (destructor)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  OPERATORS     ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Salas&
Salas::operator = ( const Salas &other )
{
	if ( this != &other ) {
	}
	return *this;
}  /* -----  end of method Salas::operator =  (assignment operator)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  METHODS       ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  adicionarSala
 * Description:  Adiciona uma sala
 *--------------------------------------------------------------------------------------
 */
	void
Salas::adicionarSala ( int num, int vertice, int P )
{
	cout	<< "Adicionando sala " << num << ".\n";
	if(!existeSala(num)) {
		sSala aux;
		aux.vertice = vertice;
		aux.P = P;
		aux.U = 0;
		sala[num] = aux;
	} else {
		cout	<< "Sala " << num << " ja existe\n";
	}
	return ;
}		/* -----  end of method Salas::adicionarSala  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  existeSala
 * Description:  Retorna se a sala de numero num existe
 *--------------------------------------------------------------------------------------
 */
	bool
Salas::existeSala ( int num )
{
	return sala.find(num) != sala.end();
}		/* -----  end of method Salas::existeSala  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  atualizar
 * Description:  Atualiza as urgencias das salas decorrido t segundos
 *--------------------------------------------------------------------------------------
 */
	int
Salas::atualizar ( time_t t )
{
	MapaSala::iterator it_s;
	time_t diferenca = t - ultima_atualizacao;
	ultima_atualizacao = t;
	int UTotal = 0;
//	cout << "Atualizando " << diferenca << " segundos\n"; getchar();

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		it_s->second.U += diferenca * it_s->second.P;
		UTotal += it_s->second.U;
	}
	return UTotal;
}		/* -----  end of method Salas::atualizar  ----- */
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  visitar
 * Description:  Visita a sala s
 *--------------------------------------------------------------------------------------
 */
	void
Salas::visitar ( int s ) 
{
//	cout << "Visitando sala: " << s << ".\n";
	sala[s].U = 0;
	return ;
}		/* -----  end of method Salas::visitar  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  imprimir
 * Description:  Imprimi as salas
 *--------------------------------------------------------------------------------------
 */
	void
Salas::imprimir ( )
{
	MapaSala::iterator it_s;


	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		cout << it_s->first << " => vertice = " << it_s->second.vertice <<
															" P = " << it_s->second.P <<
															" U = " << it_s->second.U << endl;

	}
	return ;
}		/* -----  end of method Salas::imprimir  ----- */

/*-----------------------------------------------------------------------------
 * ====================  ACCESS        ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_maiorU
 * Description:  Retorna a sala com maior grau de urgencia
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_maiorU ( int *U )
{
	int maiorU = 0, s;
	MapaSala::iterator it_s;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		if(it_s->second.U > maiorU) {
			s = it_s->first;
			maiorU = it_s->second.U;
		}
	}
	if(U != NULL) {
		*U = maiorU;
	}
	return s;
}		/* -----  end of method Salas::get_maiorU  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_vertice
 * Description:  Retorna o vertice da sala s
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_vertice ( int s )
{
	return sala.find(s)->second.vertice;
}		/* -----  end of method Salas::get_vertice  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_ultima_atualizacao
 *--------------------------------------------------------------------------------------
 */
	void
Salas::set_ultima_atualizacao ( time_t t )
{
	ultima_atualizacao	= t;
	return ;
}		/* -----  end of method Salas::set_ultima_atualizacao  ----- */

/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
