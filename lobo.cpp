#include <c2d2/chien2d2.h>

#include "animal.h"
#include "jogo_atores.h"
#include "lobo.h"

//Animacao 
Animacao animLobo[] =
{
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	// BOLA_PULA direita : 0
	{8, 5, {0, 1, 2, 3, 4, 5, 6, 7}},
	// BOLA_PULA esquerda : 1
	{8, 5, {8, 9, 10, 11, 12, 13, 14, 15}},
	// bola morreu: 2
	{2, 20, {0,5}},
	// bola escondida
	{10, 10, {16,16,16,16,16,16,16,16,16,17}}
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
        // Número de sons do lobo
        6
};

char *sonsLobo[]={
	"audio/lobo1.ogg",
        "audio/lobo2.ogg",
        "audio/lobo3.ogg",
        "audio/lobo4.ogg",
        "audio/lobo5.ogg",
        "audio/lobo6.ogg"
};


static bool AtualizaLobo(Ator *a, unsigned int mapa);

bool CarregaLobo()
{
	return ATOR_CarregaAtorEstatico(
		LOBO, 
		"imagens/lobo.png", 
		64, 
		64, 
		4, 
		5,
		64, 
		64, 
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
