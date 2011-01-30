#include <c2d2/chien2d2.h>

#include "animal.h"
#include "jogo_atores.h"
#include "lobo.h"

char *sonsLobo[]={
	"audio/lobo1.ogg",
	"audio/lobo2.ogg",
	"audio/lobo3.ogg",
	"audio/lobo4.ogg",
        "audio/lobo5.ogg",
	"audio/lobo6.ogg"
};

//Animacao 
Animacao animLobo[] =
{
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	// BOLA_PULA ESQUERDA : 0
	{10, 5, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}},
	// BOLA_PULA direita : 1
	{10, 5, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}},
	// bola morreu: 2
	{2, 20, {0,5}},
	// bola escondida
	{1, 20, {0}}
};

InfoAnimal infoLobo = {
	//velocidade
	2,
	//velocidade ataque
	9,
	//tempo Bote
	50,
	//tempo ataque
	90,
	//tempo esconderijo
	300,
        // Quantidade de sons
        6
};

static bool AtualizaLobo(Ator *a, unsigned int mapa);

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
		sonsLobo,
		6,
		&AtualizaLobo
	);
}


static bool AtualizaLobo(Ator *a, unsigned int mapa)
{
	return AtualizaAnimal(a, &infoLobo, mapa);
}
