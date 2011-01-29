#ifndef JOGO_ATORES_H
#define JOGO_ATORES_H

#include <c2d2/chien2d2mapa.h>

// A enumera��o com o tipo dos personagens
enum 
{ 
	DARKPHOENIX, 
	BOLA,
	LOBO,
	RATO,
	CORUJA,
	MORCEGO
};

// A enumera��o das marcas

enum 
{
	MARCA_MADEIRA = C2D2M_PROG,
	MARCA_GOTEIRA,
        MARCA_CACHOEIRA,
	MARCA_LOBO,
	MARCA_RATO,
	MARCA_CORUJA,
	MARCA_MORCEGO,
        MARCA_INIMIGO3,
        MARCA_FIMDIREITA,
        MARCA_FIMESQUERDA
};

#endif
