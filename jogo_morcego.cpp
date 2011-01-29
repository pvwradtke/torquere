#include <c2d2/chien2d2.h>

#include <math.h>

#include "jogo_atores.h"
#include "jogo_morcego.h"

enum {
    ANIM_MORCEGO_DIREITA, ANIM_MORCEGO_ESQUERDA
};

//Animacao 
// Vetor com as anima��es da nave (2 no total)
Animacao animMorcego[] = {
    // Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
    // VOANDO_DIREITA : 0
    {1, 1,
        {0}},
    // VOANDO_ESQUERDA
    {1, 1,
        {1}},

};

// A matriz de eventos do personagem
acao acoesMorcego[MORCEGO_ESTADOS][EVT_MAX];

// A fun��o que carrega o DarkPhoenix.
//

bool JOGO_CarregaMorcego() {
    if(ATOR_CarregaAtorEstatico(MORCEGO, "imagens/coruja_beta.png", 32, 32, 0, 0,
            32, 32, animMorcego, false, 0, 0, &AtualizaMorcego))
    {
        // Associa as ações a matriz
        memset(acoesMorcego, 0, sizeof(acao)*MORCEGO_ESTADOS*EVT_JOGO_PROG);
        acoesMorcego[MORCEGO_DESLOCANDO][EVT_COLIDIU_FIM_DIREITA] = &AcaoMorcegoFimDireitaEsquerda;
        acoesMorcego[MORCEGO_DESLOCANDO][EVT_COLIDIU_FIM_ESQUERDA] = &AcaoMorcegoFimDireitaEsquerda;
/*        acoes[CORUJA_DESLOCANDO][EVT_COLIDIU_FIM_DIREITA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_DESLOCANDO][EVT_COLIDIU_FIM_ESQUERDA] = &AcaoCorujaFimDireitaEsquerda;
        acoes[CORUJA_ESCONDIDA][EVT_TEMPO] = &AcaoCorujaTemporizador;
        acoes[CORUJA_ARMADA][EVT_TEMPO] = &AcaoCorujaTemporizador;
        acoes[CORUJA_DESLOCANDO][EVT_PROXIMO_JOGADOR] = &AcaoCorujaProximaJogador;
        acoes[CORUJA_DESLOCANDO][EVT_TOCHADA] = &AcaoCorujatochada;
        acoes[CORUJA_ARMADA][EVT_TOCHADA] = &AcaoCorujatochada;*/
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

bool AtualizaMorcego(Ator *a, unsigned int mapa) {
    Evento ev;
    // Testa entrada dos estados
    switch (a->estado.estado) {
        case ATOR_NASCENDO:
            // Muda para o estado adequado
            ATOR_TrocaEstado(a, MORCEGO_DESLOCANDO, false);
            a->gravidade = false;
            a->direcao = 0;
            // Guarda a linha em que o morcego foi criado para fazer a senoidal
            a->aux_real[0]=a->y;
            // indica o ângulo inicial
            a->aux_int[0] = 0;
            break;
        case MORCEGO_DESLOCANDO:
        {
            if (a->estado.subestado == ESTADO_INICIO) {
                a->velocidade = 2;
                a->estado.subestado = ESTADO_RODANDO;
                if (a->direcao == 0)
                    ATOR_TrocaAnimacao(a, ANIM_MORCEGO_DIREITA);
                else
                    ATOR_TrocaAnimacao(a, ANIM_MORCEGO_ESQUERDA);
            }
            // Calcula o quanto mexe no eixo y
            a->aux_int[0] = (a->aux_int[0]+5)%360;
            double desloca = 64 * sin(a->aux_int[0]*0.017453293);
            a->y = a->aux_real[0]+desloca;
            break;
        }
        case ATOR_ENCERRADO:
            return false;
    }
    // Processa eventos na matriz (fuck yeah!)
    while(ATOR_ProximoEvento(a, &ev))
    {
        if(acoesMorcego[a->estado.estado][ev.tipoEvento] != 0)
            acoesMorcego[a->estado.estado][ev.tipoEvento](a, mapa, &ev );
    }
    return true;
}

// A ação quando bate no marcador que limita o movimento
 bool AcaoMorcegoFimDireitaEsquerda(Ator* a, unsigned int mapa, Evento *evt)
 {
     // Se bateu no marcador, simplesmente muda a direção
     if(evt->tipoEvento == EVT_COLIDIU_FIM_DIREITA && a->direcao == 0 )
     {
         a->direcao = 180;
         ATOR_TrocaAnimacao(a, ANIM_MORCEGO_ESQUERDA);
     }
     else if(evt->tipoEvento == EVT_COLIDIU_FIM_ESQUERDA && a->direcao == 180 )
     {
         a->direcao = 0;
         ATOR_TrocaAnimacao(a, ANIM_MORCEGO_DIREITA);
     }
     return true;
 }