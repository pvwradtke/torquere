#include "animal.h"

#include <stdio.h>

#include "jogo_atores.h"

static void AtualizaDirecao(Ator *a, Evento *ev, unsigned int mapa, int proximoEstado)
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

bool AtualizaAnimal(Ator *a, InfoAnimal *info, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
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

				a->aux_int[0]=30;
			}

			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_FOCO_TELA:
						printf("Personagem entrou na tela.\n");
						break;

					case EVT_PERDE_FOCO_TELA:
						printf("Personagem saiu da tela.\n");
						break;

					case EVT_SAIU_FORA_MAPA:
						ATOR_TrocaEstado(a, ATOR_ENCERRADO, false);
						break;					

					case EVT_COLIDIU_PERSONAGEM:
						ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;

					case EVT_PROXIMO_JOGADOR:
						ATOR_TrocaEstado(a, ANIMAL_PREPARA_ATAQUE, false);
						break;

					default:
						AtualizaDirecao(a, &ev, mapa, ANIMAL_ANDANDO);
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
					a->temporizadores[0] = info->tempoBote;
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
						if(ev.subtipo==0)
							ATOR_TrocaEstado(a, ANIMAL_ATACANDO, false);
						break;						
					}
				}
				break;

			case ANIMAL_ATACANDO:
				if(a->estado.subestado==ESTADO_INICIO)
				{
					printf("Iniciei o ataque\n");
					a->velocidade=info->velocidadeAtaque;
					a->estado.subestado=ESTADO_RODANDO;
					a->temporizadores[0] = info->tempoAtaque;
				}

				while(ATOR_ProximoEvento(a, &ev))
				{
					switch(ev.tipoEvento)
					{						
						case EVT_TEMPO:
						if(ev.subtipo==0)
							ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;		

						default:
							AtualizaDirecao(a, &ev, mapa, ANIMAL_ATACANDO);
							break;
					}
				}
				break;
	}

	return true;
}
