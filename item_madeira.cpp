#include "item_madeira.h"

#include "jogo_atores.h"

enum 
{
	ITEM_ESPERANDO = ATOR_PROG_INI	
};

char *sonsMadeira[]={
	"audio/madeira.ogg"
};

Animacao animItemMadeira[] =
{
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	//  direita: 0
	{1, 1, {0}}	
};

static bool AtualizaItemMadeira(Ator *a, unsigned int mapa);

bool CarregaItemMadeira()
{
	return ATOR_CarregaAtorEstatico(
		ITEM_MADEIRA,
		"imagens/pau.png", 
		15, 
		32, 
		1, 
		1,
		15, 
		32, 
		animItemMadeira, 
		false, 
		sonsMadeira,
		1,
		&AtualizaItemMadeira
	);
}

bool AtualizaItemMadeira(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:			
			ATOR_TrocaEstado(a, ITEM_ESPERANDO, false);
			break;

		case ITEM_ESPERANDO:
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_FOI_PEGO:
                                            ATOR_TocaEfeito(a,0,mapa);
						return false;
				}
			}
			break;
	}

	return true;
}
