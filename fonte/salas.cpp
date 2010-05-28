/*
 * =====================================================================================
 *
 *       Filename:  salas.cpp
 *
 *    Description:  Descricao dda classe Salas
 *
 *        Version:  1.0
 *        Created:  10/08/2008 11:06:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heitor Luis Polidoro (hlp), heitor@icmc.usp.br
 *        Company:  ICMC - USP São Carlos
 *
 * =====================================================================================
 */

#include	"salas.h"

int MDC(int a, int b){
  int resto;

  while(b != 0){
    resto = a % b;
    a = b;
    b = resto;
  }

  return a;
}

/*-----------------------------------------------------------------------------
 * ====================  LIFECYCLE     =======================================
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  Sala
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Sala::Sala ()
{
}  /* -----  end of method Sala::Sala  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  Sala
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Sala::Sala ( const Sala &other )
{
}  /* -----  end of method Sala::Sala  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  ~Sala
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Sala::~Sala ()
{
}  /* -----  end of method Sala::~Sala  (destructor)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  OPERATORS     ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Sala&
Sala::operator = ( const Sala &other )
{
	if ( this != &other ) {
		vertice = other.vertice;
		P				= other.P;
		U				= other.U;
		visitas	=	other.visitas;
	}
	return *this;
}  /* -----  end of method Sala::operator =  (assignment operator)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  operator ==
 * Description:  comparative operator
 *--------------------------------------------------------------------------------------
 */
	bool
Sala::operator == (Sala &other )
{
	return ((vertice == other.vertice) &&
					(P       == other.P) &&
					(U       == other.U) &&
					(visitas == other.visitas));
}  /* -----  end of method Sala::operator ==  (comparative operator)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Sala
 *      Method:  operator !=
 * Description:  comparative operator
 *--------------------------------------------------------------------------------------
 */
	bool
Sala::operator != (Sala &other )
{
	return ((vertice != other.vertice) ||
					(P       != other.P) ||
					(U       != other.U) ||
					(visitas != other.visitas));
}  /* -----  end of method Sala::operator !=  (comparative operator)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  ACCESS        ======================================= *
 *-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/


/* ============================================================================
 *
 *                     CLASS SALA
 *
 * ============================================================================*/

/*-----------------------------------------------------------------------------
 * ====================  LIFECYCLE     =======================================
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  Salas
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Salas::Salas ()
{
	ultima_atualizacao = 0;
	normalizar = false;
	total_P = 0;
}  /* -----  end of method Salas::Salas  (constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  Salas
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Salas::Salas ( const Salas &other )
{
}  /* -----  end of method Salas::Salas  (copy constructor)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  ~Salas
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Salas::~Salas ()
{
}  /* -----  end of method Salas::~Salas  (destructor)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  OPERATORS     ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
	const Salas&
Salas::operator = ( const Salas &other )
{
	if ( this != &other ) {
		ultima_atualizacao = other.ultima_atualizacao;
//		sala = other.sala;/* NÃO FUNCIONA!!!!! */
	}
	return *this;
}  /* -----  end of method Salas::operator =  (assignment operator)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  operator ==
 * Description:  comparative operator
 *--------------------------------------------------------------------------------------
 */
	bool
Salas::operator == ( Salas &other )
{
	MapaSala::iterator it_a, it_b;

	cout	<< "==\n";
	for(it_a = sala.begin(); it_a != sala.end(); it_a++, it_b++)
		if((it_a->first != it_b->first) || (it_a->second != it_b->second))
			return false;

	return true;
}  /* -----  end of method Salas::operator ==  (comparative operator)  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  operator !=
 * Description:  comparative operator
 *--------------------------------------------------------------------------------------
 */
	bool
Salas::operator != ( Salas &other )
{
	MapaSala::iterator it_a, it_b;

	for(it_a = sala.begin(), it_b = other.sala.begin(); it_a != sala.end(); it_a++, it_b++)
		if((it_a->first != it_b->first) || (it_a->second != it_b->second))
			return true;

	return false;
}  /* -----  end of method Salas::operator !=  (comparative operator)  ----- */

