#include <stdio.h>

#include "cachoeira.h"

#include "jogo_atores.h"

Animacao animCachoeira[] ={
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	//  direita: 0
	{1, 1, {1}}	
};

static bool AtualizaCachoeira(Ator *a, unsigned int mapa);

bool CarregaCachoeira()
{
	return ATOR_CarregaAtorEstatico(
		CACHOEIRA, 
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animCachoeira, 
		false, 
		0, 
		0, 
		&AtualizaCachoeira
	);
}

static bool AtualizaCachoeira(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:			
			ATOR_TrocaEstado(a, ATOR_PROG_INI, false);			
			break;

		case ATOR_PROG_INI:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->estado.subestado = ESTADO_RODANDO;
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_FOCO_TELA:
						printf("cahcoeira\n");
						break;

					case EVT_PERDE_FOCO_TELA:
						printf("cahcoeira foi-se\n");
						break;
				}
			}
	}

	return true;
}

