#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include <ncurses.h>

#include "mapa.h"
#include "ants.h"

int *Mapa::menor_caminho_fator(int origem, int destino) {
  agente_t agente, agente2, agente_menor;
  fila_agente_t *fila = NULL; 
  celula_esp *celula;
  int *caminho_final, qtde_nos, x;
  caminho_t *aux_c;

//printf("Procurando menor caminho %i - %i\n", origem, destino);
  if(origem == destino) {
    caminho_final = (int *)malloc(sizeof(int));
    caminho_final[0] = 0;
    return(caminho_final);
  }

//  celula = (celula_esp *)malloc(sizeof(celula_esp));
  agente.noh = origem;
  agente.caminho = NULL;
  inserir_caminho(&agente.caminho, origem);
  agente.soma = 0.0;
  agente.fator = 0.0;
  inserir_agente(&fila, agente);
  while(fila != NULL) {
    agente = remove_agente(&fila);
    celula = matriz->get_linha(agente.noh);
    while(celula->prox_c != NULL) {
      celula = celula->prox_c;
      if(!no_caminho(agente, celula->c)) {
        /*Copiando e "andando" o agente */
        agente2 = copiar_agente(agente);
        agente2.soma += celula->valor;
        agente2.noh = celula->c;
        inserir_caminho(&agente2.caminho, celula->c);

        if(agente2.noh == destino) {
          agente_menor = copiar_agente(agente2);
        } else {
          inserir_agente(&fila, agente2);
        }
      }
    }
  }
  qtde_nos = 0;
  aux_c = agente_menor.caminho;
  while(aux_c != NULL) {
    aux_c = aux_c->prox;
    qtde_nos++;
  }

  caminho_final = (int *)malloc(sizeof(int) * (qtde_nos + 1));
  aux_c = agente_menor.caminho;
  caminho_final[0] = qtde_nos;
  x = 1;
  while(aux_c != NULL) {
    caminho_final[x++] = aux_c->noh;
//    printf("%i ", aux_c->noh);
    aux_c = aux_c->prox;
  }
  printf("\n");

  return(caminho_final);
}

int Mapa::extract_min(float *dist, int *ja_foi) {
	float min = INFINITO;
	int m;

	for(int i = 1; i <= total_vertices; i++) {
//		printf("(%i) %2i=%12.5f ", ja_foi[i], i, dist[i]);
		if(ja_foi[i] != 1) {
			if(min >= dist[i]) {
				min = dist[i];
				m = i;
			}
		}
	}
//		printf("min %i=%f\n", m, min);
	return(m);
}

int *Mapa::dijkstra(int origem, int destino) {
	float peso = 0;
	return(dijkstra(origem, destino, &peso));
}
			
int *Mapa::dijkstra(int origem, int destino, float *peso) {

	float *dist;
	int *path, *caminho_final, qtde_nos, v, *ja_foi, u, cont = 0, aux;
	celula_esp *cel_v;
	caminho_t *aux_c;

	dist = (float *)malloc(sizeof(float) * (total_vertices + 1));	
	path = (int *)malloc(sizeof(int) *     (total_vertices + 1));	
	ja_foi = (int *)malloc(sizeof(int) *   (total_vertices + 1));	

	for(int v = 1; v <= total_vertices; v++) {
		dist[v] = INFINITO;
		path[v] = 0;
		ja_foi[v] = 0;
	}

	dist[origem] = 0;
	while(cont <= total_vertices) {
		u = extract_min(dist, ja_foi);
		cont++;
		ja_foi[u] = 1;
		/* pra cada v adj u*/
    cel_v = matriz->get_linha(u);
    while(cel_v->prox_c != NULL) {
      cel_v = cel_v->prox_c;
			
			if((ja_foi[cel_v->c] != 1) && (dist[cel_v->c] > dist[u] + cel_v->valor)) {
				dist[cel_v->c] = dist[u] + cel_v->valor;
				path[cel_v->c] = u;
			}
		}
	}

	*peso = dist[destino];
	aux_c = NULL;
	v = destino;
	qtde_nos = 0;
	while(v != origem) {
		inserir_caminho(&aux_c, v);
		qtde_nos++;
		v = path[v];
	}
	inserir_caminho(&aux_c, origem);
	qtde_nos++;

  caminho_final = (int *)malloc(sizeof(int) * (qtde_nos + 1));
  caminho_final[0] = qtde_nos;
  v = 1;
  while(aux_c != NULL) {
    caminho_final[v++] = aux_c->noh;
    aux_c = aux_c->prox;
  }

	for(v = 1; v <= qtde_nos/2 + 1; v++) {
		aux = caminho_final[v];
		caminho_final[v] = caminho_final[qtde_nos - v + 1];
		caminho_final[qtde_nos - v + 1] = aux;
	}
  return(caminho_final);
}


