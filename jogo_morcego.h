#ifndef JOGO_MORCEGO_H
#define JOGO_MORCEGO_H

#include <c2d2/ator.h>

//#define VANDAB	3
//#define VPULO   1000


// Enumera��o dos estados da atriz do jogo
enum {MORCEGO_DESLOCANDO=ATOR_PROG_INI, MORCEGO_ESTADOS};

// A fun��o que carrega o personagem atriz (pra facilitar).
//
bool JOGO_CarregaMorcego();
// A fun��o para fazer a l�gica da atriz
bool AtualizaMorcego(Ator *a, unsigned int mapa);

// A ação quando bate no marcador que limita o movimento
 bool AcaoMorcegoFimDireitaEsquerda(Ator* a, unsigned int mapa, Evento *evt);

#endif
