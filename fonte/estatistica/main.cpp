#include <dirent.h>
#include <cstring>
#include <iostream>
#include	<string>
#include	<vector>
#include	<cstdio>
#include    <fstream>
#include    <map>

#include "../mapa.h"

using namespace std;


    int
main ( int argc, char *argv[] )
{
    DIR           *d;
    struct dirent *dir;
    vector<string> mapas_teste;
    vector<vector<float> > dados;
    vector<int> tempos;
    vector<float> valores;
    ofstream saida;
    ifstream arquivo;
    string arqnome, dir_base, s_aux;
    size_t pos;
    unsigned int qtde, tam = 1, linhas = 0, l;
    int P, visitas, s;
    float valor, tempo, total;
    Salas sala;
    Mapa mapa;
    char buff[256];
	MapaSala::iterator it_s;
	int total_visitas;
	int total_P;


    mapas_teste.push_back("quatro");
    mapas_teste.push_back("quatro_diff");
    mapas_teste.push_back("x");
    mapas_teste.push_back("x_incompleto");
    mapas_teste.push_back("espinha");
    mapas_teste.push_back("espinha_diff");
    mapas_teste.push_back("ap");

    dir_base = "/home/heitor/robo2/resultados/salas/";
    for(unsigned int m = 0; m < mapas_teste.size(); m++)
    {
        d = opendir( dir_base.c_str() );
        if( d == NULL ) {
            return 1;
        }
        mapa.carregarMapa("/home/heitor/robo2/mapas/" + mapas_teste[m] + ".txt", &sala);
        qtde = 0;
        sala.zerar_prioridades();
        sala.zerar_visitas();
        while( ( dir = readdir( d ) ) ) {
            if( strcmp( dir->d_name, "." ) == 0 ||
                strcmp( dir->d_name, ".." ) == 0 ) {
            continue;
            }
            if( dir->d_type != DT_DIR ) {
                arqnome = dir->d_name;
                pos = arqnome.find(mapas_teste[m] + "_4.");
                //cout << dir->d_name;
                if (pos == 0){
                  //  cout << " SIM" << endl;
                    arqnome = dir_base + arqnome;
                    cout << arqnome << endl;
                    arquivo.open(arqnome.c_str());
                    if(!arquivo.is_open()) {cerr << "Problemas para abrir " << arqnome << endl;}
                    arquivo.getline(buff, 256);
                    sscanf(buff, "%d %*s %*s %*s %*d  %*s %*s %d %*s %*s %d", &s, &P, &visitas);


                    while(!arquivo.eof())
                    {
                        sala.set_P(s, sala.get_P(s) + P);
                        sala.set_visitas(s, sala.get_visitas(s) + visitas);

                        arquivo.getline(buff, 256);
                        sscanf(buff, "%d %*s %*s %*s %*d  %*s %*s %d %*s %*s %d", &s, &P, &visitas);
                    }

                    arquivo.close();
                    qtde++;
//                }else {cout << " NÃO" << endl;
                }
//                arquivos[0] >> s_aux;
                //cout << s_aux;
            }
        }
        if(qtde > 0) {
            total_visitas = 0;
            total_P = 0;
            //sala.imprimir();

            s_aux = dir_base + mapas_teste[m] + "_4_salas.txt";
            saida.open(s_aux.c_str(), ifstream::trunc);
            if(!saida.is_open()) {cerr << "Problemas para abrir " << s_aux << endl;}
            for(it_s = sala.get_salas_completo().begin(); it_s != sala.get_salas_completo().end(); it_s++) {
                total_visitas += it_s->second.visitas;
                total_P += it_s->second.P;
            }

            for(it_s = sala.get_salas_completo().begin(); it_s != sala.get_salas_completo().end(); it_s++) {
                saida << it_s->first << " => vertice = " << it_s->second.vertice <<
                                              "\tP = " << (float)it_s->second.P / qtde<<
                                        "\tvisitas = " << (float)it_s->second.visitas / qtde<<
                                        "\tP/Pt = " << (float)it_s->second.P / total_P <<
                                        "\tv/vt = " << (float)it_s->second.visitas / total_visitas <<
                                        endl;
                /*cout << it_s->first << " => vertice = " << it_s->second.vertice <<
                                              "\tP = " << (float)it_s->second.P / qtde<<
                                              "\tU = " << it_s->second.U <<
                                        "\tvisitas = " << (float)it_s->second.visitas / qtde<<
                                        "\tP/Pt = " << (float)it_s->second.P / total_P <<
                                        "\tv/vt = " << (float)it_s->second.visitas / total_visitas <<
                                        endl;*/

            }
            saida.close();
        }

        //cout << "Achado " << qtde << " arquivo(s) do mapa " + mapas_teste[m] << endl;getchar();
        closedir( d );
    }

    dir_base = "/home/heitor/robo2/resultados/curvas/";
    for(unsigned int m = 0; m < mapas_teste.size(); m++)
    {
        d = opendir( dir_base.c_str() );
        if( d == NULL ) {
            return 1;
        }
        qtde = 0;
        while( ( dir = readdir( d ) ) ) {
            if( strcmp( dir->d_name, "." ) == 0 ||
                strcmp( dir->d_name, ".." ) == 0 ) {
            continue;
            }
            if( dir->d_type != DT_DIR ) {
                arqnome = dir->d_name;
                pos = arqnome.find(mapas_teste[m] + "_4.");
                //cout << dir->d_name;
                if (pos == 0){
                  //  cout << " SIM" << endl;
                    arqnome = dir_base + arqnome;
                    cout << arqnome << endl;
                    arquivo.open(arqnome.c_str());
                    if(!arquivo.is_open()) {cerr << "Problemas para abrir " << arqnome << endl;}
                    dados.resize(++tam);
                    arquivo >> tempo;
                    arquivo >> valor;
                    l = 0;
                    while(!arquivo.eof())
                    {
                        if(tam <= 2)
                        {
                            //dados[0].push_back(tempo);
                            tempos.push_back(tempo);
                            valores.push_back(valor);
                            linhas++;
                        } else {
                            valores[l] += valor;
                        }
                        l++;
                        //if(l >
                        //dados[tam-1].push_back(valor);
                        arquivo >> tempo;
                        arquivo >> valor;
                    }

                    arquivo.close();
                    qtde++;
//                }else {cout << " NÃO" << endl;
                }
//                arquivos[0] >> s_aux;
                //cout << s_aux;
            }
        }
        if(qtde > 0) {
            s_aux = dir_base + mapas_teste[m] + "_4_curva.txt";
            saida.open(s_aux.c_str(), ifstream::trunc);
            if(!saida.is_open()) {cerr << "Problemas para abrir " << s_aux << endl;}
            for(unsigned int l = 0; l < linhas ; l++)
            {
                saida << tempos[l] << "\t" << valores[l]/qtde << endl;
            }
            //cout << "Achado " << qtde << " arquivo(s) do mapa " + mapas_teste[m] << endl;getchar();
            saida.close();
        }
        closedir( d );
    }
    return 0;
}
