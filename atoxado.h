#ifndef ATOXADO_H
#define ATOXADO_H

#include <c2d2/ator.h>

#define VANDA	4
#define VPULO   1000


// Enumeração dos estados da atriz do jogo
enum 
{
	ATOXADO_INICIO=ATOR_PROG_INI, 
	ATOXADO_PARADO, 
	ATOXADO_ANDANDO, 
	ATOXADO_PULANDO,
	ATOXADO_CAINDO, 
	ATOXADO_VITORIA, 
	ATOXADO_MORRENDO, 
	ATOXADO_MORREU
};

bool CarregaAtoxado();

int GetEnergiaX(Ator *a);
int GetEnergiaY(Ator *a);

#endif
