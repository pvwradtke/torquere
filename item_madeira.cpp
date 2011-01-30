#include "item_madeira.h"

#include "jogo_atores.h"

enum 
{
	ITEM_ESPERANDO = ATOR_PROG_INI	
};

Animacao animItemMadeira[] =
{
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	//  direita: 0
	{1, 1, {1}}	
};

static bool AtualizaItemMadeira(Ator *a, unsigned int mapa);

bool CarregaItemMadeira()
{
	return ATOR_CarregaAtorEstatico(
		ITEM_MADEIRA,
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animItemMadeira, 
		false, 
		0, 
		0, 
		&AtualizaItemMadeira
	);
}

bool AtualizaItemMadeira(Ator *a, unsigned int mapa)
{
	//Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:			
			ATOR_TrocaEstado(a, ITEM_ESPERANDO, false);
			break;

		case ITEM_ESPERANDO:
			break;
	}

	return true;
}
