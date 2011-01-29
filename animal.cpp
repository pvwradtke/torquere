#include "animal.h"

#include <stdio.h>

#include "jogo_atores.h"

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

					case EVT_COLIDIU_FIM_DIREITA:
						a->direcao=180;
						ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;

					case EVT_COLIDIU_FIM_ESQUERDA:
						a->direcao=0;
						ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
						break;					

					case EVT_COLIDIU_PERSONAGEM:
						ATOR_TrocaEstado(a, ANIMAL_ANDANDO, false);
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
	}

	return true;
}
