#ifndef JOGO_ATORES_H
#define JOGO_ATORES_H

#include <c2d2/chien2d2mapa.h>
#include <c2d2/ator.h>

typedef bool (*acao)(Ator* a, unsigned int mapa, Evento *evt);

// A enumera��o com o tipo dos personagens
enum 
{ 
	ATOXADO, 
	BOLA,
	GOTEIRA,
	LOBO,
	RATO,
	CORUJA,
	MORCEGO,	
	GOTA,
	ITEM_MADEIRA
};

// A enumera��o das marcas

enum 
{
	MARCA_MADEIRA = C2D2M_PROG,
	MARCA_GOTA,
    MARCA_CACHOEIRA,
	MARCA_LOBO,
	MARCA_RATO,
	MARCA_CORUJA,
	MARCA_MORCEGO,
    MARCA_INIMIGO3,
    MARCA_FIMDIREITA,
    MARCA_FIMESQUERDA,
    MARCA_BOLA_DIREITA,
    MARCA_BOLA_ESQUERDA,	
};

enum 
{
	EVT_COLIDIU_FIM_DIREITA = EVT_JOGO_PROG,
	EVT_COLIDIU_FIM_ESQUERDA,
	EVT_PROXIMO_JOGADOR,
    EVT_TOCHADA,
	EVT_PEGA_MADEIRA,
	EVT_FOI_PEGO,
	EVT_MAX
};

#endif
