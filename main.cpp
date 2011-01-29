#include <assert.h>
#include <stdio.h>
#include <vector>

#include <c2d2/chien2d2.h>
#include <c2d2/chien2d2mapa.h>
#include <c2d2/chien2d2primitivas.h>
#include <c2d2/chienaudio2.h>
#include <c2d2/ator.h>

#include "jogo_atores.h"
#include "atoxado.h"
#include "jogo_bola.h"
#include "lobo.h"
#include "rato.h"
#include "gota.h"
#include "jogo_coruja.h"
#include "item_madeira.h"

// As dimens�es da tela desejada (cheia)
#define LARGURA_TELA	1024
#define ALTURA_TELA	600
#define ALTURA_TELA2	768
#define GRAVIDADE	250
#define MAXGRAVIDADE	2000

// Variável que indica o deslocamento da tela, para caso de 4:3
int ydesl = 0;

typedef std::vector<Ator *> VectorInimigos;

void ProcessaControle(Ator *a);

void ProcessaControle(Ator *a) {
    static Evento ev;
    static C2D2_Botao *teclado = C2D2_PegaTeclas();
    // TEsta se envia mensagens
    if (teclado[C2D2_CIMA].pressionado) {
        ev.tipoEvento = EVT_PRESSIONOU_CIMA;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_CIMA].liberado) {
        ev.tipoEvento = EVT_LIBEROU_CIMA;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_BAIXO].pressionado) {
        ev.tipoEvento = EVT_PRESSIONOU_BAIXO;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_BAIXO].liberado) {
        ev.tipoEvento = EVT_LIBEROU_BAIXO;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_ESQUERDA].pressionado) {
        ev.tipoEvento = EVT_PRESSIONOU_ESQ;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_ESQUERDA].liberado) {
        ev.tipoEvento = EVT_LIBEROU_ESQ;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_DIREITA].pressionado) {
        ev.tipoEvento = EVT_PRESSIONOU_DIR;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_DIREITA].liberado) {
        ev.tipoEvento = EVT_LIBEROU_DIR;
        ATOR_EnviaEvento(a, &ev);
    }
    if (teclado[C2D2_Z].pressionado) {
        ev.tipoEvento = EVT_PRESSIONOU_BOTAO1;
        ATOR_EnviaEvento(a, &ev);
    }
}

static double subPow2(double a, double b)
{
	return (a - b) * (a - b);
}

static void CriaInimigo(VectorInimigos *vec, int tipoMarca, int tipoAtor, int mapa)
{
	int x, y;
	if (C2D2M_PrimeiroBlocoMarca(mapa, tipoMarca, &x, &y)) {
        vec->push_back(ATOR_CriaAtor(tipoAtor, x, y, 0));

		assert(vec->back());

        while (C2D2M_ProximoBlocoMarca(mapa, &x, &y))
		{
            vec->push_back(ATOR_CriaAtor(tipoAtor, x, y, 0));
			assert(vec->back());
		}
    }
}

static void LiberaInimigos(VectorInimigos *vec)
{
	for(size_t i = 0;i < vec->size(); ++i)
	{
		free((*vec)[i]);
	}

	vec->clear();
}

