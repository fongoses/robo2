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
Ponto::Ponto (float x, float y)
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
	float
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
Ponto::set_x ( float value )
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
	float
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
Ponto::set_y ( float value )
{
	y	= value;
	return ;
}		/* -----  end of method Ponto::set_y  ----- */

	void
Ponto::set ( float vx, float vy)
{
	x = vx;
	y = vy;

	return ;
}		/* -----  end of method Ponto::set  ----- */

ostream& operator<<(ostream& out, const Ponto& p)
{
  out<<"(" << p.x << ", " << p.y << ")" <<endl;
	return out;
}

const Ponto& Ponto::operator = ( const Ponto &P )
{
	if( this != &P) {
		x = P.x;
		y = P.y;
	}
	return *this;
}

bool Ponto::operator==(Ponto P)
{
	return ((x == P.get_x()) && (y == P.get_y()))	;
}
