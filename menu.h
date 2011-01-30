#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <c2d2/chien2d2_interno.h>
#include <c2d2/chien2d2.h>
#include <c2d2/chienaudio2.h>


#define LARGURA_TELA    1024
#define ALTURA_TELA    600
#define ALTURA_TELA2    768

enum {TELA_SPLASH, TELA_MAIN, TELA_AJUDA, TELA_ABOUT ,TELA_TROFEUS,TELA_INTRO,TELA_FIM,TELA_GAMEOVER,TELA_EREMITA, TELA_JOGO, SAIR};

extern int ydesl;
extern bool telaCheia;


extern int estado_atual;

extern int encerra;
extern int fadealpha;
extern bool fadecontrol;

void XDesenhaSprite(unsigned int id,unsigned int indice,int posx, int posy,int largura,int altura,int alpha);
int XDesenhaBotao(unsigned int idbot,int indx, int x,int y, unsigned int idcursor,int &alpha );

void menu_carrega();

//telas
void menu_main();
void menu_ajuda();
void menu_splash();
void menu_about();
void menu_trofeus();
void menu_intro();
void menu_fim();
void menu_gameover();
void menu_eremita();


#endif
