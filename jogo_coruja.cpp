#include <c2d2/chien2d2.h>

#include "jogo_atores.h"
#include "jogo_coruja.h"

enum {
    ANIM_CORUJA_DIREITA, 
ANIM_CORUJA_ARMADA_DIREITA, ANIM_CORUJA_ATACANDO_DIREITA,
    ANIM_CORUJA_ESQUERDA, ANIM_CORUJA_ARMADA_ESQUERDA, ANIM_CORUJA_ATACANDO_ESQUERDA,
    ANIM_CORUJA_ESCONDIDA
};

//Animacao 
// Vetor com as anima��es da nave (2 no total)
Animacao animCoruja[] = {
    // Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
    // VOANDO_DIREITA : 0
    {1, 1,
        {0}},
    // Armada direita 1
    {1, 1,
        {0}},
    // Atacando direita
    {1, 1,
        {0}},
    // VOANDO_ESQUERDA
    {1, 1,
        {1}},
    // Armada esquerda
    {1, 1,
        {1}},
    // Atacando esquerda
    {1, 1,
        {1}},
    // bola morreu: 2
    {1, 1,
        {2}}
};

// A matriz de eventos do personagem
acao acoes[CORUJA_ESTADOS][EVT_MAX];

char *sonsCorujao[]={
	"audio/coruja1.ogg",
        "audio/coruja2.ogg",
        "audio/coruja3.ogg",
        "audio/coruja4.ogg"
};

// A fun��o que carrega o DarkPhoenix.
//

bool JOGO_CarregaCoruja() {
    if(ATOR_CarregaAtorEstatico(CORUJA, "imagens/coruja_beta.png", 32, 32, 0, 0,
            32, 32, animCoruja, false, sonsCorujao, 4, &AtualizaCoruja))
    {
        // Associa as ações a matriz
        memset(acoes, 0, sizeof(acao)*CORUJA_ESTADOS*EVT_JOGO_PROG);
        acoes[CORUJA_ATACANDO][EVT_COLIDIU_FIM_DIREITA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_ATACANDO][EVT_COLIDIU_FIM_ESQUERDA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_DESLOCANDO][EVT_COLIDIU_FIM_DIREITA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_DESLOCANDO][EVT_COLIDIU_FIM_ESQUERDA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_ESCONDIDA][EVT_TEMPO] = &AcaoCorujaTemporizador;
        acoes[CORUJA_ARMADA][EVT_TEMPO] = &AcaoCorujaTemporizador;
        acoes[CORUJA_DESLOCANDO][EVT_PROXIMO_JOGADOR] = &AcaoCorujaProximaJogador;
        acoes[CORUJA_DESLOCANDO][EVT_TOCHADA] = &AcaoCorujatochada;
        acoes[CORUJA_ARMADA][EVT_TOCHADA] = &AcaoCorujatochada;
        return true;
    }
    else
        return false;
}

// A fun��o para fazer a l�gica do DarkPhoenix
//
// Data: 04/09/2008
// �ltima atualiza��o: 04/09/2008
//

