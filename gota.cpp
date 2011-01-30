#include "gota.h"

#include <c2d2/ator.h>
#include <stdlib.h>

#include "jogo_atores.h"

#define TEMPO_CRESCIMENTO_GOTA 25

#define INTERVALO_MIN 10
#define INTERVALO_MAX 100
#define INTERVALO_REGULAR 30

enum 
{
	GOTA_PENDURADA = ATOR_PROG_INI,
	GOTA_ESCONDIDA,
	GOTA_CAINDO
};

Animacao animGota[] ={
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	//  direita: 0
	{1, 1, {1}},
	//  esquerda: 1
	{1, 1, {4}},
	// ATOXADO_MORRENDO: 9
	{1, 1, {12}}
};

char *sonsGota[]={
	"audio/pingo1.ogg",
        "audio/pingo2.ogg",
        "audio/pingo3.ogg",
        "audio/pingo4.ogg",
        "audio/pingo5.ogg",
        "audio/pingo6.ogg"
};

static bool AtualizaGota(Ator *a, unsigned int mapa);

bool CarregaGota()
{
	return ATOR_CarregaAtorEstatico(
		GOTA, 
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animGota, 
		false, 
		sonsGota,
		6,
		&AtualizaGota
	);
}

static int Intervalo()
{
	return INTERVALO_MIN + (rand() % INTERVALO_MAX);
}

static bool AtualizaGota(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
			// Muda para o estado adequado			
			a->gravidade = false;
			a->aux_real[0] = a->x;
			a->aux_real[1] = a->y;
			ATOR_TrocaEstado(a, GOTA_ESCONDIDA, false);
			break;

		case GOTA_ESCONDIDA:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->temporizadores[0] = Intervalo();
				a->estado.subestado = ESTADO_RODANDO;
				ATOR_TrocaAnimacao(a, 0);
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_TEMPO:
						ATOR_TrocaEstado(a, GOTA_PENDURADA, false);
						break;
				}
			}
			break;

		case GOTA_PENDURADA:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->temporizadores[0] = TEMPO_CRESCIMENTO_GOTA;
				a->estado.subestado = ESTADO_RODANDO;

				ATOR_TrocaAnimacao(a, 1);
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_TEMPO:
						ATOR_TrocaEstado(a, GOTA_CAINDO, false);
						break;
				}
			}
			break;

		case GOTA_CAINDO:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->gravidade = true;
				a->estado.subestado = ESTADO_RODANDO;
			}

			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_COLIDIU_PAREDE:	
					case EVT_COLIDIU_PERSONAGEM:
						a->gravidade = 0;
						a->x = a->aux_real[0];
						a->y = a->aux_real[1];
						ATOR_TrocaEstado(a, GOTA_ESCONDIDA, false);
                                                if(a->naTela)
                                                    ATOR_TocaEfeito(a, rand()%6, mapa);
						break;
				}
			}

			break;
	}

	return true;
}
