/*
 * =====================================================================================
 *
 *       Filename:  ponto.h
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
#ifndef  PONTO_INC
#define  PONTO_INC
#include	<ostream>

using namespace std;

/*
 * =====================================================================================
 *        Class:  Ponto
 *  Description:  Classe que administra um pontono R2
 * =====================================================================================
 */
class Ponto
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Ponto ();                             /* constructor */
		Ponto (float x, float y);

		/* ====================  OPERATORS     ======================================= */
		friend ostream& operator<<(ostream& out, const Ponto& p);
		const Ponto& operator=(const Ponto &P);
		bool operator==(const Ponto &P);

		/* ====================  METHODS       ======================================= */
		float distancia (const Ponto &P);
		float distancia_angular (float a, const Ponto &P)

		/* ====================  ACCESS        ======================================= */
		float get_x();
		float get_y();
		void set_x(float x);
		void set_y(float y);
		void set(float x, float y);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		float x, y;

}; /* -----  end of class  Ponto  ----- */

#endif   /* ----- #ifndef PONTO_INC  ----- */