int *Mapa::menor_caminho(int origem, int destino, float *peso) {
  agente_t agente, agente2, agente_menor;
  fila_agente_t *fila = NULL; 
  celula_esp *celula;
  float minimo_encontrado = INFINITO;
  int *caminho_final, qtde_nos, x;
  caminho_t *aux_c;

//printw("Procurando menor caminho (Ants)%i - %i", origem, destino);
  if(origem == destino) {
    caminho_final = (int *)malloc(sizeof(int) * 1);
    caminho_final[0] = 0;
    *peso = 0;
    return(caminho_final);
  }

//  celula = (celula_esp *)malloc(sizeof(celula_esp));
  agente.noh = origem;
  agente.caminho = NULL;
  inserir_caminho(&agente.caminho, origem);
  agente.soma = 0.0;
  inserir_agente(&fila, agente);
//	mvprintw(12, 5, "Inserindo agente da fila: %3d", agente.noh);refresh();getchar();
  while(fila != NULL) {
    agente = remove_agente(&fila);

/*		mvprintw(11, 5, "Fila:");
		aux_f = fila;
		while(aux_f != NULL) {
			printw(" %i", aux_f->agente.noh);
			aux_f = aux_f->prox;
		}printw("     ");refresh();

		mvprintw(12, 5, "Removendo agente da fila: %3d", agente.noh);
		mvprintw(13, 5, "Caminho:");
		aux_c = agente.caminho;
		while(aux_c != NULL) {
			printw(" %i", aux_c->noh);
			aux_c = aux_c->prox;
		}printw("     ");refresh();getchar();*/
    celula = matriz->get_linha(agente.noh);
    while(celula->prox_c != NULL) {
      celula = celula->prox_c;
      if((agente.soma + celula->valor < minimo_encontrado) && (!no_caminho(agente, celula->c))) {
        /*Copiando e "andando" o agente */
        agente2 = copiar_agente(agente);
        agente2.soma += celula->valor;
        agente2.noh = celula->c;
        inserir_caminho(&agente2.caminho, celula->c);

        if(agente2.noh == destino) {
          agente_menor = copiar_agente(agente2);
          minimo_encontrado = agente_menor.soma;
        } else {
          inserir_agente(&fila, agente2);
/*		mvprintw(11, 5, "Fila:");
		aux_f = fila;
		while(aux_f != NULL) {
			printw(" %i", aux_f->agente.noh);
			aux_f = aux_f->prox;
		}printw("     ");refresh();
					mvprintw(12, 5, "Inserindo agente da fila: %3d", agente2.noh);refresh();getchar();*/

        }
      }
    }
  }
  qtde_nos = 0;
  aux_c = agente_menor.caminho;
  while(aux_c != NULL) {
    aux_c = aux_c->prox;
    qtde_nos++;
  }

  caminho_final = (int *)malloc(sizeof(int) * (qtde_nos + 1));
  aux_c = agente_menor.caminho;
  caminho_final[0] = qtde_nos;
  *peso = agente_menor.soma;
  x = 1;
  while(aux_c != NULL) {
    caminho_final[x++] = aux_c->noh;
    aux_c = aux_c->prox;
  }

  return(caminho_final);
}

int **Mapa::todos_os_caminhos(int origem, int destino, float **lista_pesos) {
  agente_t agente, agente2;
  fila_agente_t *fila = NULL; 
  celula_esp *celula;
  int qtde_nos, qtde_caminhos, **lista_caminhos_final;
  caminho_t *aux_c;
  lista_caminhos_t *aux_lc, *lista_caminhos = NULL;

printf("Procurando todos os caminhos %i - %i\n", origem, destino);
  if(origem == destino) {

    lista_caminhos_final = (int **)malloc(sizeof(int*));
    lista_caminhos_final[0] = (int *)malloc(sizeof(int));
    lista_caminhos_final[0][0] = 0;
    *lista_pesos = (float *)malloc(sizeof(float));
    *lista_pesos[0] = 0;
    return(lista_caminhos_final);
  }

//  celula = (celula_esp *)malloc(sizeof(celula_esp));
  agente.noh = origem;
  agente.caminho = NULL;
  inserir_caminho(&agente.caminho, origem);
  agente.soma = 0.0;
  inserir_agente(&fila, agente);
  qtde_caminhos = 0;
  while(fila != NULL) {
    agente = remove_agente(&fila);
    celula = matriz->get_linha(agente.noh);
    while(celula->prox_c != NULL) {
      celula = celula->prox_c;
      if(!no_caminho(agente, celula->c)) {
        /*Copiando e "andando" o agente */
        agente2 = copiar_agente(agente);
        agente2.soma += celula->valor;
        agente2.noh = celula->c;
        inserir_caminho(&agente2.caminho, celula->c);

        if(agente2.noh == destino) {
          printf("caminho %d\n", qtde_caminhos++);
          novo_caminho(&lista_caminhos, agente2.caminho);
        } else {
          inserir_agente(&fila, agente2);
        }
      }
    }
  }

  qtde_caminhos = 0;
  aux_lc = lista_caminhos;
  while(aux_lc != NULL) {
    aux_lc = aux_lc->prox;
    qtde_caminhos++;
  }

  lista_caminhos_final = (int **)malloc(sizeof(int *) * (qtde_caminhos + 1));
  lista_caminhos_final[0] = (int *)malloc(sizeof(int));
  lista_caminhos_final[0][0] = qtde_caminhos;
  *lista_pesos = (float *)malloc(sizeof(float) * (qtde_caminhos + 1));
  *lista_pesos [0] = 0;
  aux_lc = lista_caminhos;
  for(int x = 1; x <= qtde_caminhos; x++) {
//printf("caminho %d\n", x);

    qtde_nos = 0;
    aux_c = aux_lc->caminho;
    while(aux_c != NULL) {
      aux_c = aux_c->prox;
      qtde_nos++;
    }
    lista_caminhos_final[x] = (int *)malloc(sizeof(int) * (qtde_nos + 1));
    aux_c = aux_lc->caminho;
    lista_caminhos_final[x][0] = qtde_nos;
    *lista_pesos[x] = -1;//Calcular pesos 
    for(int y = 1; y <= qtde_nos; y++) {
      lista_caminhos_final[x][y] = aux_c->noh;
//    printf("%i ", aux_c->noh);
      aux_c = aux_c->prox;
    }
//  printf("\n");
  aux_lc = aux_lc->prox;
  }
//  getchar();

  return(lista_caminhos_final);
}

