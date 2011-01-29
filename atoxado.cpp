#include <c2d2/chien2d2.h>

#include "jogo_atores.h"
#include "atoxado.h"

//Animacao 
// Vetor com as animações da nave (2 no total)
Animacao animAtoxado[] ={
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	// ATOXADO_PARADO direita: 0
	{1, 1, {1}},
	// ATOXADO_PARADO esquerda: 1
	{1, 1, {4}},
	// ATOXADO_ANDANDO direita: 2
	{4, 10, {0, 1, 2, 1}},
	// ATOXADO_ANDANDO esquerda: 3
	{4, 10, {3, 4, 3, 5}},
	// ATOXADO_PULANDO direita: 4
	{1, 1, {2}},
	// ATOXADO_PULANDO esquerda: 5
	{1, 1, {3}},
	// ATOXADO_CAINDO direita: 6
	{2, 5, {0, 2}},
	// ATOXADO_CAINDO esquerda: 7
	{2, 5, {3, 5}},
	// ATOXADO_VITORIA: 8
	{2, 30, {9, 10}},
	// ATOXADO_MORRENDO: 9
	{1, 1, {12}},
	// ATOXADO_MORREU: 10
	{1, 1, {11}}
};

char *sons[]={
	"audio/pula.wav",
	"audio/bate.wav",
	"audio/morreu.wav"
};

enum 
{
	TEMPORIZADOR_MORRENDO = 0,
	TEMPORIZADOR_MORTE,
	TEMPORIZADOR_VITORIA,
	TEMPORIZADOR_TOCHA
};

enum CamposAuxiliaresInt
{
	INT_RESETA_TOCHA = 0,
	INT_OSCILACAO_TOCHA = 1,
	INT_BOOST_TOCHA = 2,
	INT_TEMPO_BOOST = 3,
	INT_SINAL_BOOST = 4
};

enum CamposAuxiliaresReal
{
	REAL_X = 0,
	REAL_Y,
	REAL_ENERGIA_TOCHA
};

//Tempo entre cada update da tocha
#define TEMPO_TOCHA 2

//Energia minima da tocha, abaixo disso morte
#define ENERGIA_MINIMA 164

//Energia inicial da tocha
#define ENERGIA_INICIAL 512

//Valor maximo que a tocha oscila para dar o efeito visual
#define OSCILACAO_MAX 30

//Quanto que a gota prejudica a tocha
#define DANO_GOTA 70

#define EFEITO_GOTA_TOCHA 250

#define PASSO_OSCILACAO_GOTA 6

static bool AtualizaAtoxado(Ator *a, unsigned int mapa);

// A função que carrega o DarkPhoenix.
//
bool CarregaAtoxado()
{
	return ATOR_CarregaAtorEstatico(
		ATOXADO, 
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animAtoxado, 
		false, 
		sons, 
		3, 
		&AtualizaAtoxado
	);
}

static void AtualizaColisaoAtor(Ator *a, Evento *ev, unsigned int mapa)
{
	switch(ev->tipoEvento)
	{
		case EVT_COLIDIU_PERSONAGEM:
			switch(ev->subtipo)
			{
				case ITEM_MADEIRA:
					break;

				case GOTA:
					a->aux_int[INT_BOOST_TOCHA] = EFEITO_GOTA_TOCHA;
					a->aux_int[INT_TEMPO_BOOST] = PASSO_OSCILACAO_GOTA;
					a->aux_int[INT_SINAL_BOOST] = -1;
					a->aux_real[REAL_ENERGIA_TOCHA] -= DANO_GOTA * ((rand() % 100) / 150.0f);
					break;

				default:
					ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
					break;
			}			
			break;
	}
}

static void AtualizaTochada(Actor *a, Event *ev, unsigned int mapa)
{

}

