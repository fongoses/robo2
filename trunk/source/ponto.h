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
		Ponto (double x, double y);

		/* ====================  OPERATORS     ======================================= */
		friend ostream& operator<<(ostream& out, const Ponto& p);
		const Ponto& operator=(const Ponto &P);
		bool operator==(const Ponto &P);

		/* ====================  METHODS       ======================================= */
		double distancia (const Ponto &P);

		/* ====================  ACCESS        ======================================= */
		double get_x();
		double get_y();
		void set_x(double x);
		void set_y(double y);
		void set(double x, double y);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
		double x, y;

}; /* -----  end of class  Ponto  ----- */

#endif   /* ----- #ifndef PONTO_INC  ----- */
