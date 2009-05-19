/*
 * =====================================================================================
 *
 *       Filename:  avaliador.cpp
 *
 *    Description:  Programa para avaliar o desempenho das estratégias
 *
 *        Version:  1.0
 *        Created:  05/05/2009 02:41:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor L. Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC, USP - São Carlos - SP
 *
 * =====================================================================================
 */

#include	"../mapa.h"
#include	"../robo.h"

	int
main ( int argc, char *argv[] )
{
	Robo *robo1;
	Mapa mapa;
	Salas sala;
	Vertice v;
	int vertice, U, aval_ant, aval, i;
	time_t tempo, anterior;
	string arq_mapa, arq_rota;
	ListaVertices rota;
	vector<int> caminho;
	ifstream file;


	
	if(argc != 3){
		cout << "AVALIADOR Digite o mapa: ";
//		cin >> arq;
		arq_mapa = "quatro.txt";
		cout << "AVALIADOR Digite a tragetoria: ";
//		cin >> arq;
		arq_rota = "rota.txt";

		argc = 3;
		argv = (char **)malloc(sizeof(char *) * 3);
		for(i = 0; i < 3; i++) {
			argv[i] = (char *)malloc(sizeof(char) * 10);
		}

		strcpy(argv[0], "avaliador.cpp");
		strcpy(argv[1], arq_mapa.c_str());
		strcpy(argv[2], arq_rota.c_str());

		aval = main(argc, argv);
		cout << "AVALIADOR Aval: " << aval << endl;
		return aval;
	} else {
		arq_mapa = argv[1];
		arq_rota = argv[2];
	}
	
	v = mapa.carregarMapa(arq_mapa, &sala);
	if(arq_rota == "rota.txt") {
		cout	<< "AVALIADOR Digite a rota: \n";
		cin >> vertice;
		while (vertice != -1){
			rota.push_back(vertice);
			cin >> vertice;
		}
	} else {
		file.open(arq_rota.c_str());
		cout << "AVALIADOR Carregando rota... ";
		if(file.is_open()) {
			file >> vertice;
			while(!file.eof()) {
				rota.push_back(vertice);
				file >> vertice;
			}
		}
	}
	cout << endl;


	robo1 = new Robo(v, mapa, true);

	/* Iniciacao padrao */
	sala.set_ultima_atualizacao(time(&tempo)-10);
	sala.atualizar(tempo);
	anterior = tempo;

	while(!rota.empty()) { /* Passando o caminho de ListaVertices (list) para vector */
		cout << rota.front() << " ";
		caminho.push_back(rota.front());
		rota.pop_front();
	}
	cout << endl;

	aval = 0;

	do{
		aval_ant = aval;
		aval = 0;
		for(unsigned int i = 0; i < caminho.size(); i++){
//			cout << "Vertice " << caminho[i] << endl;
			vertice = caminho[i];
			
			tempo += robo1->irPara(vertice);

//			cout << "tempo " << tempo - anterior << " ATU " << ATUALIZACAO << endl;getchar();
			while( tempo - anterior > ATUALIZACAO) {
				anterior += ATUALIZACAO;
				U = sala.atualizar(anterior);
//  			sala.imprimir();	getchar();
				if(aval < U)
					aval = U;
			}

			U = sala.atualizar(tempo);
//			if(aval < U)
//				aval = U;

//			cout << "Antes: " << U << endl;
//			sala.imprimir();

			sala.visitar(vertice);
//			U = sala.atualizar(tempo);
//			aval = U;

//			cout << "U: " << U << endl; 
//			sala.imprimir();			getchar();
//			tempo += VISITAR_SALA;
		}

		cout	<< "AVALIADOR Aval = " << aval << endl; //getchar();
	}while(aval_ant != aval);

//	return EXIT_SUCCESS;
	return aval;
}				/* ----------  end of function main  ---------- */
