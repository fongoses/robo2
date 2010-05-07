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

#include	<iostream>

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
	vertice = -1;
	avaliacao = 0;
	tempo = 0;
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
	tempo = 0;
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
	vertice = other.vertice;
	caminho = other.caminho;
	avaliacao = other.avaliacao;
	tempo = other.tempo;
}  /* -----  end of method Agente::Agente  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  novo
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
void Agente::novo ()
{
	vertice = -1;
	avaliacao = 0;
	tempo = 0;
	caminho.clear();
}  /* -----  end of method Agente::novo  (constructor)  ----- */

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
		vertice = other.vertice;
		caminho = other.caminho;
		avaliacao = other.avaliacao;
	}
	return *this;
}  /* -----  end of method Agente::operator =  (assignment operator)  ----- */
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator>
 * Description:  grater then operator
 *--------------------------------------------------------------------------------------
 */
	bool
Agente::operator> (Agente &ag)
{
	if(avaliacao != ag.avaliacao)
		return avaliacao > ag.avaliacao;
	else
		return caminho.size() > ag.caminho.size();
}		/* -----  end of method Agente::operator>  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator>=
 * Description:  grater equal then operator
 *--------------------------------------------------------------------------------------
 */
	bool
Agente::operator>= (Agente &ag)
{
	return avaliacao >= ag.avaliacao;
}		/* -----  end of method Agente::operator>=  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator<
 * Description:  less then operator
 *--------------------------------------------------------------------------------------
 */
	bool
Agente::operator< (Agente &ag)
{
	if(avaliacao != ag.avaliacao)
		return avaliacao < ag.avaliacao;
	else if(caminho.size() != ag.caminho.size())
		return caminho.size() < ag.caminho.size();
    else
        for(unsigned int i = 0; i < caminho.size(); i++)
            if(caminho[i] < ag.caminho[i]) return true;
            else if(caminho[i] > ag.caminho[i]) return false;
}		/* -----  end of method Agente::operator<  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator<=
 * Description:  less equal then operator
 *--------------------------------------------------------------------------------------
 */
	bool
Agente::operator<= (Agente &ag)
{
	return avaliacao <= ag.avaliacao;
}		/* -----  end of method Agente::operator<=  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  operator==
 * Description:  equal operator
 *--------------------------------------------------------------------------------------
 */
	bool
Agente::operator== (Agente &ag)
{
	return (avaliacao == ag.avaliacao) && (caminho.size() == ag.caminho.size());
}		/* -----  end of method Agente::operator==  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  imprimir
 * Description:  Imprime o agente
 *--------------------------------------------------------------------------------------
 */
	void
Agente::imprimir (  )
{
	cout << "Vertice: " << vertice << endl;
	cout << "Caminho:";
	for(unsigned int i = 0; i < caminho.size(); i++)
		cout << " " << caminho[i];
	cout << endl << "Avaliacao: " << avaliacao << endl;
	cout << "Tempo: " << tempo << endl;

}		/* -----  end of method Agente::imprimir  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  get_vertice
 *--------------------------------------------------------------------------------------
 */
	int
Agente::get_vertice (  )
{
	return vertice;
}		/* -----  end of method Agente::get_vertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  set_vertice
 *--------------------------------------------------------------------------------------
 */
	 void
Agente::set_vertice ( int value )
{
	vertice	= value;
	if(caminho.size() == 0)
        caminho.push_back(value);
	return ;
}		/* -----  end of method Agente::set_vertice  ----- */
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  get_avaliacao
 *--------------------------------------------------------------------------------------
 */
	 int
Agente::get_avaliacao (  )
{
	return avaliacao;
}		/* -----  end of method Agente::get_avaliacao  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  set_avaliacao
 *--------------------------------------------------------------------------------------
 */
	 void
Agente::set_avaliacao ( int value )
{
	avaliacao	= value;
	return ;
}		/* -----  end of method Agente::set_avaliacao  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  get_caminho
 *--------------------------------------------------------------------------------------
 */
	 Caminho
Agente::get_caminho (  )
{
	return caminho;
}		/* -----  end of method Agente::get_caminho  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  set_caminho
 *--------------------------------------------------------------------------------------
 */
	 void
Agente::set_caminho ( Caminho value )
{
	caminho	= value;
	return ;
}		/* -----  end of method Agente::set_caminho  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  get_tamanho
 * Description:  Retorna o tamanho do caminho
 *--------------------------------------------------------------------------------------
 */
	int
Agente::get_tamanho ( )
{
	return caminho.size();
}		/* -----  end of method Agente::get_tamanho  ----- */
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Agente
 *      Method:  adicionarVertice
 * Description:  Adiciona um vertice no caminho do Agente
 *--------------------------------------------------------------------------------------
 */
	void
Agente::adicionarVertice ( int vertice )
{
	caminho.push_back(vertice);
}		/* -----  end of method Agente::adicionarVertice  ----- */

