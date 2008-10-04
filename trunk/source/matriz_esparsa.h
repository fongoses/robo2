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
		float getValor() {return valor; };
		int getLinha () { return linha; }; 
		int getColuna () { return coluna; }; 

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

		/* ====================  METHODS       ======================================= */
    int adicionarCelula(int l, int c, float valor);
    int adicionarCelulaDupla(int l, int c, float valor);
    int *menorCaminho(int origem, int destino);
//		bool existe(int l, int c);

    void imprimir();
    void imprimirLinha(int l);
    void imprimirCelula(CelulaEsparsa c);


		/* ====================  ACCESS        ======================================= */
    float getValor(int l, int c);

    CelulaEsparsa *getCelula(int l, int c);
    CelulaEsparsa *getLinha(int l);
    CelulaEsparsa *getColuna(int c);
		CelulaEsparsa *getRaiz();

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
//		int total_linhas, total_colunas;
		CelulaEsparsa *raiz;
		vector<CelulaEsparsa> linha, coluna;

}; /* -----  end of class  MatrizEsparsa  ----- */