static void AtualizaVoo(Ator *a, Evento *ev, unsigned int mapa)
{
	switch(ev->tipoEvento)
	{
		case EVT_PRESSIONOU_ESQ:
			if(a->velocidade==0)
			{
				a->velocidade = VANDA;
				a->direcao = 180;
				ATOR_TrocaAnimacao(a, 5);
			}
			break;

		case EVT_PRESSIONOU_DIR:
			if(a->velocidade==0)
			{
				a->velocidade = VANDA;
				a->direcao = 0;
				ATOR_TrocaAnimacao(a, 4);
			}
			break;

		case EVT_LIBEROU_ESQ:
			if(a->velocidade!=0 && a->direcao == 180)
				a->velocidade = 0;
			break;

		case EVT_LIBEROU_DIR:
			if(a->velocidade!=0 && a->direcao == 0)
				a->velocidade = 0;
			break;

		case EVT_COLIDIU_ARMADILHA:
			ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
			break;

		case EVT_CHECKPOINT:
			a->aux_real[REAL_X] = a->x;
			a->aux_real[REAL_Y] = a->y;
			break;

		case EVT_FIM_FASE:
			ATOR_TrocaEstado(a, ATOXADO_VITORIA, false);
			break;

		default:
			AtualizaColisaoAtor(a, ev, mapa);
			break;
	}
}



static void AtualizaTocha(Ator *a, Evento *ev, unsigned int mapa)
{
	switch(ev->tipoEvento)
	{
		case EVT_TEMPO:
			if(ev->subtipo != TEMPORIZADOR_TOCHA)
				break;

			a->temporizadores[TEMPORIZADOR_TOCHA] = TEMPO_TOCHA;
			a->aux_real[REAL_ENERGIA_TOCHA] -= 0.1f;	
			a->energia = (int)(a->aux_real[REAL_ENERGIA_TOCHA] + (rand() % OSCILACAO_MAX));
			a->energia += a->aux_int[INT_BOOST_TOCHA] * a->aux_int[INT_SINAL_BOOST];
			if(a->energia <= ENERGIA_MINIMA)
				a->energia = ENERGIA_MINIMA;

			a->aux_int[INT_BOOST_TOCHA] -= a->aux_int[INT_TEMPO_BOOST];
			if(a->aux_int[INT_BOOST_TOCHA] < 0)
				a->aux_int[INT_BOOST_TOCHA] = 0;

			if(a->aux_real[REAL_ENERGIA_TOCHA] <= ENERGIA_MINIMA)
			{				
				a->energia = ENERGIA_MINIMA / 2;
				a->aux_int[INT_RESETA_TOCHA] = true;

				ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
			}
			break;
	}
}

