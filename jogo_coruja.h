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
// A fun��o para fazer a l�gica da atriz
bool AtualizaCoruja(Ator *a, unsigned int mapa);

// A ação quando bate no marcador que limita o movimento
 bool AcaoCorujaFimDireitaEsquerda(Ator* a, unsigned int mapa, Evento *evt);
// A ação de eventos de tempo
 bool AcaoCorujaTemporizador(Ator* a, unsigned int mapa, Evento *evt);
// A ação de evento de visualização do jogador
 bool AcaoCorujaProximaJogador(Ator* a, unsigned int mapa, Evento *evt);
// A ação de evento da tochada
 bool AcaoCorujatochada(Ator* a, unsigned int mapa, Evento *evt);

 bool AcaoCorujaAmanheceu(Ator* a, unsigned int mapa, Evento *evt);
 bool AcaoCorujaAnoiteceu(Ator* a, unsigned int mapa, Evento *evt);


#endif
