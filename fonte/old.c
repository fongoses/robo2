#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>
#include <libplayerc++/playerc++.h>
#include <time.h>
#include <ncurses.h>

#include "funcoes.h"
#include "robo.h"
//#include "matriz_esparsa.h"

//#include <sys/types.h>
//#include <argz.h>
//#include <string.h>
//#include <errno.h>
//#include <termios.h>


int device_index = 0;

void Robo::calcular(float x, float y, float *dist, int *angulo) {
  float dx, dy, hipotenusa, seno, cosseno, angulo_rad;

  player_client.Read();

  dx = x - position.GetXPos();
  dy = y - position.GetYPos();

  hipotenusa = sqrt(dx * dx + dy * dy);

  cosseno = dx / hipotenusa;
  seno = dy / hipotenusa;


  /* Quadrantes I e II */
  if(seno >= 0) {
    angulo_rad = acos(cosseno);
  /* Quadrante III */
  } else if((seno < 0) && (cosseno < 0)){
    angulo_rad = 180 / GRAD_TO_RAD - asin(seno);
  /* Quadrante IV */
  } else {
    angulo_rad = asin(seno);
  }

  *dist = hipotenusa;
  *angulo = (int)(angulo_rad * GRAD_TO_RAD);
}

int Robo::ir_para(float x, float y, float dist_ajuste) {
  float fim_a_rad;
  int fim_a;
  float dist, vel, inclinacao_anda, y0_anda;
  float dif, dif2, vel_rot, inclinacao_rot, y0_rot;
  float metros, aux;
//  time_t aux_t, relogio;
//  bool primeira_vez = true, virando = false, muito_perto = false, virar_muito = false, meia_volta = false;
	bool sair = false;

//  mvprintw(15, 0, "Andando");refresh();

  inclinacao_anda = (MAX_VEL_ANDA / 2 - MIN_VEL_ANDA) / (MAX_DIST - MIN_DIST);
  y0_anda = MIN_VEL_ANDA - inclinacao_anda * MIN_DIST;

  inclinacao_rot = (MAX_VEL_ROT  - MIN_VEL_ROT) / (MAX_DIF - MIN_DIF);
  y0_rot = MIN_VEL_ROT - inclinacao_rot * MIN_DIF;

  indo_x = x; 
  indo_y = y;


  /* Inicializa variaveis */
    player_client.Read();
	if(dist_ajuste != 0)
		vel =	position.GetXSpeed();
	else
	  vel = 0;
  vel_rot = 0;

  do {
    player_client.Read();

    calcular(x, y, &metros, &fim_a);

    if(fim_a * fim_a == 180 * 180) {
      fim_a--;
    }

    if (fim_a > 179) {
      fim_a -= 360;
    } else if (fim_a < -179) {
      fim_a += 360;
    }

    dist = ((indo_x - position.GetXPos())*(indo_x - position.GetXPos()) +
            (indo_y - position.GetYPos())*(indo_y - position.GetYPos()));

    dif = (fim_a - position.GetYaw() * GRAD_TO_RAD)*(fim_a - position.GetYaw() * GRAD_TO_RAD);
    dif2 = 360*360 - dif;

//    if(dist > MAX_DIST) {
//      vel = MAX_VEL_ANDA;
//    } else if (dist > MIN_DIST) {
//      vel = MIN_VEL_ANDA;
//    }

//    if((laser[ 60] < MIN_DIST*2) || (laser[120] < MIN_DIST*2))
//    {
//      vel = 0;
//    }

/* calcula velocidade de rotacao em funcao da distancia do angulo destino */
    if(MENOR(dif, dif2) > MAX_DIF) {
      vel_rot = MAX_VEL_ROT;
    } else if (MENOR(dif, dif2) > DIF_ERRO) {
      vel_rot = MIN_VEL_ROT;
    } else {
      vel_rot = 0;
    }
/*SEM DESVIO*/
    if(MENOR(dif, dif2) > 15*15)
			vel = 0;
		else
			vel += 0.01;
	/*FIM*/

    fim_a_rad = fim_a / GRAD_TO_RAD;

/* Verifica para qual lado é mais curto virar */
    if(((dif < dif2) && (fim_a_rad < position.GetYaw())) ||
       ((dif > dif2) && (fim_a_rad > position.GetYaw()))) {
      vel_rot = -vel_rot;
    } 
    
    aux = 0;
    
//    if(laser[  0] < MAX_DIST) aux += (MAX_DIST - laser[  0]) * 5;
//    if(laser[ 30] < MAX_DIST) aux += (MAX_DIST - laser[ 30]) * 3;
//    if(laser[ 60] < MAX_DIST) aux += (MAX_DIST - laser[ 60]) * 1;
//    if(laser[120] < MAX_DIST) aux -= (MAX_DIST - laser[120]) * 1;
//    if(laser[150] < MAX_DIST) aux -= (MAX_DIST - laser[150]) * 3;
//    if(laser[179] < MAX_DIST) aux -= (MAX_DIST - laser[179]) * 5;

//    if((laser[ 60] > MAX_DIST) && (laser[120] > MAX_DIST))
//    {
//      vel *= 1.5;
//    }

//    vel_rot += aux / 15;
    position.SetSpeed(vel, vel_rot);

	  imprimir_dados();
//		printw("%f > %f", dist, DIST_ERRO + dist_ajuste);

  } while ((!sair) && (dist > DIST_ERRO + dist_ajuste*0));

  position.SetSpeed(0, 0);
//  mvprintw(15, 0, "Parado ");refresh();
//  printf("Foi para (%.1f, %.1f). Ajuste = %5.2f\n", x, y, dist_ajuste);getchar();

  return !sair;
}