// A função para fazer a lógica do DarkPhoenix
//
// Data: 04/09/2008
// Última atualização: 04/09/2008
//
static bool AtualizaAtoxado(Ator *a, unsigned int mapa)
{
	Evento ev;
	switch(a->estado.estado)
	{
		case ATOR_NASCENDO:
			// Muda para o estado adequado
			ATOR_TrocaEstado(a, ATOXADO_INICIO, false);
			a->vidas=3;
			a->aux_real[REAL_ENERGIA_TOCHA] = ENERGIA_INICIAL;
			a->energia = ENERGIA_INICIAL;
			a->temporizadores[TEMPORIZADOR_TOCHA] = TEMPO_TOCHA;
			break;

		case ATOXADO_INICIO:
			// Indica para qual direção está olhando
			a->olhandoPara=0;
			// Guarda a posição inicial
			a->aux_real[REAL_X] = a->x;
			a->aux_real[REAL_Y] = a->y;
			ATOR_TrocaEstado(a, ATOXADO_PARADO, false);
			break;

		case ATOXADO_PARADO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				a->velocidade=0;
				a->estado.subestado=ESTADO_RODANDO;
				if(a->direcao==0)
					ATOR_TrocaAnimacao(a, 0);
				else
					ATOR_TrocaAnimacao(a, 1);
			}

			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_PRESSIONOU_BOTAO1:
						ATOR_TrocaEstado(a, ATOXADO_PULANDO, false);
						break;
					case EVT_PRESSIONOU_ESQ:
						ATOR_TrocaEstado(a, ATOXADO_ANDANDO,false);
						a->direcao=180;
						break;
					case EVT_PRESSIONOU_DIR:
						ATOR_TrocaEstado(a, ATOXADO_ANDANDO,false);
						a->direcao=0;
						break;
					case EVT_COMECOU_CAIR:
						ATOR_TrocaEstado(a, ATOXADO_CAINDO, false);
						break;
					case EVT_COLIDIU_ARMADILHA:
						ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
						break;
					case EVT_CHECKPOINT:
						a->aux_real[REAL_X] = a->x;
						a->aux_real[REAL_Y] = a->y;
						break;
					case EVT_FIM_FASE:
						ATOR_TrocaEstado(a, ATOXADO_VITORIA, false);
						break;

					default:
						AtualizaTocha(a, &ev, mapa);
						AtualizaColisaoAtor(a, &ev, mapa);
						break;
				}
			}
			break;
		case ATOXADO_PULANDO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				ATOR_Impulsiona(a, VPULO);
				ATOR_TocaEfeitoTela(a, 0, mapa);
				a->estado.subestado=ESTADO_RODANDO;
				if(a->direcao==0)
					ATOR_TrocaAnimacao(a, 4);
				else
					ATOR_TrocaAnimacao(a, 5);

			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_TOPO_PULO:
						ATOR_TrocaEstado(a, ATOXADO_CAINDO, false);
						break;
					case EVT_COLIDIU_PAREDE:
						if(ev.subtipo == SUBEVT_COLIDIU_PAREDE_CIMA)
						{
							ATOR_TrocaEstado(a, ATOXADO_CAINDO, false);
							ATOR_TocaEfeitoTela(a, 1, mapa);
						}
						break;			

					case EVT_SAIU_FORA_MAPA:
						if(ev.subtipo != SUBEVT_SAIU_FORA_MAPA_CIMA)
							ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
						break;

					default:
						AtualizaTocha(a, &ev, mapa);
						AtualizaVoo(a, &ev, mapa);
						break;
				}
			}
			break;
		case ATOXADO_CAINDO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				a->estado.subestado=ESTADO_RODANDO;
				if(a->direcao==0)
					ATOR_TrocaAnimacao(a, 6);
				else
					ATOR_TrocaAnimacao(a, 7);

			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_SAIU_FORA_MAPA:
						if(ev.subtipo != SUBEVT_SAIU_FORA_MAPA_CIMA)
							ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
						break;
					case EVT_COLIDIU_PAREDE:
						if(ev.subtipo == SUBEVT_COLIDIU_PAREDE_BAIXO)
							if(a->velocidade == 0)
								ATOR_TrocaEstado(a, ATOXADO_PARADO, false);
							else
								ATOR_TrocaEstado(a, ATOXADO_ANDANDO, false);
						break;										

					default:
						AtualizaTocha(a, &ev, mapa);
						AtualizaVoo(a, &ev, mapa);
						break;
				}
			}

			break;

		case ATOXADO_ANDANDO:
			if(a->estado.subestado==ESTADO_INICIO)
			{
				a->velocidade=VANDA;
				a->estado.subestado=ESTADO_RODANDO;
				if(a->direcao==0)
					ATOR_TrocaAnimacao(a, 2);
				else
					ATOR_TrocaAnimacao(a, 3);
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_PRESSIONOU_BOTAO1:
 						ATOR_TrocaEstado(a, ATOXADO_PULANDO, false);
						break;
					case EVT_LIBEROU_ESQ:
						if(a->direcao==180)
							ATOR_TrocaEstado(a, ATOXADO_PARADO,false);
						break;
					case EVT_LIBEROU_DIR:
						if(a->direcao==0)
							ATOR_TrocaEstado(a, ATOXADO_PARADO,false);
						break;
					case EVT_COLIDIU_PAREDE:
						if(ev.subtipo==SUBEVT_COLIDIU_PAREDE_CIMA)
							ATOR_TocaEfeitoTela(a, 1, mapa);
						break;
					case EVT_SAIU_FORA_MAPA:
						if(ev.subtipo != SUBEVT_SAIU_FORA_MAPA_CIMA)
							ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
						break;
					case EVT_COLIDIU_ARMADILHA:
						ATOR_TrocaEstado(a, ATOXADO_MORRENDO, false);
						break;
					case EVT_CHECKPOINT:
						a->aux_real[REAL_X] = a->x;
						a->aux_real[REAL_Y] = a->y;
						break;
					case EVT_FIM_FASE:
						ATOR_TrocaEstado(a, ATOXADO_VITORIA, false);
						break;

					default:
						AtualizaTocha(a, &ev, mapa);
						AtualizaColisaoAtor(a, &ev, mapa);
						break;
				}
			}
			break;
		case ATOXADO_MORRENDO:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				ATOR_Impulsiona(a, VPULO*1.5);
				ATOR_TrocaAnimacao(a, 9);
				ATOR_TocaEfeitoTela(a, 2, mapa);
				a->temporizadores[TEMPORIZADOR_MORRENDO] = 120;
				a->estado.subestado = ESTADO_RODANDO;
				a->velocidade=0;
				a->vidas--;
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
					case EVT_COLIDIU_PAREDE:
						if(ev.subtipo == SUBEVT_COLIDIU_PAREDE_BAIXO)
							ATOR_TrocaEstado(a, ATOXADO_MORREU, false);
						break;
					case EVT_TEMPO:
						if(ev.subtipo==TEMPORIZADOR_MORRENDO)
							ATOR_TrocaEstado(a, ATOXADO_MORREU, false);
						break;
				}
			}
			break;
		case ATOXADO_MORREU:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				ATOR_TrocaAnimacao(a, 10);
				a->velocidade=0;
				a->temporizadores[TEMPORIZADOR_MORTE] = 60;
				a->estado.subestado = ESTADO_RODANDO;
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				switch(ev.tipoEvento)
				{
				case EVT_TEMPO:
					if(ev.subtipo==TEMPORIZADOR_MORTE)
					{
						if(a->vidas>0)
						{
							a->x = a->aux_real[REAL_X];
							a->y = a->aux_real[REAL_Y];
							a->direcao=0;

							//religamos a tocha
							a->temporizadores[TEMPORIZADOR_TOCHA] = TEMPO_TOCHA;

							if(a->aux_int[INT_RESETA_TOCHA])
							{
								a->aux_int[INT_RESETA_TOCHA] = false;
								a->aux_real[REAL_ENERGIA_TOCHA] = ENERGIA_INICIAL;
								a->energia = ENERGIA_INICIAL;
							}

							ATOR_TrocaEstado(a, ATOXADO_PARADO, false);
						}
						else
							ATOR_TrocaEstado(a, ATOR_ENCERRADO, false);
					}
					break;
				}
			}
			break;
		case ATOR_ENCERRADO:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->estado.subestado=ESTADO_RODANDO;
				a->velocidade=0;
				ev.tipoEvento = EVT_FIM_FASE;
				ev.subtipo = SUBEVT_FIM_FASE_DERROTA;
				ATOR_EnviaEventoJogo(&ev);

			}

			return false;
		case ATOXADO_VITORIA:
			if(a->estado.subestado == ESTADO_INICIO)
			{
				a->estado.subestado=ESTADO_RODANDO;
				ATOR_TrocaAnimacao(a, 8);
				a->temporizadores[TEMPORIZADOR_VITORIA]=240;
				a->velocidade=0;
			}
			while(ATOR_ProximoEvento(a, &ev))
			{
				if((ev.tipoEvento==EVT_TEMPO) && (ev.subtipo == TEMPORIZADOR_VITORIA))
				{
					ev.tipoEvento = EVT_FIM_FASE;
					ev.subtipo = SUBEVT_FIM_FASE_VITORIA;
					ATOR_EnviaEventoJogo(&ev);
				}
			}
			break;
	}
	return true;
}
