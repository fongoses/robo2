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

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  set
 * Description:  Atribio os valores vx e vy no ponto.x e ponto.y respectivamente
 *--------------------------------------------------------------------------------------
 */
	void
Ponto::set ( float vx, float vy)
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
  out<<"(" << p.x << ", " << p.y << ")";
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
	float
Ponto::distancia ( const Ponto &P )
{
	return sqrt(pow(x - P.x, 2) + pow(y - P.y, 2));
}		/* -----  end of method Ponto::distancia  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Ponto
 *      Method:  distancia_angular
 * Description:  Retorna a distancia angular de um angulo a para virar para o ponto P
 *--------------------------------------------------------------------------------------
 */
	float
Ponto::distancia_angular ( float *a, const Ponto &P )
{
	float dx, dy, seno, cosseno, hipotenusa, ang, resp;

	dx = x - P.x;
	dy = y - P.y;

//	cout << "de [" << x << "," << y << "]" << endl;
//	cout << "para [" << P.x << "," << P.y << "]" << endl;

	hipotenusa = distancia(P);
	if(hipotenusa == 0)
		return 0;

	seno = dy / hipotenusa;
	cosseno = dx / hipotenusa;

//	cout << "sen: " << seno << endl;
//	cout << "cos: " << cosseno << endl;

	if(seno >= 0) /* Quadrantes I e II */
		ang = acos(cosseno);
	else if (cosseno < 0) /* Quadrante III */
		ang = -acos(cosseno);
	else /* Quadrante IV */
		ang = asin(seno);

//	cout << "de " << *a << " para " << ang << endl;
	resp = ang - *a;
//	cout << "Resp " << resp;

	*a = ang;
	if(resp > PI)
		resp -= 2 * PI;
	else if (resp < -PI)
		resp += 2 * PI;

	return resp;


}		/* -----  end of method Ponto::distancia_angular  ----- */

