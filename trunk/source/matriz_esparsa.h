/*
 * =====================================================================================
 *
 *       Filename:  matriz_esparsa.h
 *
 *    Description:  Classe de uma matriz esparsa
 *
 *        Version:  1.0
 *        Created:  10/02/2008 05:19:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#ifndef MATRIZ_ESPARSA_H
#define	MATRIZ_ESPARSA_H			/*  */

#include	<iostream>
#include	<vector>

using namespace std;

/*
 * =====================================================================================
 *        Class:  CelulaEsparsa
 *  Description:  Classe de uma celula de uma matriz esparsa
 * =====================================================================================
 */
class CelulaEsparsa
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		CelulaEsparsa ()                             /* constructor */
		{
			valor = 0.0;
			linha = coluna = 0;
			p_linha = NULL;
			p_coluna = NULL;
			visitado = false;
		};
		
		CelulaEsparsa (int l, int c, int v)                             /* constructor */
		{
			valor = v;
			linha = l;
			coluna = c;
			p_linha = NULL;
			p_coluna = NULL;
			visitado = false;
		};

		~CelulaEsparsa ()                             /* denstructor */
		{
//			delete (p_linha);
//			delete (p_coluna);
		}
		/* ====================  OPERATORS     ======================================= */

		/* ====================  OPERATIONS    ======================================= */

		/* ====================  ACCESS        ======================================= */
		CelulaEsparsa *getProxLinha() {	return p_linha; };
		CelulaEsparsa *getProxColuna() {	return p_coluna; };
		float get_valor() {return valor; };
		int get_linha () { return linha; }; 
		int get_coluna () { return coluna; }; 

		void setProxLinha(CelulaEsparsa *p) { p_linha = p; };
		void setProxColuna(CelulaEsparsa *p) { p_coluna = p; };
		void setValor(float v) { valor = v; };
		void setLinha(int l) { linha = l; };
		void setColuna(int c) { coluna = c; };

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		float valor;
	  int linha, coluna;
	  CelulaEsparsa *p_linha, *p_coluna;
	  bool visitado;

}; /* -----  end of class  CelulaEsparsa  ----- */

/*
 * =====================================================================================
 *        Class:  MatrizEsparsa
 *  Description:  Classe de uma Matriz Esparsa
 * =====================================================================================
 */
class MatrizEsparsa
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		MatrizEsparsa ();                             /* constructor */
		~MatrizEsparsa ();                             /* destructor */

		/* ====================  OPERATORS     ======================================= */
		const MatrizEsparsa& operator = (const MatrizEsparsa &other);

		/* ====================  METHODS       ======================================= */
    int adicionarCelula(int l, int c, float valor);
    int adicionarCelulaDupla(int l, int c, float valor);
    int *menorCaminho(int origem, int destino);
//		bool existe(int l, int c);

    void imprimir();
    void imprimirLinha(int l);
    void imprimirCelula(CelulaEsparsa c);


		/* ====================  ACCESS        ======================================= */
    float get_valor(int l, int c);

    CelulaEsparsa *get_celula(int l, int c);
    CelulaEsparsa *get_linha(int l);
    CelulaEsparsa *get_coluna(int c);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
//		int total_linhas, total_colunas;
		CelulaEsparsa *raiz;
		vector<CelulaEsparsa> linha, coluna;

}; /* -----  end of class  MatrizEsparsa  ----- */

#endif
