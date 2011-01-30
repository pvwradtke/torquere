#include "menu.h"
#include "jogo.h"

int main(int ac, char **av)
{
    ////////////////////////////
    //tela escolha resolução //
    //////////////////////////
    if(!C2D2_Inicia(360, 120, C2D2_JANELA, C2D2_DESENHO_OPENGL, (char*)"torquere"))
	{
		printf("Nao conseguiu iniciar a tela. Encerrando.\n");
		return 1;
	}
    static C2D2_Botao *teclado = C2D2_PegaTeclas();
    static C2D2_Mouse *mouse = C2D2_PegaMouse();
    unsigned int cursor = C2D2_CarregaSpriteSet("./menu/cursor.png",40,40);
    unsigned int botsmode = C2D2_CarregaSpriteSet("./menu/botsmode.png", 100,100);
    int balpha[12]={0,0,0,0,0,0,0,0,0,0,0,0};

    while(1)
    {
        //sai com esc
        if(teclado[C2D2_ESC].pressionado)
        {
            C2D2_Encerra();
            return 0;
        }
        C2D2_LimpaTela();
        if(XDesenhaBotao(botsmode,0,10,10,cursor,balpha[0])==1)
        {
            ydesl=0;
            telaCheia=false;
            break;
        }
        if(XDesenhaBotao(botsmode,2,130,10,cursor,balpha[1])==1)
        {
            ydesl=0;
            telaCheia=true;
            break;
        }
        if(XDesenhaBotao(botsmode,4,250,10,cursor,balpha[2])==1)
        {
            ydesl=84;
            telaCheia=true;
            break;
        }
        C2D2_DesenhaSprite(cursor,0,mouse->x,mouse->y);
        C2D2_Sincroniza(60);
    }
    C2D2_Encerra();



    ///////////
    // MENU///
    /////////

	if (!C2D2_Inicia(LARGURA_TELA, ydesl==0?ALTURA_TELA:ALTURA_TELA2,telaCheia?C2D2_TELA_CHEIA:C2D2_JANELA, C2D2_DESENHO_OPENGL, "torquere"))
	{
		printf("Nao conseguiu iniciar a tela. Encerrando.\n");
		return 1;
	}

	// Inicia o áudio
	CA2_Inicia();

	//carrega no splash screen//

	estado_atual=TELA_SPLASH;

	while(estado_atual!=SAIR)
	{
		//depois de sair do while da tela ele precisa voltar pra zero
		encerra=0;

		switch(estado_atual)
		{
            case TELA_SPLASH:
				menu_splash();break;
            case TELA_MAIN:
				menu_main();break;
            case TELA_AJUDA:
				menu_ajuda();break;
            case TELA_ABOUT:
				menu_about();break;
//            case TELA_TROFEUS:
//				menu_trofeus();
//				break;
            case TELA_INTRO:
				menu_intro();break;
            case TELA_FIM:
				menu_fim();break;
            case TELA_GAMEOVER:
                menu_gameover();break;
            case TELA_EREMITA:
                menu_eremita();break;
			case TELA_JOGO:
				main_jogo();
				estado_atual = TELA_MAIN;
				break;
			case SAIR:
				return 0;
				break;
		}
	}
	// Encerra tudo
	CA2_Encerra();
	C2D2_Encerra();
	return 0;
}