/*-----------------------------------------------------------------------------
 * ====================  METHODS       ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  adicionarSala
 * Description:  Adiciona uma sala
 *--------------------------------------------------------------------------------------
 */
	void
Salas::adicionarSala ( int num, int vertice, int P )
{
	//DEBUG*/cout	<< "Adicionando sala " << num << ".\n";
	if(!existeSala(num)) {
		Sala aux;
		aux.vertice = vertice;
		aux.P = P;
		aux.U = 0;
		aux.visitas = 0;
		sala[num] = aux;
		total_P += P;
	} else {
		//DEBUG*/cout	<< "Sala " << num << " ja existe\n";
	}
	//imprimir();
	return ;
}		/* -----  end of method Salas::adicionarSala  ----- */


/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  existeSala
 * Description:  Retorna se a sala de numero num existe
 *--------------------------------------------------------------------------------------
 */
	bool
Salas::existeSala ( int num )
{
	bool resp;
	//DEBUG*/cout << "SALAS#existeSala: Verificando se existe a sala " << num << endl; getchar();
	resp = (sala.find(num) != sala.end());
	//DEBUG*/cout << "SALAS#existeSala: Existe a sala " << num << "? " << resp << endl; getchar();
	return resp;

	return sala.find(num) != sala.end();
}		/* -----  end of method Salas::existeSala  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  ehSala
 * Description:  Retorna se o vertice v é uma sala
 *--------------------------------------------------------------------------------------
 */
	bool
Salas::ehSala ( int v )
{
	bool resp;
	//DEBUG*/cout << "SALAS#ehSala: Verificando se o vertice " << v << " é uma sala.\n";getchar();
	resp = existeSala(get_sala(v));
	//DEBUG*/cout << "SALAS#ehSala: Vertice " << v << " É uma sala? " << resp << endl;getchar();
	return resp;
	return existeSala(get_sala(v));
}
/* -----  end of method Salas::ehSala  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  atualizar
 * Description:  Atualiza as urgencias das salas decorrido t segundos
 *--------------------------------------------------------------------------------------
 */
	float
Salas::atualizar ( time_t t)
{
	MapaSala::iterator it_s;
	time_t diferenca = t - ultima_atualizacao;
	ultima_atualizacao = t;
	float UTotal = 0;
//	int mdc = 1;
//	if(normalizar) mdc = normalizar_prioridades();
//	//DEBUG*/cout << "Atualizando " << diferenca << " segundos\n"; getchar();

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
        //cout << "SALAS#ATUALIZAR Sala: " << it_s->first << " U:" << it_s->second.U << " D:" << diferenca << " P:" << it_s->second.P << " Pt:" << total_P << endl;
		it_s->second.U += diferenca * ((float)it_s->second.P/total_P);
//		it_s->second.U += diferenca * (it_s->second.P/mdc);
        //cout << "SALAS#ATUALIZAR Sala: " << it_s->first << " U:" << it_s->second.U << " D:" << diferenca << " P:" << it_s->second.P << " Pt:" << total_P << endl;
		UTotal += it_s->second.U;
	}
	return UTotal;
}		/* -----  end of method Salas::atualizar  ----- */
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  visitar
 * Description:  Visita a sala s
 *--------------------------------------------------------------------------------------
 */
	void
Salas::visitar ( int s )
{
	//DEBUG */cout << "SALAS#visitar: Visitando sala: " << s << ".\n";getchar();

	sala[s].U = 0;
	sala[s].visitas++;
	return ;
}		/* -----  end of method Salas::visitar  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  imprimir
 * Description:  Imprimi as salas
 *--------------------------------------------------------------------------------------
 */
	void
Salas::imprimir ( )
{
	MapaSala::iterator it_s;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		cout << it_s->first << " => vertice = " << it_s->second.vertice <<
															"\tP = " << it_s->second.P <<
															"\tU = " << it_s->second.U <<
															"\tvisitas = "<< it_s->second.visitas << endl;

	}
	return ;
}		/* -----  end of method Salas::imprimir  ----- */

	void