int main(int narg, char **valarg) {
    // Inicia a Chien2D 2 e testa se deu tudo certo
    int altura = ALTURA_TELA;
    if (ydesl)
        altura = ALTURA_TELA2;
    if (C2D2_Inicia(LARGURA_TELA, ydesl == 0 ? ALTURA_TELA : ALTURA_TELA2, C2D2_JANELA, C2D2_DESENHO_OPENGL, "Darkphoenix - O Baixinho Invocado"))
        printf("Iniciou a Chien2D 2 com sucesso\n");
    else {
        printf("Falhou ao iniciar a Chien2D 2. Encerrando o programa.\n");
        return 0;
    }

    // Inicia as primitivas
    C2D2P_Inicia();
    // Inicia os mapas
    C2D2M_Inicia();
    // Inicia o �udio
    CA2_Inicia();
    // Inicia os personagens
    ATOR_Inicia();
    // Carrega a fonte do sistema
    unsigned int fonte = C2D2_CarregaFonte("imagens/isabelle64_alpha.png", 64);
    // Carrega a tocha
    unsigned int tocha = C2D2_CarregaSpriteSet("./imagens/mask.png", 512, 512);
    // Carrega o mapa
    //unsigned int mapa = C2D2M_CarregaMapaMappy("fases/Aula04-Mapa.FMP", "fases/Aula04-tileset.png");
    unsigned int mapa = C2D2M_CarregaMapaMappy("fases/atocha.fmp", "fases/tileset.png");
    // D� as velocidades. As duas �ltimas devem ser 1. As demais, incrementa de 1 em 1
    int numcamadas = 4;
    C2D2M_VelocidadeCamadaMapa(mapa, 3, 1);
    C2D2M_VelocidadeCamadaMapa(mapa, 4, 1);
    C2D2M_VelocidadeCamadaMapa(mapa, 5, 1);
    // A camada de marcas � sempre a �ltima
    C2D2M_CamadaMarcas(mapa, 0, 1);
    // Indica a gravidade a aplicar no mapa
    C2D2M_GravidadeMapa(mapa, GRAVIDADE, MAXGRAVIDADE);

    // Carrega o personagem
    bool cdark = CarregaAtoxado();
    bool cbola = JOGO_CarregaBola();
    bool clobo = CarregaLobo();
    bool crato = CarregaRato();
    bool cgota = CarregaGota();
    bool ccoruja = JOGO_CarregaCoruja();
    bool citemMadeira = CarregaItemMadeira();

    // As m�sicas
    unsigned int musicas[2];
    musicas[0] = CA2_CarregaMusica("audio/AulaPaulo_byPiovezan.it");
    musicas[1] = CA2_CarregaMusica("audio/venceu.wav");
    // Testa se carregou certo (se � diferente de 0)
    if (fonte == 0 || mapa == 0 || !cdark || !cbola || !ccoruja) {
        printf("Falhou ao carregar alguma coisa. Encerrando.\n");
        // Encerra a Chien2d2
        CA2_Encerra();
        ATOR_Encerra();
        C2D2M_Encerra();
        C2D2_Encerra();
        return 0;
    }
    C2D2_TrocaCorLimpezaTela(24, 24, 24);
    C2D2_Botao *teclado = C2D2_PegaTeclas();
    // cria o personagem
    int x = 60, y = 60;
    C2D2M_PrimeiroBlocoMarca(mapa, C2D2M_INICIO, &x, &y);
    Ator *dark = ATOR_CriaAtor(ATOXADO, x, y, 0);

    Evento ev;
    bool nafase = true;

    VectorInimigos inimigos;	

	CriaInimigo(&inimigos, MARCA_LOBO, LOBO, mapa);    
	CriaInimigo(&inimigos, MARCA_RATO, RATO, mapa);
	CriaInimigo(&inimigos, MARCA_CORUJA, CORUJA, mapa);	

	CriaInimigo(&inimigos, MARCA_GOTA, GOTA, mapa);
	CriaInimigo(&inimigos, MARCA_MADEIRA, ITEM_MADEIRA, mapa);

    // Coloca a m�sica para tocar
    CA2_TocaMusica(musicas[0], -1);
    // Indica se e a primeira vez que vai tocar a musicado fim da fase
    bool primeira = false;
    while (!teclado[C2D2_ESC].pressionado && nafase) {
        C2D2_LimpaTela();

        // Testa as colis�es
        if (ATOR_ColidiuBlocoCenario(dark, mapa, C2D2M_MORTE)) {
            ev.tipoEvento = EVT_COLIDIU_ARMADILHA;
            ATOR_EnviaEvento(dark, &ev);
        }
        if (ATOR_ColidiuBlocoCenario(dark, mapa, C2D2M_CHECK)) {
            ev.tipoEvento = EVT_CHECKPOINT;
            ATOR_EnviaEvento(dark, &ev);
        }
        if (ATOR_ColidiuBlocoCenario(dark, mapa, C2D2M_FIM)) {
            ev.tipoEvento = EVT_FIM_FASE;
            ATOR_EnviaEvento(dark, &ev);
            if (!primeira) {
                CA2_TocaMusica(musicas[1], -1);
                primeira = true;
            }
        }

		//
		//
		//Verifica se existem inimigos proximo do personagem
		//Em energia armazenamos a "potencia" da tocha
        double energia2 = dark->energia * dark->energia;
        for (size_t i = 0; i < inimigos.size(); ++i) {
            if (ATOR_ColidiuBlocoCenario(inimigos[i], mapa, MARCA_FIMDIREITA)) {
                ev.tipoEvento = EVT_COLIDIU_FIM_DIREITA;
                ATOR_EnviaEvento(inimigos[i], &ev);
            }

            if (ATOR_ColidiuBlocoCenario(inimigos[i], mapa, MARCA_FIMESQUERDA)) {
                ev.tipoEvento = EVT_COLIDIU_FIM_ESQUERDA;
                ATOR_EnviaEvento(inimigos[i], &ev);
            }

            if (dark->direcao != inimigos[i]->direcao) {
                double distancia = subPow2(inimigos[i]->x, dark->x) + subPow2(inimigos[i]->y, dark->y);
                if (distancia < energia2) {
                    ev.tipoEvento = EVT_PROXIMO_JOGADOR;
                    ATOR_EnviaEvento(inimigos[i], &ev);
                }
            }
        }

        for (size_t i = 0; i < inimigos.size(); i++) {
            if (inimigos[i] != 0)
                ATOR_ColidiuAtores(dark, inimigos[i]);
        }

        // Atualiza a l�gica
        ATOR_AplicaEstado(dark, mapa, LARGURA_TELA, ALTURA_TELA);
        for (size_t i = 0; i < inimigos.size(); i++) {
            if (inimigos[i] != 0)
                ATOR_AplicaEstado(inimigos[i], mapa, LARGURA_TELA, ALTURA_TELA);
        }

        // L� os controles
        ProcessaControle(dark);
        // Atualiza os personagens
        ATOR_Atualiza(dark, mapa);

        for (size_t i = 0; i < inimigos.size(); i++) {
            if (inimigos[i] != 0) {
                if (!ATOR_Atualiza(inimigos[i], mapa)) {
                    free(inimigos[i]);
                    inimigos[i] = 0;
                }
            }
        }

        // Centraliza o mapa no personagem principal
        ATOR_CentraMapa(dark, mapa, LARGURA_TELA, ALTURA_TELA);
        // Roda os eventos do jogo
        while (ATOR_ProximoEventoJogo(&ev)) {
            switch (ev.tipoEvento) {
                case EVT_FIM_FASE:
                    nafase = false;
                    break;
            }
        }

        // Desenha o cen�rio
        C2D2M_DesenhaCamadaMapa(mapa, 3, 0, ydesl, LARGURA_TELA, ALTURA_TELA);
        C2D2M_DesenhaCamadaMapa(mapa, 4, 0, ydesl, LARGURA_TELA, ALTURA_TELA);
        
        // DEsenha os personagens
        ATOR_Desenha(dark, mapa, 0, ydesl);
        for (size_t i = 0; i < inimigos.size(); i++) {
            if (inimigos[i] != 0)
                ATOR_Desenha(inimigos[i], mapa, 0, ydesl);
        }

        // Desenha a camada mais superior
        //C2D2M_DesenhaCamadaMapa(mapa, 3, 0, ydesl, LARGURA_TELA, ALTURA_TELA);
        C2D2M_DesenhaCamadaMapa(mapa, 5, 0, ydesl, LARGURA_TELA, ALTURA_TELA);
        // DEsenha as mensagens
        if ((dark->estado.estado == ATOXADO_MORRENDO || dark->estado.estado == ATOXADO_MORREU) && dark->vidas > 0)
            C2D2_DesenhaTexto(fonte, LARGURA_TELA / 2, ALTURA_TELA / 2 + ydesl, "Ops!", C2D2_TEXTO_CENTRALIZADO);
        if ((dark->estado.estado == ATOXADO_MORRENDO || dark->estado.estado == ATOXADO_MORREU) && dark->vidas == 0)
            C2D2_DesenhaTexto(fonte, LARGURA_TELA / 2, ALTURA_TELA / 2 + ydesl, "Game Over", C2D2_TEXTO_CENTRALIZADO);
        if (dark->estado.estado == ATOXADO_VITORIA)
            C2D2_DesenhaTexto(fonte, LARGURA_TELA / 2, ALTURA_TELA / 2 + ydesl, "Fase Completa!", C2D2_TEXTO_CENTRALIZADO);

        // Desenha as barras pretas se necessário
        if (ydesl) {
            C2D2P_RetanguloPintado(0, 0, LARGURA_TELA, ydesl, 0, 0, 0);
            C2D2P_RetanguloPintado(0, ydesl + ALTURA_TELA, LARGURA_TELA, 2 * ydesl + ALTURA_TELA, 0, 0, 0);
        }
        // Enfim, desenha a tocha
        C2D2_DesenhaSprite(tocha, 0, 256, ydesl+44);
        // Desenha as barras pretas
        C2D2P_RetanguloPintado(0,ydesl, LARGURA_TELA, ydesl+44, 0, 0, 0);
        C2D2P_RetanguloPintado(0,ydesl+556, LARGURA_TELA, ydesl+ALTURA_TELA, 0, 0, 0);
        C2D2P_RetanguloPintado(0,ydesl+44, 256, ydesl+556, 0, 0, 0);
        C2D2P_RetanguloPintado(768,ydesl+44, LARGURA_TELA, ydesl+556, 0, 0, 0);

        C2D2_Sincroniza(C2D2_FPS_PADRAO);
        if (teclado[C2D2_ENTER].ativo)
            C2D2_Pausa(50);
        //C2D2M_AnimaMapa(mapa);
    }

    // Apaga os personagens
    free(dark);
	LiberaInimigos(&inimigos);	

    // Descarrega o personagem
    ATOR_DescarregaAtor(ATOXADO);
    // Apaga as imagens carregadas na mem�ria
    C2D2_RemoveFonte(fonte);
    // Encerra os atores
    ATOR_Encerra();
    // Encerra os mapas
    C2D2M_Encerra();
    // Encerra o �udio
    CA2_Encerra();
    // Encerra a Chien2D 2
    C2D2_Encerra();

    return 0;
}
