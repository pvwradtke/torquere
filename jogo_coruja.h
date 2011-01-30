#ifndef JOGO_CORUJA_H
#define JOGO_CORUJA_H

#include <c2d2/ator.h>

//#define VANDAB	3
//#define VPULO   1000


// Enumera��o dos estados da atriz do jogo
enum {CORUJA_DESLOCANDO=ATOR_PROG_INI, CORUJA_ARMADA, CORUJA_ATACANDO, CORUJA_ESCONDIDA, CORUJA_ESTADOS};

// A fun��o que carrega o personagem atriz (pra facilitar).
//
bool JOGO_CarregaCoruja();



#endif
