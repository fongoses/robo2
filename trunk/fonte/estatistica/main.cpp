#include <dirent.h>
#include <cstring>
#include <iostream>
#include	<string>
#include	<vector>
#include	<cstdio>
#include    <fstream>
#include    <map>

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
    string arqnome, dir_base = "/home/heitor/robo2/resultados/curvas/", s_aux;
    size_t pos;
    unsigned int qtde, tam = 1, linhas = 0, l;
    float valor, tempo, total;


    mapas_teste.push_back("quatro");
    mapas_teste.push_back("quatro_diff");
    mapas_teste.push_back("x");
    mapas_teste.push_back("x_incompleto");
    mapas_teste.push_back("espinha");
    mapas_teste.push_back("espinha_diff");
    mapas_teste.push_back("ap");


    for(unsigned int m = 0; m < mapas_teste.size(); m++)
    {
        s_aux = dir_base + mapas_teste[m] + "_4_curva.txt";
        saida.open(s_aux.c_str(), ifstream::trunc);
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
                cout << dir->d_name;
                if (pos == 0){
                    cout << " SIM" << endl;
                    arqnome = dir_base + arqnome;
                    arquivo.open(arqnome.c_str());
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
                }else {cout << " NÃO" << endl;}
//                arquivos[0] >> s_aux;
                //cout << s_aux;
            }
        }
        for(unsigned int l = 0; l < linhas ; l++)
        {
            saida << tempos[l] << "\t" << valores[l]/qtde << endl;
        }
        cout << "Achado " << qtde << " arquivo(s) do mapa " + mapas_teste[m] << endl;getchar();
        closedir( d );
    }
    return 0;
}
