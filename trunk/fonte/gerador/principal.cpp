/*
 * =====================================================================================
 *
 *       Filename:  principal.cpp
 *
 *    Description:  Programa para gerar rotas e encontrar a melhor.
 *
 *        Version:  1.0
 *        Created:  05/11/2009 10:25:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	<cstring>
#include	<cstdlib>
#include    <cstdio>
#include	<iostream>
#include    <fstream>

#include	"gerador.h"

	int
main ( int argc, char *argv[])
{
	string arq_mapa, s_aux;
	int i;
	list<Agente> melhores;
	list<Agente>::iterator it;
	Agente melhor;
	vector<string> mapas_teste;
    float inicio, total;
	ofstream arq;

	mapas_teste.push_back("x2");

/*	mapas_teste.push_back("quatro");
	mapas_teste.push_back("quatro_diff");
	mapas_teste.push_back("x");
	mapas_teste.push_back("x2");
	mapas_teste.push_back("x_incompleto");
	mapas_teste.push_back("x_incompleto2");
	mapas_teste.push_back("espinha");
	mapas_teste.push_back("espinha_diff");
	mapas_teste.push_back("ap");*/
//	cout << argv[0] << " " << argv[1] << endl; getchar();


	if(argc != 2){
		cout << "GERADOR Digite o mapa: ";
//		cin >> arq;
		arq_mapa = "../../mapas/tres.txt";

		argc = 2;
		argv = (char **)malloc(sizeof(char *) * 2);
		for(i = 0; i < 2; i++) {
			argv[i] = (char *)malloc(sizeof(char) * 20);
		}

		strcpy(argv[0], "../../gerador_loop");
		strcpy(argv[1], arq_mapa.c_str());

		main(argc, argv);
		return EXIT_SUCCESS;
	} else {
		arq_mapa = argv[1];
	}


	arq.open("/home/heitor/robo2/resultados/gerador.log", ifstream::trunc);

    for(unsigned int m = 0; m < mapas_teste.size(); m++)
    {
//        melhores = gerar(arq_mapa);
        inicio = clock();
        melhores = gerar("/home/heitor/robo2/mapas/" + mapas_teste[m] + ".txt");
        total = (clock() - inicio)/1000000;
        arq << mapas_teste[m] << " em " << total << " segundos." << endl;
        cout << "Melhor(es) caminho(s)\n";
//        imprimir_agentes(melhores);
        melhores.sort();
        imprimir_agentes(melhores);
        salvar_loop("/home/heitor/robo2/loops/" + mapas_teste[m] + "_loop.txt", melhores);
        cout << "Avaliação: " << melhores.begin()->get_avaliacao() << endl;
        cout << "Gerou em " << total << " segundos.\n";
    }
//	for(it = melhores.begin(); it != melhores.end(); it++)
//		it->imprimir();


    arq.close();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
