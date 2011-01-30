#include "menu.h"

//fullscreen e cia
int ydesl=0;
bool telaCheia = false;

//estado e efeitos de fade
int estado_atual;
int encerra=0;
int fadealpha=255;
bool fadecontrol=false;


//sprites menu
unsigned int cursor;
unsigned int botsmain;
unsigned int botback;
unsigned int black;

unsigned int backmain;
unsigned int backajuda;
unsigned int backsobre;
unsigned int backsobre2;
unsigned int backgameover;
unsigned int backwin;

unsigned int splash;


//quadros
unsigned int quadrointro;
unsigned int quadroeremita;


//musicas
bool tocaMusicaMain = false;
unsigned int music_menu;
unsigned int music_game;
unsigned int music_over;
unsigned int music_win;
unsigned int music_eremita;


void XDesenhaSprite(unsigned int id,unsigned int indice,int posx, int posy,int largura,int altura,int alpha)
{
	//quando vai desenhar com o tamanho que foi carregado
	if(largura==0 || altura==0)
	{
		largura=sprites[id-1].spLargura; //olhar chien2d2 para referencia :P
		altura=sprites[id-1].spAltura;
	}

	int x[4];
	int y[4];
	x[0]=posx;
	x[1]=posx+largura;
	x[2]=posx+largura;
	x[3]=posx;
	y[0]=posy;
	y[1]=posy;
	y[2]=posy+altura;
	y[3]=posy+altura;

	C2D2_DesenhaSpriteEfeito(id, indice, x, y, 255,255,255,alpha);
}

int XDesenhaBotao(unsigned int idbot,int indx, int x,int y, unsigned int idcursor,int &alpha )
{
	C2D2_Mouse *mouse = C2D2_PegaMouse();
	//botão normal
	C2D2_DesenhaSprite(idbot,indx,x,y+ydesl);
    //botão selecionado
	XDesenhaSprite(idbot,indx+1,x,y+ydesl,0,0,alpha);

	if(C2D2_ColidiuSprites(idcursor, 1, mouse->x, mouse->y, idbot, indx, x, y))
	{
		if(alpha<250)
			alpha+=25;
		if(mouse->botoes[C2D2_MESQUERDO].pressionado)
			return 1;
		else if(mouse->botoes[C2D2_MESQUERDO].ativo)
			return 2;
		else if(mouse->botoes[C2D2_MESQUERDO].liberado)
			return 3;
	}else
	{
		if(alpha>0)
			alpha-=25;
		return false;
	}
	return NULL;
}

void menu_carrega()
{
    cursor = C2D2_CarregaSpriteSet("./menu/cursor.png",40,40);
    botsmain = C2D2_CarregaSpriteSet("./menu/botsmain.png",220,50);
    botback = C2D2_CarregaSpriteSet("./menu/botback.png",128,104);

    black = C2D2_CarregaSpriteSet("./menu/black.png",0,0);
    backmain = C2D2_CarregaSpriteSet("./menu/backmain.jpg",0,0);
    backajuda = C2D2_CarregaSpriteSet("./menu/backajuda.jpg",0,0);
    backsobre = C2D2_CarregaSpriteSet("./menu/backsobre.jpg",0,0);
    backsobre2 = C2D2_CarregaSpriteSet("./menu/backsobre2.jpg",0,0);
    backgameover= C2D2_CarregaSpriteSet("./menu/gameover.png",0,0);
    backwin= C2D2_CarregaSpriteSet("./menu/win.png",0,0);   

    quadrointro = C2D2_CarregaSpriteSet("./menu/quadrointro.jpg",0,0);
    quadroeremita = C2D2_CarregaSpriteSet("./menu/quadroeremita.jpg",0,0);

    music_menu = CA2_CarregaMusica("./musicas/menu.ogg");
    music_game = CA2_CarregaMusica("./musicas/game.ogg");
    music_over = CA2_CarregaMusica("./musicas/over.ogg");
    music_win = CA2_CarregaMusica("./musicas/win.ogg");
    music_eremita = CA2_CarregaMusica("./musicas/eremita.ogg");

}

