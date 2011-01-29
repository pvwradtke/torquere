#include <c2d2/chien2d2.h>

#include "jogo_atores.h"
#include "lobo.h"

enum
{
	ANIM_ANDANDO_DIREITA,
	ANIM_ANDANDO_ESQUERDA,
	ANIM_MORRENDO
}

//Animacao 
Animacao animLobo[] =
{
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	// BOLA_PULA ESQUERDA : 0
	{10, 5, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},
	// BOLA_PULA direita : 1
	{10, 5, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}},
	// bola morreu: 2
	{2, 20, {0,5}}
};

bool CarregaLobo()
{
	return ATOR_CarregaAtorEstatico(
		LOBO, 
		"imagens/inimigobola.png", 
		28, 
		28, 
		0, 
		0,
		28, 
		28, 
		animLobo, 
		false, 
		0, 
		0, 
		&AtualizaLobo
	);
}


bool AtualizaLobo(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
			// Muda para o estado adequado
			ATOR_TrocaEstado(a, LOBO_ANDANDO, false);
			break;

		case LOBO_ANDANDO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				a->velocidade=2;
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
						ATOR_TrocaEstado(a, LOBO_ANDANDO, false);
						break;

					case EVT_COLIDIU_FIM_ESQUERDA:
						a->direcao=0;
						ATOR_TrocaEstado(a, LOBO_ANDANDO, false);
						break;					

					case EVT_COLIDIU_PERSONAGEM:
						ATOR_TrocaEstado(a, LOBO_ANDANDO, false);
						break;
				}
			}
			break;

			case LOBO_MORRENDO:
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