Salas::salvar (string nome )
{
	ofstream arq;
	MapaSala::iterator it_s;
	int total_visitas = 0;

	arq.open(nome.c_str(), ifstream::trunc);
	if(!arq.is_open()) {
		cerr << "Problemar para abrir " << nome << ".\n";getchar();
	}

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
        total_visitas += it_s->second.visitas;
	}

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		arq << it_s->first << " => vertice = " << it_s->second.vertice <<
                                      "\tP = " << it_s->second.P <<
                                "\tvisitas = " << it_s->second.visitas <<
                                "\tP/Pt = " << (float)it_s->second.P / total_P <<
                                "\tv/vt = " << (float)it_s->second.visitas / total_visitas <<
                                endl;
		/*cout << it_s->first << " => vertice = " << it_s->second.vertice <<
                                      "\tP = " << it_s->second.P <<
                                      "\tU = " << it_s->second.U <<
                                "\tvisitas = " << it_s->second.visitas <<
                                "\tP/Pt = " << (float)it_s->second.P / total_P <<
                                "\tv/vt = " << (float)it_s->second.visitas / total_visitas <<
                                endl;*/

	}
	arq.close();
	return ;
}		/* -----  end of method Salas::imprimir  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:	 zerar_prioridades
 * Description:  Coloca a prioridades de todas as salas em 0
 *--------------------------------------------------------------------------------------
 */
	void
Salas::zerar_prioridades ( )
{
	MapaSala::iterator it_s;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		it_s->second.P = 0;
		it_s->second.U = 0;
	}
	total_P = 0;
	return ;
}		/* -----  end of method Salas::zerar_prioridades ----- */

/** @brief (one liner)
  *
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:	 zerar_visitas
 * Description:  Coloca as visitas de todas as salas em 0
 *--------------------------------------------------------------------------------------
  */
void Salas::zerar_visitas()
{
	MapaSala::iterator it_s;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		it_s->second.visitas = 0;
	}
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  incrementar_prioridade
 * Description:  Incrementa em uma unidade a prioridade da sala indicada
 *--------------------------------------------------------------------------------------
 */
	void
Salas::incrementar_prioridade (int s)
{

	sala[s].P++;
	total_P++;
//	sala[s].P+=100;

	/* PENSAR NUM MODO DE DIMINUIR AS PRIORIDADES QUANDO NAO FOREM PRIMAS */
}

  int
Salas::normalizar_prioridades()
{
	MapaSala::iterator it_s;
	int mdc = 1;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++)
	{
		if(it_s->second.P <= 1) /* Se alguma prioridade for 0 ou 1 não divide */
			return 1;
	}

	mdc = sala.begin()->second.P;

	for(it_s = sala.begin(); it_s != sala.end() && mdc > 1; it_s++)
	{
		mdc = MDC(mdc, it_s->second.P);
//		//DEBUG*/cout << "mdc = " << mdc;getchar();
	}

	if(mdc > 1)
	return mdc;
		//for(it_s = sala.begin(); it_s != sala.end(); it_s++)
//			it_s->second.P /= mdc;

	return mdc;
}		/* -----  end of method Salas::incrementar_prioridade ----- */

  void
Salas::usar_prioridades_normalizadas(bool value)
{
  normalizar = value;
}

    void
Salas::apagar_salas()
{
	ultima_atualizacao = 0;
	normalizar = false;
    sala.clear();
    total_P = 0;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  emergencia
 * Description:  Aumente bruscamente o grau de urgencia da sala indicada
 *--------------------------------------------------------------------------------------
 */
	void
Salas::emergencia (int s)
{
	MapaSala::iterator it_s;
	int mdc = 1;
	if(normalizar) mdc = normalizar_prioridades();

	sala[s].U = FATOR_ER * sala[s].P/mdc;

	return ;
}		/* -----  end of method Salas::emergencia ----- */

/*-----------------------------------------------------------------------------
 * ====================  ACCESS        ======================================= *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_salas_vertices
 * Description:  Retorna a lista dos vertices que são salas existentes
 *--------------------------------------------------------------------------------------
 */
	VetorVertices
Salas::get_salas_vertices ( )
{
	MapaSala::iterator it_s;
	VetorSalas aux;


	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		aux.push_back(it_s->second.vertice);
	}
	return aux;
}		/* -----  end of method Salas::get_salas_vertice ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_salas_
 * Description:  Retorna a lista dos vertices que são salas existentes
 *--------------------------------------------------------------------------------------
 */
	VetorVertices
