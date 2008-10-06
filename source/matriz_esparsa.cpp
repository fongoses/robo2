/*
 * =====================================================================================
 *
 *       Filename:  matriz_esparsa.cpp
 *
 *    Description:  Implementacao da classe MatrizEsparsa
 *
 *        Version:  1.0
 *        Created:  10/02/2008 06:33:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#include	<cstdlib>
#include	<cfloat>

#include	"matriz_esparsa.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrizEsparsa
 *      Method:  MatrizEsparsa
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
MatrizEsparsa::MatrizEsparsa ()
{
  raiz = new CelulaEsparsa();
}  /* -----  end of method MatrizEsparsa::MatrizEsparsa  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrizEsparsa
 *      Method:  MatrizEsparsa
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
MatrizEsparsa::~MatrizEsparsa()
{
  CelulaEsparsa *aux, *l, *c;

  l = raiz->getProxLinha();

  while(l != NULL) {
    c = l->getProxColuna();
    while(c != NULL) {
      aux = c;
//      printf("Liberou [%2d, %2d] = %2.2f\t", coluna->l, coluna->c, coluna->valor);
      c = c->getProxColuna();
      delete(aux);
    }
    l = l->getProxLinha();
  }
  delete(raiz);
}  /* -----  end of method MatrizEsparsa::~MatrizEsparsa  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrizEsparsa
 *      Method:  adicionarCelula
 * Description:  Adiciona uma celula na matriz
 *--------------------------------------------------------------------------------------
 */
	int
MatrizEsparsa::adicionarCelula ( int l, int c, float v )
{
	CelulaEsparsa *aux, *nova;
	aux = get_celula(l, c);
printf("Adicionando [%d, %d] = %f\n", l, c, v);
	if(aux != NULL) {
		cerr << "Celula [" << l << ", " << c << "] Já existe! Sobreescrevendo o valor."  << endl;
		aux->setValor(v);
	} else {
		/* Aumentando os dimensoes da matriz, se necessario */
		if(c + 1 > (int)coluna.size()) {
			coluna.resize(c + 1);
		}
		if(l + 1 > (int)linha.size()) {
			linha.resize(l + 1);
		}

		nova = new CelulaEsparsa(l, c, v);

		/* localizando a posicao onde a nova celula tem que ser inserida */
		aux = &coluna[c];
		/* Enquanto a proxima celula existir, ou a pocisao da linha for depois da nova celula */
		while((aux->getProxLinha() != NULL) && (aux->getProxLinha()->get_linha() < l)) {
			aux = aux->getProxLinha();
		}

		nova->setProxLinha(aux->getProxLinha());
		aux->setProxLinha(nova);

		aux = &linha[l];
		/* Enquanto a proxima celula existir, ou a pocisao da coluna for depois da nova celula */
		while((aux->getProxColuna() != NULL) && (aux->getProxColuna()->get_coluna() < c)) {
			aux = aux->getProxColuna();
		}

		nova->setProxColuna(aux->getProxColuna());
		aux->setProxColuna(nova);
	}


	return 0;
}		/* -----  end of method MatrizEsparsa::adicionarCelula  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrizEsparsa
 *      Method:  adicionarCelulaDupla
 * Description:  Adiciona duas celulas simetricas
 *--------------------------------------------------------------------------------------
 */
	int
MatrizEsparsa::adicionarCelulaDupla ( int l, int c, float v )
{
	return (adicionarCelula(l, c, v) | adicionarCelula(c, l, v));
}		/* -----  end of method MatrizEsparsa::adicionarCelulaDupla  ----- */

	CelulaEsparsa
*MatrizEsparsa::get_celula ( int l, int c )
{
	CelulaEsparsa *aux;
	if((l <= (int)linha.size() || c <= (int)coluna.size())) {
		/* localizando a posicao onde a nova celula tem que ser inserida */
		aux = &coluna[c];
		/* Enquanto a proxima celula existir, ou a pocisao da linha for depois da nova celula */
		while((aux->getProxLinha() != NULL) && (aux->getProxLinha()->get_linha() != l)) {
			aux = aux->getProxLinha();
		}
		return aux->getProxLinha();
	} else {
		return NULL;
	}
}		/* -----  end of method MatrizEsparsa::get_celula  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  MatrizEsparsa
 *      Method:  get_valor
 * Description:  
 *--------------------------------------------------------------------------------------
 */
	float
MatrizEsparsa::get_valor ( int l, int c )
{
	CelulaEsparsa *aux;

	aux = get_celula(l, c);
	if(aux != NULL) {
		return aux->get_valor();
	} else {
		return -FLT_MAX;
	}

}		/* -----  end of method MatrizEsparsa::get_valor  ----- */

	void
MatrizEsparsa::imprimir (  )
{
	int l, c;
	for ( l = 0; l < (int)linha.size(); l += 1 )
		for ( c = 0; c < (int)coluna.size(); c += 1 )
			if(get_celula(l, c) != NULL)
				cout << "[" << l << ", " << c << "]=>" << get_valor(l, c) << endl;
	return ;
}		/* -----  end of method MatrizEsparsa::imprimir  ----- */