int Robo::ir_para(float x, float y) {
  return ir_para(x, y, 0);
}

int Robo::ir_para(int vertice){
  return ir_para(vertice, 0);
}

int Robo::ir_para(int vertice, float dist_ajuste){
//  printf("Indo para vertice %d\n", vertice);
	indo_vertice = vertice;
  bool sair = !ir_para(mapa->vertices[vertice].x, mapa->vertices[vertice].y, dist_ajuste);
  set_vertice(vertice);
  return !sair;
}

void Robo::imprimir_dados(){
	int l = 0, c;
  mvprintw(l++, 0, "*********************************************************");
  mvprintw(l++, 0, "Posicao: [%6.2f, %6.2f, %6.2f]", position.GetXPos(), position.GetYPos(), position.GetYaw() * GRAD_TO_RAD);
	mvprintw(l++, 0, "Destino: [%6.2f, %6.2f]", indo_x, indo_y);
  mvprintw(l++, 0, "Velocidade: %6.3f Rotacao: %6.3f", position.GetXSpeed(), position.GetYawSpeed());
	mvprintw(l++, 0, "Caminho: ");
	for(c = 1; c < caminho[0] + 1; c++ ){
		if(caminho[c] == indo_vertice){
			attron(A_BOLD);
			printw(" %i", caminho[c]);
			attroff(A_BOLD);
		} else {
			printw(" %i", caminho[c]);
		}
	}
	printw("\n");
	mvprintw(l++, 0, "*********************************************************\n");

	
	
	if(getch() == 27) {
		endwin();
		exit(0);
	}
	refresh();
}

void Robo::teste()
{
//    position.SetSpeed(1, 0);
  position.ResetOdometry();
  position.SetSpeed(1, 0.01);
  while(1)
  {
    player_client.Read();
  }
}

int **Robo::todos_os_caminhos(int destino, float **pesos) {
  return(mapa->todos_os_caminhos(get_vertice(), destino, pesos));
}

int *Robo::menor_caminho(int destino) {
  float peso;
//  caminho = mapa->dijkstra(get_vertice(), destino, &peso);
  caminho = mapa->menor_caminho(get_vertice(), destino, &peso);
  return(caminho);
}
int *Robo::menor_caminho(int destino, float *peso) {
  caminho = mapa->menor_caminho(get_vertice(), destino, peso);
  return(caminho);
}

int Robo::get_vertice() {
  return(vertice);
}

