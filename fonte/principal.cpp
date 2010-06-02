/*
 * =====================================================================================
 *
 *       Filename:  principal.cpp
 *
 *    Description:  Rotina principal do projeto de monitoramento de ambientes internos
 *									utilizando robos moveis
 *
 *        Version:  1.0
 *        Created:  10/03/2008 01:38:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */
#include	<cstdio>
#include	<iostream>
#include	<fstream>
#include    <sstream>

using namespace std;

#include	"mapa.h"
#include	"robo.h"
#include	"ponto.h"


#define	TOTAL	10*60			/* Tempo de execucao total(m) */
#define SIMULACAO true
#define TESTES 100

	void
Sleep (int segundos)
{
	if(!SIMULACAO)
		sleep(segundos);
}


	int
main ( int argc, char *argv[] )
{
	Mapa mapa;
	Robo *robo1;
	Salas sala;
	Vertice v;
	time_t tempo, inicio, anterior, t_aux;
	int visitar_sala, algoritmo;
	map<int, float> chances; /* PENSAR NUM NOME MELHOR */
	VetorSalas v_salas;
	unsigned int i, total_P;
	float aux, U;
	ofstream arq, arq_gnu;
	vector<string> mapas_teste;
	string s_alg, s_aux;



	mapas_teste.push_back("quatro");
	mapas_teste.push_back("quatro_diff");
	mapas_teste.push_back("x");
	//mapas_teste.push_back("x2");
	mapas_teste.push_back("x_incompleto");
	//mapas_teste.push_back("x_incompleto2");
	mapas_teste.push_back("espinha");
	mapas_teste.push_back("espinha_diff");
	mapas_teste.push_back("ap");
	arq_gnu.open("/home/heitor/robo2/resultados/graficos/gnu_conf.plt", ifstream::trunc);
    arq_gnu << "set term png size 1024,768\n";


	for(unsigned int m = 0;m < mapas_teste.size();m++)
	{
        for(int alg = 0; alg <= TESTES; alg++)
        {
            if(alg == 0) {algoritmo = 3; s_alg = "3";}
            else if(alg >= 1) {stringstream out;algoritmo = 4; out << "4." << alg; s_alg = out.str();}
            else {cerr << "Erro pra selecionar algoritmos!"; exit (EXIT_FAILURE);}
            system("clear");
            v = mapa.carregarMapa("/home/heitor/robo2/mapas/" + mapas_teste[m] + ".txt", &sala);
            robo1 = new Robo(v, mapa, &sala, SIMULACAO);

            /* Iniciacao padrao */
            sala.set_ultima_atualizacao(time(&tempo)-1);
            sala.atualizar(tempo);
            inicio = tempo;
    //        sala.imprimir();
            s_aux = "/home/heitor/robo2/resultados/curvas/" + mapas_teste[m] + "_" + s_alg + "_curva.txt";
            arq.open(s_aux.c_str(), ifstream::trunc);
            if(!arq.is_open()) {
                cout << "Não foi possivel abrir " + s_aux + ".\n";getchar();
            }
            cout << mapas_teste[m] << "_" << s_alg << endl;
            anterior = tempo;/* Usado para simulacao */
            /* Fim da iniciacao padrão */

            v_salas = sala.get_salas();

            srand(time(NULL));

            /* Gerando aleatoriamente a chances de um chamado de emergência V2*/
            total_P = 0;
            for(i = 0; i < v_salas.size(); i++)
            {
                chances[v_salas[i]] = sala.get_P(sala.get_sala(v_salas[i]));
                total_P += chances[v_salas[i]];
            }

        /*	for(i = 0; i < 100; i++)
            {
                aux = rand() % v_salas.size();
                chances[v_salas[aux]]++;*/
        //		//DEBUG*/cout << "sala: " << v_salas[aux] << " %: " << chances[v_salas[aux]] << endl;getchar();
        //	}

            for(i = 0; i < v_salas.size(); i++)
            {
                chances[v_salas[i]] = chances[v_salas[i]] / total_P;
                //cout << "sala: " << v_salas[i] << " %: " << chances[v_salas[i]] << endl;
            }

            cout << "Iniciando simulacao mapa: " << mapas_teste[m] << " algoritmo: " << algoritmo << endl;
            switch(algoritmo) {
                /*-----------------------------------------------------------------------------
                 * Algoritmo 1: Estrategia greedy, vai para a sala com maior grau de urgencia
                 *-----------------------------------------------------------------------------*/
                case 1: {
        //			cout << "Algoritmo 1\n"; getchar();
                    while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
                        sala.atualizar(tempo);
                        visitar_sala = robo1->get_sala_maiorU();
        //				sala.imprimir();
                        //DEBUG*/cout << "PRINCIPAL#main: Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl;getchar();
                        t_aux = tempo;
                        robo1->irPara(sala.get_vertice(visitar_sala));
                        while(!robo1->chegou())
                        {
                            tempo += robo1->get_tempo_viagem();
                            if(t_aux < tempo - 10)
                            {
                                //Chance pra emergencia
                                cout << "ER!!\n";
                                t_aux = tempo;
                            }
                        }
        //				cout << "Diferenca: " << tempo - inicio << endl;getchar();
                        while( tempo - anterior > ATUALIZACAO) {
                            anterior += ATUALIZACAO;
                            U = sala.atualizar(anterior);
        //					cout << U; getchar();
                            arq << anterior - inicio << "\t" << U << endl;
                        }
        //				if(!SIMULACAO)
        //					sleep(VISITAR_SALA);
        //				else
        //					tempo += VISITAR_SALA;
        //				sala.visitar(visitar_sala);

                        tempo += robo1->visitar_sala();
                        //DEBUG*/cout << "PRINCIPAL:main\n";
                        sala.imprimir();
                        //DEBUG*/getchar();
        //				tempo += VISITAR_SALA;
        //				sala.imprimir();
        //				cout << "Tempo total: " << tempo - inicio << endl;
                    }
                };break;
        //		/*-----------------------------------------------------------------------------
        //		 * Algoritmo 2: Estrategia greedy, vai para a sala com maior grau de urgencia
        //		 *							visitando as salas adjacentes (um vertice de distancia) ao caminho
        //		 *-----------------------------------------------------------------------------*/
        //		case 2: {
        //			ListaVertices caminho, adjacentes;
        //			ListaVertices::iterator it_c, it_a;
        //			while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
        //				visitar_sala = sala.get_maiorU();
        ////				cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl;
        //				caminho = mapa.dijkstra(robo1->get_vertice(), visitar_sala);
        //				caminho.pop_front(); /* Removendo o vertice atual do caminho */
        //				for(it_c = caminho.begin(); it_c != caminho.end(); it_c++) {
        //					adjacentes = mapa.verticesAdjacentes(robo1->get_vertice()); /* Verifica se existe salas adjacentes ao vertice atual */
        //					for(it_a = adjacentes.begin(); it_a != adjacentes.end(); it_a++) {
        //						if(sala.existeSala(*it_a)) {
        ////							cout << "Visitando sala adjacente " << *it_a << endl;
        //							robo1->irPara(*it_a); /* Visita todas as salas adjacentes ao vertice atual */
        //							sala.visitar(*it_a);
        //						}
        //					}
        //					robo1->irPara(*it_c);
        //				}
        //				while( tempo - anterior > ATUALIZACAO) {
        //					anterior += ATUALIZACAO;
        //					U = sala.atualizar(anterior);
        //					arq << anterior - inicio << "\t" << U << endl;
        //				}
        //				sala.visitar(visitar_sala);
        //				tempo += VISITAR_SALA;
        ////				sala.imprimir();
        ////				cout << "Tempo total: " << tempo - inicio << endl;
        //			}
        //		};break;
                /*-----------------------------------------------------------------------------
                 * Algoritmo 3: Segue um caminho pre definido
                 *-----------------------------------------------------------------------------*/
                case 3: {
                    ListaVertices loop;
                    ListaVertices::iterator it_l;
                    int sala_loop;
                    ifstream arq_loop;
                    //time_t tempo_ER = tempo, t_simu;

                    s_aux  = "/home/heitor/robo2/resultados/loops/" + mapas_teste[m] + "_loop.txt";
                    arq_loop.open(s_aux.c_str());
                    if(!arq_loop.is_open()) {
                        cout << "Não foi possível abrir \'" + s_aux + "'.\n";getchar();
                        arq.close();
                        continue;
                    }
                    cout << s_aux << endl;
        //			arq_loop.open(argv[1]);

                    arq_loop >> sala_loop;
                    while(!arq_loop.eof())
                    {
                        loop.push_back(sala_loop);
                        arq_loop >> sala_loop;
                    }
                    arq_loop.close();

                    it_l = loop.begin();

                    while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
//                        cout << "Faltam " << TOTAL * 60 - (tempo - inicio) << "s\n";
                        visitar_sala = *it_l;
        /* MODO BLOQUEANTE */
        //				tempo += robo1->irPara(sala.get_vertice(visitar_sala));
        /* MODO NAO BLOQUEANTE */
                        robo1->irPara(visitar_sala);
                        while(!robo1->chegou())
                        {
                            tempo += robo1->get_tempo_viagem();
/*                            if(t_aux < tempo - 10)
                            {
                                //Chance pra emergencia
                                cout << "ER!!\n";
                                t_aux = tempo;
                            }*/
                        }

        /*				while(!robo1->chegou(mapa.get_ponto(sala.get_vertice(visitar_sala))) && t_simu > 0)
                        {
                            if(SIMULACAO)
                            {
                                t_simu--;
                                tempo++;
                            } else {
                                time(&tempo);
                            }*/
                            /* Gerador aleatorio de emergencia */
        /*					while( tempo - tempo_ER > 60 )
        					{
                                tempo_ER+=60;
                                for(i = 0; i < v_salas.size(); i++)
                                {
                                    aux = rand() % 100;
        //							cout << "sala " << v_salas[i] << " " << chances[v_salas[i]] << "% " << aux << "%\n";
                                    if(chances[v_salas[i]] >= aux)//rand() % 100)
                                    {
                                        cout << "Emergencia na sala: " << v_salas[i] << endl;
                                        robo1->irPara(sala.get_vertice(v_salas[i]));
                                        if(SIMULACAO)
                                        {
                                            tempo += t_simu;
                                        } else {
                                            while(!robo1->chegou(mapa.get_ponto(sala.get_vertice(v_salas[i]))));
                                            time(&tempo);
                                        }
                                    }
                                }
                            }
                            robo1->irPara(sala.get_vertice(visitar_sala));
                            if(SIMULACAO)
                            {
                                tempo += t_simu;
                            } else {
                                time(&tempo);
                            }
                        }*/

                        while( (tempo - anterior >= ATUALIZACAO) && (anterior - inicio < TOTAL * 60)) {
                            anterior += ATUALIZACAO;
                            U = sala.atualizar(anterior);
                            arq << anterior - inicio << "\t" << U << endl;
                        }
                        sala.atualizar(tempo);
                        //sala.visitar(visitar_sala);
        //				tempo += VISITAR_SALA;
                        //cout << "Visitando sala: " << visitar_sala << endl;
                        tempo += robo1->visitar_sala();
                        if(++it_l == loop.end())
                            it_l = loop.begin();


                    }
                        while( (tempo - anterior >= ATUALIZACAO) && (anterior - inicio < TOTAL * 60)) {
                            anterior += ATUALIZACAO;
                            U = sala.atualizar(anterior);
                            //if(anterior - inicio >= 36000)getchar();
                            arq << anterior - inicio << "\t" << U << endl;
                            //sala.imprimir();getchar();
                        }
                };break;

                /*-----------------------------------------------------------------------------
                 * Algoritmo 4: Prioridades dinamicas
                 *-----------------------------------------------------------------------------*/
                case 4: {
                    time_t tempo_ER;
                    bool sair = false;
//                    Salas total_P_incrementado;



        //			getchar();
                    sala.zerar_prioridades();
                    sala.usar_prioridades_normalizadas(true);
//                    total_P_incrementado.set_salas(sala.get_salas_completo());
                    tempo_ER = tempo;
                    while(!sair)
                                for(i = 0; i < v_salas.size(); i++)
                                {
                                    aux = (float)(rand() % 10000)/10000;
        							//cout << "sala " << v_salas[i] << " " << chances[v_salas[i]] << "% " << aux << "%\n";
                                    if(chances[v_salas[i]] >= aux)//rand() % 100)
                                    {
                                        sala.incrementar_prioridade(sala.get_sala(v_salas[i]));
                                        //total_P_incrementado.incrementar_prioridade(v_salas[i]);
                                        sair = true;
                                        break;

        //								cout << "!!\n";
                                    }
                                }
            sala.set_ultima_atualizacao(time(&tempo)-1);
            sala.atualizar(tempo);
                    while(tempo - inicio < TOTAL * 60) { /* rodar por TOTAL minutos */
//                        cout << "Faltam " << TOTAL * 60 - (tempo - inicio) << "s\n";

                        do {

                            while( tempo - tempo_ER >= 60 ) /* USAR DEFINE */
                            {
                                tempo_ER+=60;
                                for(i = 0; i < v_salas.size(); i++)
                                {
                                    aux = (float)(rand() % 10000)/10000;
        //							cout << "sala " << v_salas[i] << " " << chances[v_salas[i]] << "% " << aux << "%\n";
                                    if(chances[v_salas[i]] >= aux)//rand() % 100)
                                    {
                                        sala.incrementar_prioridade(sala.get_sala(v_salas[i]));
                                        //total_P_incrementado.incrementar_prioridade(v_salas[i]);

        //								cout << "!!\n";
                                    }
                                }
                            }

        //					tempo++;
                            sala.atualizar(tempo);
                            //sala.imprimir();//getchar();
                            visitar_sala = robo1->get_sala_maiorU();
        //					cout << "Tempo total: " << tempo - tempo_ER << endl;


                        }while (visitar_sala == -1);


    //                    total_P_incrementado.imprimir();
        //				getchar();
    //                    cout << "Indo para sala " << visitar_sala << " vertice " << sala.get_vertice(visitar_sala)<< endl; //getchar();
        /* MODO BLOQUEANTE */
        //				tempo += robo1->irPara(sala.get_vertice(visitar_sala));
        /* MODO NAO BLOQUEANTE */
                        robo1->irPara(sala.get_vertice(visitar_sala));
                        while(!robo1->chegou())
                        {
                            tempo += robo1->get_tempo_viagem();
                            if(t_aux < tempo - 10)
                            {
                                //Chance pra emergencia
                                cout << "ER!!\n";
                                t_aux = tempo;
                            }
                        }
        //				time(&tempo);
    //                    cout << "Tempo: " << tempo - inicio << endl;
                        while( (tempo - anterior >= ATUALIZACAO) && (anterior - inicio < TOTAL * 60)) {
                            anterior += ATUALIZACAO;
                            U = sala.atualizar(anterior);
                            arq << anterior - inicio << "\t" << U << endl;
                            //sala.imprimir();getchar();
                        }

                        //cout << "Visitando sala: " << visitar_sala << endl;
                        tempo += robo1->visitar_sala();
                        sala.atualizar(tempo);
    //                    sala.imprimir();

        //				Sleep(VISITAR_SALA);
        //				tempo += VISITAR_SALA;
                        //getchar();
                    }
                        while( (tempo - anterior >= ATUALIZACAO) && (anterior - inicio < TOTAL * 60)) {
                            anterior += ATUALIZACAO;
                            U = sala.atualizar(anterior);
                            //if(anterior - inicio >= 36000)getchar();
                            arq << anterior - inicio << "\t" << U << endl;
                            //sala.imprimir();getchar();
                        }
                };break;
            }
            arq.close();
            //sala.imprimir();getchar();
            sala.salvar("/home/heitor/robo2/resultados/salas/" + mapas_teste[m] + "_" + s_alg + "_salas.txt");
        }
        arq_gnu << "set output '/home/heitor/robo2/resultados/graficos/" << mapas_teste[m] << ".png' ; ";
        arq_gnu << "plot '/home/heitor/robo2/resultados/curvas/" << mapas_teste[m] << "_3_curva.txt' with lines, ";
        arq_gnu <<      "'/home/heitor/robo2/resultados/curvas/" << mapas_teste[m] << "_4_curva.txt' with lines\n";

        //s_aux = "/home/heitor/robo2/resultados/curvas/" + mapas_teste[m] + "_4_curva.txt";
        //arq.open(s_aux.c_str(), ifstream::trunc);
        //for(int i = 0; i < TESTES; i++)
        //{
        //}
	}
	arq_gnu.close();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
