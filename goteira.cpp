#include "goteira.h"

#include <stdlib.h>

#include <c2d2/ator.h>

#include "jogo_atores.h"

#define INTERVALO_MIN 10
#define INTERVALO_MAX 50
#define INTERVALO_REGULAR 30

enum 
{
	GOTEIRA_PINGANDO = ATOR_PROG_INI
};

Animacao animGoteira[] ={
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	//  direita: 0
	{1, 1, {1}},
	//  esquerda: 1
	{1, 1, {4}},
	// ATOXADO_MORRENDO: 9
	{1, 1, {12}}
};

static bool AtualizaGoteira(Ator *a, unsigned int mapa);

bool CarregaGoteira()
{
	return ATOR_CarregaAtorEstatico(
		GOTEIRA, 
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animGoteira, 
		false, 
		0, 
		0, 
		&AtualizaGoteira
	);
}

static int Intervalo()
{
	return INTERVALO_MIN + (rand() % INTERVALO_MAX);
}

static bool AtualizaGoteira(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
			// Muda para o estado adequado
			ATOR_TrocaEstado(a, GOTEIRA_PINGANDO, false);
			break;

		case GOTEIRA_PINGANDO:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->temporizadores[0] = Intervalo();
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_TEMPO:
						a->temporizadores[0] = INTERVALO_REGULAR;
						ATOR_CriaAtor(GOTA, a->x, a->y, 0);
						break;
				}
			}
			break;
	}

	return true;
}