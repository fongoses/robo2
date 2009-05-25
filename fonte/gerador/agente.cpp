/*
 * =====================================================================================
 *
 *       Filename:  agente.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/25/2009 03:28:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */


#include	"agente.h"
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  Agente
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Agente::Agente ()
{
}  /* -----  end of method Agente::Agente  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  Agente
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Agente::Agente (int inicial)
{
	vertice = inicial;
	caminho.push_back(inicial);
	avaliacao = 0;
}  /* -----  end of method Agente::Agente  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  Agente
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Agente::Agente ( const Agente &other )
{
}  /* -----  end of method Agente::Agente  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  ~Agente
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Agente::~Agente ()
{
}  /* -----  end of method Agente::~Agente  (destructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Agente&
Agente::operator = ( const Agente &other )
{
	if ( this != &other ) {
	}
	return *this;
}  /* -----  end of method Agente::operator =  (assignment operator)  ----- */

