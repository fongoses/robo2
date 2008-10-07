/*
 * =====================================================================================
 *
 *       Filename:  robo.h
 *
 *    Description:  Definicao da classe Robo
 *
 *        Version:  1.0
 *        Created:  10/07/2008 01:57:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */


#include <libplayerc++/playerc++.h>

#include "mapa.h"

#define GRAD_TO_RAD 57.29577951

/* Define para Virar */
#define MAX_VEL_ROT 0.5 
#define MIN_VEL_ROT 0.1
/* MAX e MIN sao valores quadrados */
#define MAX_DIF 500
#define MIN_DIF 1
#define DIF_ERRO 0.2

/* Define para Andar */
#define MAX_VEL_ANDA 0.25
#define MIN_VEL_ANDA 0.10
/* MAX e MIN sao valores quadrados */
#define MAX_DIST 1
#define MIN_DIST 0.25

#define DIST_ERRO 0.08

//#define T_ATUALIZAR 30 //em segundos
//#define T_TOTAL 10 //em minutos
//#define T_CURVA_INDEX T_TOTAL * 60 / T_ATUALIZAR

#define HOST "localhost"
#define PORT 6665


/*
 * =====================================================================================
 *        Class:  Robo
 *  Description:  Classe que controla o robo usando a biblioteca Player
 * =====================================================================================
 */
class Robo
{
	public:

		/* ====================  LIFECYCLE     ======================================= */
		Robo ();                             /* constructor      */
		Robo ( const Robo &other );   /* copy constructor */
    Robo(float x, float y, int vertice, int t_atualizar, int t_total, Mapa *map);
		~Robo ();                            /* destructor       */

		/* ====================  OPERATORS     ======================================= */
		const Robo& operator = ( const Robo &other ); /* assignment operator */

		/* ====================  METHODS       ======================================= */
    void imprimir_dados();
    
    void calcular(float x, float y, float *dist, int *angulo);
    int ir_para(float x, float y, float dist_ajuste);
    int ir_para(float x, float y);
    int ir_para(int vertice, float dist_ajuste);
    int ir_para(int vertice);
    int ir_para_sala(int sala);
    int *menor_caminho(int destino);
    int *menor_caminho(int destino, float *peso);
    int **todos_os_caminhos(int destino, float **pesos);

		/* ====================  ACCESS        ======================================= */
    int get_vertice();
    void set_vertice(int v);

		/* ====================  INQUIRY       ======================================= */

		/* ====================  DATA MEMBERS  ======================================= */
	protected:

	private:
    Mapa *mapa;
		int indo_vertice, vertice;
		float indo_x, indo_y;
		int *caminho;

}; /* -----  end of class  Robo  ----- */

