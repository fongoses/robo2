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
//	linha = new CelulaEsparsa();
//	coluna = new CelulaEsparsa();

//	raiz->linha = linha;
//	raiz->coluna = coluna;

//	total_linhas = total_colunas = -1;
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

	int
MatrizEsparsa::adicionarCelula ( int l, int c, float v )
{
	CelulaEsparsa *aux, *nova;
	aux = getCelula(l, c);
printf("Adicionando [%d, %d] = %f\n", l, c, v);getchar();
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
		while((aux->getProxLinha() != NULL) && (aux->getProxLinha()->getLinha() < l)) {
			aux = aux->getProxLinha();
		}

		nova->setProxLinha(aux->getProxLinha());
		aux->setProxLinha(nova);

		aux = &linha[c];
		/* Enquanto a proxima celula existir, ou a pocisao da coluna for depois da nova celula */
		while((aux->getProxColuna() != NULL) && (aux->getProxColuna()->getColuna() < c)) {
			aux = aux->getProxColuna();
		}

		nova->setProxColuna(aux->getProxColuna());
		aux->setProxColuna(nova);
	}

	imprimir();getchar();

	cerr << "addCelula incompleto!!!" << endl;
	return 0;
}		/* -----  end of method MatrizEsparsa::adicionarCelula  ----- */

	CelulaEsparsa
*MatrizEsparsa::getCelula ( int l, int c )
{
	CelulaEsparsa *aux;
	if((l <= (int)linha.size() || c <= (int)coluna.size())) {
		/* localizando a posicao onde a nova celula tem que ser inserida */
		aux = &coluna[c];
		/* Enquanto a proxima celula existir, ou a pocisao da linha for depois da nova celula */
		while((aux->getProxLinha() != NULL) && (aux->getProxLinha()->getLinha() != l)) {
			aux = aux->getProxLinha();
		}
		return aux->getProxLinha();
	} else {
		return NULL;
	}
}		/* -----  end of method MatrizEsparsa::getCelula  ----- */

	float
MatrizEsparsa::getValor ( int l, int c )
{
	CelulaEsparsa *aux;

	aux = getCelula(l, c);
	if(aux != NULL) {
		return aux->getValor();
	} else {
		return -FLT_MAX;
	}

}		/* -----  end of method MatrizEsparsa::getValor  ----- */

	void
MatrizEsparsa::imprimir (  )
{
	int l, c;
	for ( l = 0; l < (int)linha.size(); l += 1 )
		for ( c = 0; c < (int)coluna.size(); c += 1 ) {
			cout << "[" << l << ", " << c << "]=>" << getValor(l, c) << endl;
		}
			return ;
}		/* -----  end of method MatrizEsparsa::imprimir  ----- */

