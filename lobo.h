#ifndef LOBO_H
#define LOBO_H

#include <c2d2/ator.h>

//#define VANDAB	3
//#define VPULO   1000


// Enumeração dos estados da atriz do jogo
enum 
{
	LOBO_ANDANDO=ATOR_PROG_INI, 
	LOBO_MORRENDO
};

bool CarregaLobo();


bool AtualizaLobo(Ator *a, unsigned int mapa);

#endif
