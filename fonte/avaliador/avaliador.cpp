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

#include	"avaliador.h"

	float
avaliar (	string arq_mapa, vector<int> caminho, float limite)
{
	Robo *robo1;
	Mapa mapa;
	Salas salas, salas_ant, salas_atual;
	int vertice;
	float aval_ant, aval, retornar=0, U;
	bool sair=false, visitou_todas=false, loop=true;
	unsigned int i, eh_loop;
	time_t tempo, anterior;
	Vertice inicial;
	VetorSalas vsalas;
	map <int, bool> visitou;
	map <int, bool>::iterator it_s;

    //cout << "AVALIADOR::avaliar Avaliando caminho: ";for(unsigned int i = 0; i < caminho.size(); i++){cout << caminho[i] << " ";}cout << endl;
	if(caminho.size() <= 4)
        return -1;

	inicial = mapa.carregarMapa(arq_mapa, &salas);

	robo1 = new Robo(inicial, mapa, &salas, true);
	/* Cria um controle para verificar se todas as salas foram visitadas */
	vsalas = salas.get_salas();
	for(i = 0; i < vsalas.size(); i++)

		visitou[vsalas[i]] = false;


	/* Iniciacao padrao */
	aval = 0;

	salas.set_ultima_atualizacao(time(&tempo));
	salas.atualizar(tempo);
	anterior = tempo;
	salas_atual.set_salas(salas.get_salas_completo());
    if(caminho[0] != caminho[caminho.size()-1])
    {
        loop = false;
        //sair = true;
        eh_loop = 0;
        //cout << "AVALIADOR::avaliar Não é loop\n";
    } else eh_loop = 1;
    robo1->irPara(caminho[caminho.size()-2-eh_loop]);
    while(!robo1->chegou());
    robo1->get_tempo_viagem();
    robo1->irPara(caminho[caminho.size()-1-eh_loop]);
    while(!robo1->chegou());
    robo1->get_tempo_viagem();
	do{
	//for(int vezes = 0;vezes<3;vezes++){
		aval_ant = aval;
		salas_ant.set_salas(salas_atual.get_salas_completo());
		salas.zerar_visitas();


		aval = 0;

		/* Simulando a navegação do robô no mapa */
		for(i = 0; (i < caminho.size()-eh_loop) && (!sair); i++){
			vertice = caminho[i];
			if(!salas.ehSala(vertice)) {
			    cerr << "A vertice " << vertice << " não é uma sala válida.\n";
			    getchar();
			    exit (EXIT_FAILURE);
			}


			robo1->irPara(vertice);
			while(!robo1->chegou());
			tempo += robo1->get_tempo_viagem();
			U = salas.atualizar(tempo);

			if(aval < U)
				aval = U;

            if((aval > limite))// && (aval_ant > limite))
            {
                sair = true;
            }

			tempo += robo1->visitar_sala();

			visitou[vertice] = true;

			//cout << "AVAL# TEMPO DE VISITA DA SALA!!!!!\n";


			//salas.imprimir();
            //cout << "AVALIADOR::avaliar aval=" << aval << "\tLimite=" << limite<<endl;//getchar();


			salas_atual.set_salas(salas.get_salas_completo());
			//salas.visitar(vertice);
		}
		/* Fim da simulação */


		/* Verificando se o robô visitou todas as salas do mapa */
		if(!visitou_todas && !sair)
		{
            visitou_todas = true;
            for(it_s = visitou.begin(); (it_s != visitou.end())&&(!sair); it_s++)
            {
                if(!it_s->second) {
                    sair = true;
                    visitou_todas = false;
                    //cout << "AVALIADOR::avaliar Não visitou todas\n";
                }
            }
		}
        //salas_atual.imprimir();salas_ant.imprimir();
	}while(((salas_ant != salas_atual) || (aval != aval_ant)) && (!sair) && (loop));

	delete(robo1);

//    if(!sair)
    if(aval > limite)
    {
        retornar = 0;
    } else if(visitou_todas && loop) //Estabilizou
    {
        retornar = aval;
    }  else if(!visitou_todas || !loop)
    {
/*        if(aval == limite)
        {
            retornar =  0;
        } else*/ if(aval == 0)
        {
            retornar = -1;
        } else
        {
            retornar = -aval;
        }
    }

		/* Verificando se o caminho passado é um loop, ou seja, se começa e termina no mesmo vértice */

//            if(aval > limite) {
//                retornar = 0;
//                sair = true;
//            }

	return retornar;
}