void menu_blacklayer()
{
	static C2D2_Botao *teclado = C2D2_PegaTeclas();
	static C2D2_Mouse *mouse = C2D2_PegaMouse();

	//sai com esc
	if(teclado[C2D2_ESC].pressionado)
	{
	    if(estado_atual==TELA_MAIN) estado_atual=SAIR;
        else estado_atual=TELA_MAIN;
	}


    //para efeitos de fade
    if(!fadecontrol && fadealpha >0)
        fadealpha-=25;
    else if(fadecontrol)
    {
        if(fadealpha<250)
                fadealpha+=25;
            else
            {
                encerra=1;
                fadecontrol=false;
            }
    }

    if(estado_atual != TELA_SPLASH
        && estado_atual != TELA_GAMEOVER
        && estado_atual != TELA_INTRO
        && estado_atual != TELA_FIM
        && estado_atual != TELA_EREMITA
       )C2D2_DesenhaSprite(cursor,0,mouse->x,mouse->y+ydesl);

    if(fadealpha > 0)
        XDesenhaSprite(black,0,0,ydesl,1024,600,fadealpha);


}

void menu_splash()
{
   // vetor com alpha de cada botão usado pela XDesenhaBotao
	int balpha[12]={0,0,0,0,0,0,0,0,0,0,0,0};

	int tempo = 120;
	bool carregou = false;

	splash = C2D2_CarregaSpriteSet("./menu/splash.jpg",0,0);

	while(!encerra)
	{
	    //carrega dados
	    if(fadealpha <=5 && !carregou)
        {
            menu_carrega();
            carregou = true;
        }

		if(estado_atual != TELA_SPLASH)
            fadecontrol=true;

        if(tempo > 0)
            tempo --;
        else
            estado_atual=TELA_INTRO;

        C2D2_LimpaTela();
        C2D2_DesenhaSprite(splash,0,0,ydesl);

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}

void menu_main()
{
    if(!tocaMusicaMain)
    {
        CA2_TocaMusica(music_menu,-1);
        tocaMusicaMain = true;
    }

    // vetor com alpha de cada botão usado pela XDesenhaBotao
	int balpha[12]={0,0,0,0,0,0,0,0,0,0,0,0};

	while(!encerra)
	{
		if(estado_atual != TELA_MAIN)
            fadecontrol=true;

		C2D2_LimpaTela();

		C2D2_DesenhaSprite(backmain,0,0,ydesl);

		if(XDesenhaBotao(botsmain,0,735,130,cursor,balpha[0])==1)
        {
           // CA2_TocaEfeito(sombot,0);
            //estado_atual=TELA_MAIN;
            estado_atual=TELA_JOGO;
            tocaMusicaMain=false;
        }
        if(XDesenhaBotao(botsmain,2,735,185,cursor,balpha[1])==1)
        {
           // CA2_TocaEfeito(sombot,0);
            estado_atual=TELA_AJUDA;
        }
        if(XDesenhaBotao(botsmain,4,735,240,cursor,balpha[2])==1)
        {
           // CA2_TocaEfeito(sombot,0);
            estado_atual=TELA_ABOUT;
        }
        if(XDesenhaBotao(botsmain,8,735,295,cursor,balpha[3])==1)
        {
           // CA2_TocaEfeito(sombot,0);
            estado_atual=SAIR;
        }

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}

void menu_ajuda()
{
    // vetor com alpha de cada botão usado pela XDesenhaBotao
	int balpha[12]={0,0,0,0,0,0,0,0,0,0,0,0};

	while(!encerra)
	{
		if(estado_atual != TELA_AJUDA)
            fadecontrol=true;

		C2D2_LimpaTela();

		C2D2_DesenhaSprite(backajuda,0,0,ydesl);

        if(XDesenhaBotao(botback,0,460,490,cursor,balpha[0])==1)
        {
           // CA2_TocaEfeito(sombot,0);
            estado_atual=TELA_MAIN;
        }

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}

void menu_about()
{
// vetor com alpha de cada botão usado pela XDesenhaBotao
	int balpha[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	int estadoAbout = 0;

	while(!encerra)
	{
		if(estado_atual != TELA_ABOUT)
            fadecontrol=true;

		C2D2_LimpaTela();

        !estadoAbout ? C2D2_DesenhaSprite(backsobre,0,0,ydesl) : C2D2_DesenhaSprite(backsobre2,0,0,ydesl);

        if(XDesenhaBotao(botback,0,360,490,cursor,balpha[0])==1)
        {
           // CA2_TocaEfeito(sombot,0);
           if(estadoAbout ==0)
                estado_atual=TELA_MAIN;
            else
                estadoAbout--;
        }

        if(estadoAbout == 0 )
            if(XDesenhaBotao(botback,2,560,490,cursor,balpha[1])==1)
            {
                 estadoAbout++;
            }

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}

void menu_trofeus()
{
    ;
}

void menu_intro()
{
    if(!tocaMusicaMain)
    {
        CA2_TocaMusica(music_menu,-1);
        tocaMusicaMain = true;
    }

    int indxQuadro = 0;
    int tempo = 200;
    int x =1200;
    int y =1200;

    //posicoes dos quadros
    int quadro[8][2] = {{0,0},
                        {-980,110},
                        {0,-365},
                        {-946,-442},
                        {24,-930},
                        {-912,-824},
                        {22,-1450},
                        {-1000,-1430}
                        };
	while(!encerra)
	{
		if(estado_atual != TELA_INTRO)
            fadecontrol=true;

        if(tempo > 0 )
        {
            tempo--;
        }
        else
        {
            tempo = 200;
            if(indxQuadro < 7 )
                indxQuadro++;
            else
                estado_atual=TELA_MAIN;
        }

        //efeito em X
        if(x < quadro[indxQuadro][0])
            x += (quadro[indxQuadro][0] - x)/25 +1;
        else if(x > quadro[indxQuadro][0])
            x -= (x-quadro[indxQuadro][0])/25 +1;

        //efeito em Y
        if(y < quadro[indxQuadro][1])
            y += (quadro[indxQuadro][1] - y)/25 +1;
        else if(y > quadro[indxQuadro][1])
            y -= (y-quadro[indxQuadro][1])/25 +1;

        C2D2_LimpaTela();

        XDesenhaSprite(quadrointro,0,x,y+ydesl,2048,2048,255);
        //C2D2_DesenhaSprite(quadrointro,0,x,y);

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}
void menu_fim()
{
    CA2_TocaMusica(music_win,-1);
    tocaMusicaMain = false;

	int tempo = 180;

	while(!encerra)
	{
		if(estado_atual != TELA_FIM)
            fadecontrol=true;

        if(tempo > 0)
            tempo --;
        else
            estado_atual=TELA_MAIN;
        C2D2_DesenhaSprite(backwin,0,ydesl,0);

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}
void menu_gameover()
{
    CA2_TocaMusica(music_over,-1);
    tocaMusicaMain = false;

	int tempo = 180;

	while(!encerra)
	{
		if(estado_atual != TELA_GAMEOVER)
            fadecontrol=true;

        if(tempo > 0)
            tempo --;
        else
            estado_atual=TELA_MAIN;
        C2D2_DesenhaSprite(backgameover,0,ydesl,0);

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}

void menu_eremita()
{
    CA2_TocaMusica(music_eremita,-1);
    tocaMusicaMain = false;

    int indxQuadro = 0;
    int tempo = 200;
    int x =1200;
    int y =1200;

    //posicoes dos quadros
    int quadro[8][2] = {{0,0},
                        {-980,110},
                        {0,-365},
                        {-946,-442},
                        {24,-930},
                        {-912,-824},
                        {22,-1450},
                        {-1000,-1430}
                        };
	while(!encerra)
	{
		if(estado_atual != TELA_EREMITA)
            fadecontrol=true;

        if(tempo > 0 )
        {
            tempo--;
        }
        else
        {
            tempo = 200;
            if(indxQuadro < 7 )
                indxQuadro++;
            else
                estado_atual=TELA_MAIN;
        }

        //efeito em X
        if(x < quadro[indxQuadro][0])
            x += (quadro[indxQuadro][0] - x)/25 +1;
        else if(x > quadro[indxQuadro][0])
            x -= (x-quadro[indxQuadro][0])/25 +1;

        //efeito em Y
        if(y < quadro[indxQuadro][1])
            y += (quadro[indxQuadro][1] - y)/25 +1;
        else if(y > quadro[indxQuadro][1])
            y -= (y-quadro[indxQuadro][1])/25 +1;

        C2D2_LimpaTela();

        XDesenhaSprite(quadroeremita,0,x,y+ydesl,2048,2048,255);
       // C2D2_DesenhaSprite(backmain,0,x,y);

		//esse é o menu da esquerda
		menu_blacklayer();

		C2D2_Sincroniza(60);
	}
}
