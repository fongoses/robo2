/*
 * =====================================================================================
 *
 *       Filename:  ponto.cpp
 *
 *    Description:  Classe que administra um ponto no R2
 *
 *        Version:  1.0
 *        Created:  09/25/2008 03:10:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#include	<cmath>

#include	"ponto.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  Ponto
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Ponto::Ponto ()
{
	x = y = 0;
}  /* -----  end of method Ponto::Ponto  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  Ponto
 * Description:  constructor com valores
 *--------------------------------------------------------------------------------------
 */
Ponto::Ponto (double x, double y)
{
	this->x = x;
	this->y = y;
}  /* -----  end of method Ponto::Ponto  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  get_x
 *--------------------------------------------------------------------------------------
 */
	double
Ponto::get_x (  )
{
	return x;
}		/* -----  end of method Ponto::get_x  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  set_x
 *--------------------------------------------------------------------------------------
 */
	void
Ponto::set_x ( double value )
{
	x	= value;
	return ;
}		/* -----  end of method Ponto::set_x  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  get_y
 *--------------------------------------------------------------------------------------
 */
	double
Ponto::get_y (  )
{
	return y;
}		/* -----  end of method Ponto::get_y  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  set_y
 *--------------------------------------------------------------------------------------
 */
	void
Ponto::set_y ( double value )
{
	y	= value;
	return ;
}		/* -----  end of method Ponto::set_y  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  set
 * Description:  Atribio os valores vx e vy no ponto.x e ponto.y respectivamente
 *--------------------------------------------------------------------------------------
 */
	void
Ponto::set ( double vx, double vy)
{
	x = vx;
	y = vy;

	return ;
}		/* -----  end of method Ponto::set  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  operator <<
 * Description:  
 *--------------------------------------------------------------------------------------
 */
ostream& operator<<(ostream& out, const Ponto& p)
{
  out<<"(" << p.x << ", " << p.y << ")" <<endl;
	return out;
}		/* -----  end of method Ponto::operator <<  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  operator =
 * Description:  operador de atribuicao
 *--------------------------------------------------------------------------------------
 */
const Ponto& Ponto::operator = ( const Ponto &P )
{
	if( this != &P) {
		x = P.x;
		y = P.y;
	}
	return *this;
}		/* -----  end of method Ponto::operator =  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  operator ==
 * Description:  Operador igualdade
 *--------------------------------------------------------------------------------------
 */
bool Ponto::operator==(const Ponto &P)
{
	return ((x == P.x) && (y == P.y))	;
}		/* -----  end of method Ponto::operator ==  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  distancia
 * Description:  Retorna a distancia euclidiana entre o ponto da classe e o ponto P
 *--------------------------------------------------------------------------------------
 */
	double
Ponto::distancia ( const Ponto &P )
{
	return sqrt(pow(x - P.x, 2) + pow(y - P.y, 2));
}		/* -----  end of method Ponto::distancia  ----- */

