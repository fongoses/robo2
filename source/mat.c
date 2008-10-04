#include <stdlib.h>
#include <stdio.h>
#include "matriz_esparsa.h"


//CelulaEsparsa *raiz = NULL; //inicio da matriz esparsa
//CelulaEsparsa *linha = NULL;
//CelulaEsparsa *coluna = NULL;

void MatrizEsparsa::imprimir_matriz_esp()
{
  CelulaEsparsa *linha, *coluna;

/*	for(int l = 0; l < total_linhas; l++) {
		linha = &raiz->getProxLinha[l];
    printf("** Linha %2d **\n", linha->l);
		while(linha != NULL) {			
      imprimir_celula(*linha);getchar();
			printf("X\n");
			linha = linha->getProxColuna;
		}
	}*/

//			if(total_colunas > 21) {printf("a");imprimir_celula(raiz->getProxColuna[21]);getchar();}
//	linha = raiz->getProxLinha;
  linha = &raiz->getProxLinha[1];
	while(linha != NULL)
  {
    printf("** Linha %2d **\n", linha->l);
//      imprimir_celula(*linha);getchar();
  
    coluna = linha;
    while(coluna != NULL)
    {
//			if(total_colunas > 21) {printf("b");imprimir_celula(raiz->getProxColuna[21]);getchar();}
			if(coluna->c * coluna->l != 0) {
				imprimir_celula(*coluna);getchar();
			}
//      printf("[%2d, %2d] = %5.2f\t", coluna->l, coluna->c, coluna->valor);
      coluna = coluna->getProxColuna;
    }
    printf("\n");
    linha = linha->getProxLinha;
  }
	printf("FIM\n");
}

CelulaEsparsa *MatrizEsparsa::get_raiz() {
	return(raiz);
}

CelulaEsparsa *MatrizEsparsa::get_linha(int l) {
  return(&raiz->getProxLinha[l]);
}

void MatrizEsparsa::imprimir_linha(int l) {
  CelulaEsparsa *celula;

  celula = get_linha(l);
  while(celula != NULL) {
    printf("\n");
  }
}

CelulaEsparsa *MatrizEsparsa::get_celula(int l, int c) {
  CelulaEsparsa *celula; //ponteiro para navegar pela matriz

//  celula = &raiz[l];
//  celula = raiz;
//printf("CELULA %i, %i\n", c, l);

//  while((celula->getProxLinha != NULL) && (celula->getProxLinha->l <= l))//Localiza a linha desejada
//  {
//    celula = celula->getProxLinha;
//imprimir_celula(*celula);
//printf("{%i, %i}\n", celula->c, celula->l);
//  }

	celula = &raiz->getProxLinha[l];

//imprimir_celula(*celula);getchar();
  while((celula->getProxColuna != NULL) && (celula->getProxColuna->c <= c))//Localiza a coluna desejada
  {
    celula = celula->getProxColuna;
//imprimir_celula(*celula);getchar();
//printf("{%i, %i}\n", celula->c, celula->l);
  }

  if((celula->c == c) && (celula->l == l)) {
//printf("ACHEI!\n");
    return(celula);
  } else {
    fprintf(stderr, "Celula [%d, %d] não encontrada\n", l, c);
    return(celula);
  }  
}

float MatrizEsparsa::get_valor(int l, int c) {
  CelulaEsparsa *celula;

  celula = get_celula(l, c);
//  printf("VALOR = %.2f\n", celula->valor);
  return(celula->valor);
}

int *MatrizEsparsa::menor_caminho(int origem, int destino)
{
  CelulaEsparsa *linha, *coluna;

  linha = raiz->getProxLinha;

  while(linha != NULL)
  {
    coluna = linha->getProxColuna;
    while(coluna != NULL)
    {
      coluna->visitado = false;
      coluna = coluna->getProxColuna;
    }
    linha = linha->getProxLinha;
  }

  return(0);
}
  
    
