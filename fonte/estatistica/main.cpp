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
    vector<int> tempos;
    vector<float> valores;
    ofstream saida;
    ifstream arquivo;
    string arqnome, dir_base, s_aux;
    size_t pos;
    unsigned int qtde, linhas = 0, l, qtde_media, qtde_media3;
    int P, visitas, s;
    float valor, tempo, media, media3;
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
                    arqnome = "rm " + arqnome;
                    system(arqnome.c_str());
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
        qtde = linhas = 0;
        tempos.clear();
        valores.clear();
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
                    arquivo >> tempo;
                    arquivo >> valor;
                    l = 0;
                    while(!arquivo.eof())
                    {
                        if(qtde == 0)
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
                    arqnome = "rm " + arqnome;
                    system(arqnome.c_str());
                    //cout << "Valores size:" << valores.size() << endl;getchar();
                }
                pos = arqnome.find(mapas_teste[m] + "_3_curva.txt");
                //cout << dir->d_name;
                if (pos == 0){
                  //  cout << " SIM" << endl;
                    arqnome = dir_base + arqnome;
                    cout << arqnome << endl;
                    arquivo.open(arqnome.c_str());
                    if(!arquivo.is_open()) {cerr << "Problemas para abrir " << arqnome << endl;}
                    arquivo >> tempo;
                    arquivo >> valor;
                    media3 = qtde_media3 = 0;
                    while(!arquivo.eof())
                    {
                        if (tempo>35000)
                        {
                            media3 += valor;
                            qtde_media3++;
                        }

                        arquivo >> tempo;
                        arquivo >> valor;
                    }

                    arquivo.close();
                }
//                arquivos[0] >> s_aux;
                //cout << s_aux;
            }
        }
        if(qtde > 0) {
            s_aux = dir_base + mapas_teste[m] + "_4_curva.txt";
            saida.open(s_aux.c_str(), ifstream::trunc);
            if(!saida.is_open()) {cerr << "Problemas para abrir " << s_aux << endl;}
            media = qtde_media = 0;
            for(unsigned int l = 0; l < linhas ; l++)
            {
                saida << tempos[l] << "\t" << valores[l]/qtde << endl;
                if (tempos[l]>35000)
                {
                    media += valores[l]/qtde;
                    qtde_media++;
                    //cout << media/qtde_media << endl; getchar();
                }
            }
            //cout << "Achado " << qtde << " arquivo(s) do mapa " + mapas_teste[m] << endl;getchar();
            saida.close();
            s_aux = dir_base + mapas_teste[m] + "_3_curva_media.txt";
            saida.open(s_aux.c_str(), ifstream::trunc);
            if(!saida.is_open()) {cerr << "Problemas para abrir " << s_aux << endl;}
            saida << media3/qtde_media3 << endl;
            saida.close();
            s_aux = dir_base + mapas_teste[m] + "_4_curva_media.txt";
            saida.open(s_aux.c_str(), ifstream::trunc);
            if(!saida.is_open()) {cerr << "Problemas para abrir " << s_aux << endl;}
            saida << media/qtde_media << endl;
            saida.close();
        }
        closedir( d );
    }
    return 0;
}