Salas::get_salas( )
{
	MapaSala::iterator it_s;
	VetorSalas aux;


	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		aux.push_back(it_s->second.vertice);
	}
	return aux;
}		/* -----  end of method Salas::get_salas ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_maiorU
 * Description:  Retorna a sala com maior grau de urgencia
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_maiorU ( float *U )
{
	unsigned int s = -1;
	float maiorU = 0;
	MapaSala::iterator it_s;

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		if(it_s->second.U > maiorU) {
			s = it_s->first;
			maiorU = it_s->second.U;
		}
	}
	if(U != NULL) {
		*U = maiorU;
	}
	return s;
}		/* -----  end of method Salas::get_maiorU  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_vertice
 * Description:  Retorna o vertice da sala s
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_vertice ( int s )
{
    if (existeSala(s))
        return sala.find(s)->second.vertice;

    cerr << "Sala " << s << " não existe.\n";getchar();
    exit(EXIT_FAILURE);
}		/* -----  end of method Salas::get_vertice  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_sala
 * Description:  Retorna a sala do vertice v
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_sala ( int v )
{
	MapaSala::iterator it_s;

	//DEBUG*/cout << "SALAS#get_sala: Retornando a sala correspondente ao vertice " << v << endl;getchar();

	for(it_s = sala.begin(); it_s != sala.end(); it_s++) {
		if(it_s->second.vertice == v)
			return it_s->first;
	}
	return -1;
}
/* -----  end of method Salas::get_sala  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_P
 * Description:  Retorna a prioridade da sala s
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_P ( int s )
{
	return sala.find(s)->second.P;
}
/* -----  end of method Salas::get_P  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_P
 * Description:  Seta a prioridade da sala s
 *--------------------------------------------------------------------------------------
 */
	void
Salas::set_P ( int s , int P)
{
	sala.find(s)->second.P = P;
}
/* -----  end of method Salas::set_P  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_visitas
 * Description:  Seta as visitas da sala s
 *--------------------------------------------------------------------------------------
 */
	void
Salas::set_visitas ( int s , int visitas)
{
	sala.find(s)->second.visitas = visitas;
}
/* -----  end of method Salas::set_visitas  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  get_visitas
 * Description:  Retorna as visitas da sala s
 *--------------------------------------------------------------------------------------
 */
	int
Salas::get_visitas ( int s )
{
	return sala.find(s)->second.visitas;
}
/* -----  end of method Salas::get_P  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_ultima_atualizacao
 *--------------------------------------------------------------------------------------
 */
	void
Salas::set_ultima_atualizacao ( time_t t )
{
	ultima_atualizacao	= t;
	return ;
}		/* -----  end of method Salas::set_ultima_atualizacao  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_salas_completo
 *--------------------------------------------------------------------------------------
 */
	MapaSala
Salas::get_salas_completo()
{
	MapaSala::iterator it;
	MapaSala resp;


	for(it = sala.begin(); it != sala.end(); it++)
		resp[it->first] = it->second;

	return resp;
}		/* -----  end of method Salas::set_salas_completo  ----- */

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Salas
 *      Method:  set_salas
 *--------------------------------------------------------------------------------------
 */
	void
Salas::set_salas(MapaSala s)
{
	MapaSala::iterator it;

	for(it = s.begin(); it != s.end(); it++)
		sala[it->first] = it->second;
}		/* -----  end of method Salas::set_salas  ----- */

/*-----------------------------------------------------------------------------
 * ====================  INQUIRY       ======================================= *
 *-----------------------------------------------------------------------------*/
