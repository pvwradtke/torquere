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
	MARCA_BOLA_DIREITA = C2D2M_PROG, 
	MARCA_BOLA_ESQUERDA,
	MARCA_LOBO,
	MARCA_RATO,
	MARCA_CORUJA,
	MARCA_MORCEGO
};

#endif
