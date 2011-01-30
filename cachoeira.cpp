#include <stdio.h>
#include <c2d2/chienaudio2.h>
#include <c2d2/ator.h>

#include "cachoeira.h"
#include "jogo_atores.h"

Animacao animCachoeira[] ={
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	//  direita: 0
	{4, 5, {0, 1, 2, 3}}
};

char *sonsCachoeira[]={
	"audio/cachoeira.ogg"
};

static bool AtualizaCachoeira(Ator *a, unsigned int mapa);

bool CarregaCachoeira()
{
	return ATOR_CarregaAtorEstatico(
		CACHOEIRA, 
		"imagens/cachoeira.png",
		128,
		128,
		8,
		0,
		112,
		128,
		animCachoeira, 
		false, 
		sonsCachoeira,
		1,
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
                                                a->aux_int[0] = ATOR_TocaEfeitoLoop(a, 0, 0, -1);
						break;

					case EVT_PERDE_FOCO_TELA:
						printf("cahcoeira foi-se\n");
                                                CA2_CortaEfeito(a->aux_int[0], 1000);
						break;
				}
			}
	}

	return true;
}