bool AtualizaCoruja(Ator *a, unsigned int mapa) {
    Evento ev;
    // Testa entrada dos estados
    switch (a->estado.estado) {
        case ATOR_NASCENDO:
            // Muda para o estado adequado
            ATOR_TrocaEstado(a, CORUJA_DESLOCANDO, false);
            a->gravidade = false;
            a->direcao = 0;
            break;
        case CORUJA_DESLOCANDO:
            if (a->estado.subestado == ESTADO_INICIO) {
                a->velocidade = 2;
                a->estado.subestado = ESTADO_RODANDO;
                if (a->direcao == 0)
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_DIREITA);
                else
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_ESQUERDA);
            }
            break;

        case CORUJA_ARMADA:
            if (a->estado.subestado == ESTADO_INICIO) {
                if (a->direcao == 0)
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_ARMADA_DIREITA);
                else
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_ARMADA_ESQUERDA);
                a->velocidade = 0;
                a->estado.subestado = ESTADO_RODANDO;
                a->temporizadores[0] = 120;
            }
            break;
        case CORUJA_ATACANDO:
            if (a->estado.subestado == ESTADO_INICIO) {
                a->velocidade = 4;
                if (a->direcao == 0)
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_ATACANDO_DIREITA);
                else
                    ATOR_TrocaAnimacao(a, ANIM_CORUJA_ATACANDO_ESQUERDA);                
                a->estado.subestado = ESTADO_RODANDO;
                // usa o contador para contar quantos pixels desceu para baixo
                a->aux_int[0]=0;
                // 0 indica que o personagem está descendo, 1 indica que está subindo
                a->aux_int[1]= 0;
                if(a->naTela)
                    ATOR_TocaEfeito(a, rand()%4, mapa);
            }
            else
            {
                if(a->aux_int[1])
                {
                    // Sobe a coruja
                    a->y-=4;
                    if(--a->aux_int[0] == 0)
                    {
                        ATOR_TrocaEstado(a, CORUJA_DESLOCANDO, false);
                        a->temporizadores[0]=120;
                    }
                }
                else
                {
                    // desce a coruja
                    a->y+=4;;
                    if(++a->aux_int[0] == 16)
                        a->aux_int[1]=1;
                }
            }
            break;
        case CORUJA_ESCONDIDA:
            if (a->estado.subestado == ESTADO_INICIO) {
                a->velocidade = 0;
				a->invulneravel = 1;
                a->estado.subestado = ESTADO_RODANDO;
                ATOR_TrocaAnimacao(a, ANIM_CORUJA_ESCONDIDA);
                a->velocidade=0;
                a->temporizadores[0]=300;
            }
            break;

        case ATOR_ENCERRADO:
            return false;
    }
    // Processa eventos na matriz (fuck yeah!)
    while(ATOR_ProximoEvento(a, &ev))
    {
        if(acoes[a->estado.estado][ev.tipoEvento] != 0)
            acoes[a->estado.estado][ev.tipoEvento](a, mapa, &ev );
    }
    return true;
}

// A ação quando bate no marcador que limita o movimento
 bool AcaoCorujaFimDireitaEsquerda(Ator* a, unsigned int mapa, Evento *evt)
 {
     // Se bateu no marcador, simplesmente muda a direção
     if(evt->tipoEvento == EVT_COLIDIU_FIM_DIREITA && a->direcao == 0 )
     {
         a->direcao = 180;
         ATOR_TrocaAnimacao(a, ANIM_CORUJA_ESQUERDA);
     }
     else if(evt->tipoEvento == EVT_COLIDIU_FIM_ESQUERDA && a->direcao == 180 )
     {
         a->direcao = 0;
         ATOR_TrocaAnimacao(a, ANIM_CORUJA_DIREITA);
     }
     return true;
 }

 // A ação de eventos de tempo
 bool AcaoCorujaTemporizador(Ator* a, unsigned int mapa, Evento *evt)
 {
     // Se acabou o temporizador, sai do esconderijo ou então ataca
     // Testa se estava armada, o evento é de tempo e se o temporizador é 0
     if(a->estado.estado == CORUJA_ARMADA && evt->tipoEvento == EVT_TEMPO && evt->subtipo==0)
         ATOR_TrocaEstado(a, CORUJA_ATACANDO, false);
     else if(a->estado.estado == CORUJA_ESCONDIDA && evt->tipoEvento == EVT_TEMPO && evt->subtipo==0)
	 {
		 a->invulneravel = 0;
         ATOR_TrocaEstado(a, CORUJA_DESLOCANDO, false);
	 }
     return true;
 }

 // A ação de evento de visualização do jogador
 bool AcaoCorujaProximaJogador(Ator* a, unsigned int mapa, Evento *evt)
 {
     if(a->estado.estado == CORUJA_DESLOCANDO && evt->tipoEvento == EVT_PROXIMO_JOGADOR && a->temporizadores[0]==0)
         ATOR_TrocaEstado(a, CORUJA_ATACANDO, false);
     return true;
 }

 // Aqui tem que ir a funcao da tochada
// A ação de evento da tochada
 bool AcaoCorujatochada(Ator* a, unsigned int mapa, Evento *evt)
 {
     if((a->estado.estado == CORUJA_DESLOCANDO || a->estado.estado == CORUJA_ARMADA) && evt->tipoEvento == EVT_TOCHADA)
         ATOR_TrocaEstado(a, CORUJA_ESCONDIDA, false);
     return true;

 }
