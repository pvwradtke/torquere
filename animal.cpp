#include "animal.h"

#include <stdio.h>
#include <stdlib.h>

#include "jogo_atores.h"

enum CamposAuxiliaresInt
{
	INT_FLAG_DIA
};

enum Temporizadores
{
	TEMPORIZADOR_ATAQUE,
	TEMPORIZADOR_ESCONDIDO
};

static void AtualizaDirecao(Ator *a, Evento *ev, unsigned int mapa)
{
	switch(ev->tipoEvento)
	{
		case EVT_COLIDIU_FIM_DIREITA:
			a->direcao=180;
			ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
			break;

		case EVT_COLIDIU_FIM_ESQUERDA:
			a->direcao=0;
			ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
			break;					
	}
}

static void VerificaAmanheceu(Ator *a, Evento *ev)
{
	switch(ev->tipoEvento)
	{
		case EVT_AMANHECEU:			
			ATOR_TrocaEstado(a, ANIMAL_ESCONDIDO, false);
			a->aux_int[INT_FLAG_DIA] = true;
			break;
	}
}

bool AtualizaAnimal(Ator *a, InfoAnimal *info, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
			a->aux_int[INT_FLAG_DIA] = 0;			

			// Muda para o estado adequado
			ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
			break;

		case ANIMAL_ANDANDO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				a->velocidade=info->velocidade;
				a->estado.subestado=ESTADO_RODANDO;

				if(a->direcao==0)
					ATOR_TrocaAnimacao(a, ANIM_ANDANDO_ESQUERDA);
				else
					ATOR_TrocaAnimacao(a, ANIM_ANDANDO_DIREITA);
			}

			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_SAIU_FORA_MAPA:
						ATOR_TrocaEstado(a, ATOR_ENCERRADO, false);
						break;					

					case EVT_COLIDIU_PERSONAGEM:
						ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;

					case EVT_PROXIMO_JOGADOR:
						ATOR_TrocaEstado(a, ANIMAL_PREPARA_ATAQUE, false);
						break;

					case EVT_TOCHADA:
						ATOR_TrocaEstado(a, ANIMAL_ESCONDIDO, false);
						break;					

					default:
						VerificaAmanheceu(a, &ev);
						AtualizaDirecao(a, &ev, mapa);
						break;
				}
			}
			break;

			case ANIMAL_MORRENDO:
				if(a->estado.subestado == ESTADO_INICIO)
				{
					ATOR_TrocaAnimacao(a, ANIM_MORRENDO);
					a->velocidade=0;
					a->temporizadores[0] = 60;
					a->estado.subestado = ESTADO_RODANDO;
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
							if(ev.subtipo==0)
								ATOR_TrocaEstado(a, ATOR_ENCERRADO, false);
							break;
					}
				}
				break;
			case ATOR_ENCERRADO:
				return false;		

			case ANIMAL_PREPARA_ATAQUE:
				if(a->estado.subestado==ESTADO_INICIO)
				{
					a->velocidade=0;
					a->estado.subestado=ESTADO_RODANDO;
					a->temporizadores[TEMPORIZADOR_ATAQUE] = info->tempoBote;		
                    if(info->sons > 0)
                        ATOR_TocaEfeitoTela(a, rand()%info->sons, mapa);
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
							if(ev.subtipo==TEMPORIZADOR_ATAQUE)
								ATOR_TrocaEstado(a, ANIMAL_ATACANDO, false);
							break;		

						case EVT_TOCHADA:
							ATOR_TrocaEstado(a, ANIMAL_ESCONDIDO, false);
							break;

						default:
							VerificaAmanheceu(a, &ev);
							break;
					}
				}
				break;

			case ANIMAL_ATACANDO:
				if(a->estado.subestado==ESTADO_INICIO)
				{					
					a->velocidade=info->velocidadeAtaque;
					a->estado.subestado=ESTADO_RODANDO;
					
					a->temporizadores[TEMPORIZADOR_ATAQUE] = info->tempoAtaque;					
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
						if(ev.subtipo==TEMPORIZADOR_ATAQUE)
							ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;		

						default:
							VerificaAmanheceu(a, &ev);
							AtualizaDirecao(a, &ev, mapa);
							break;
					}
				}
				break;

			case ANIMAL_ESCONDIDO:
				if(a->estado.subestado == ESTADO_INICIO)
				{
					//printf("Vou me esconder %d\n", (int)a);
					a->velocidade = 0;		
					a->invulneravel = 1;
					a->estado.subestado = ESTADO_RODANDO;
					a->temporizadores[TEMPORIZADOR_ESCONDIDO] = info->tempoEsconderijo;

					ATOR_TrocaAnimacao(a, ANIM_ESCONDIDO);
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
							if((ev.subtipo==TEMPORIZADOR_ESCONDIDO) && !(a->aux_int[INT_FLAG_DIA]))
							{				
								a->invulneravel = 0;
								ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
							}
							break;

						case EVT_ANOITECEU:
							a->aux_int[INT_FLAG_DIA] = false;
							a->temporizadores[TEMPORIZADOR_ESCONDIDO] = rand() % info->tempoEsconderijo;
							break;
					}
				}
	}

	return true;
}
