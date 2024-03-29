#include "rato.h"

#include <c2d2/chien2d2.h>
#include <c2d2/ator.h>

#include "animal.h"
#include "jogo_atores.h"

static bool AtualizaRato(Ator *a, unsigned int mapa);

Animacao animRato[] ={
	// Ordem: n�mero de quadros, tempo entre os quadros, vetor com a seq��ncia de quadros
	//  direita: 0
	{1, 1, {0}},
	//  esquerda: 1
	{1, 1, {0}},
	// ATOXADO_MORRENDO: 9
	{1, 1, {0}},
	// bola escondida
	{10, 8, {1,1,1,1,1,1,1,1,1,2}}
};

char *sonsRato[]={
	"audio/rato1.ogg",
	"audio/rato2.ogg",
        "audio/rato3.ogg",
	"audio/rato4.ogg"
};

InfoAnimal infoRato = {
	//velocidade
	1,
	//velocidade ataque
	7,
	//tempo bote
	60,
	//tempo ataque
	50,
	//tempo esconderijo
	300,
        // Número de sons
        4
};


bool CarregaRato()
{
	return ATOR_CarregaAtorEstatico(
		RATO, 
		"imagens/rato.png", 
		64, 
		28, 
		1, 
		3,
		64, 
		28, 
		animRato, 
		false, 
		sonsRato,
		4,
		&AtualizaRato
	);
}



static bool AtualizaRato(Ator *a, unsigned int mapa)
{
	return AtualizaAnimal(a, &infoRato, mapa);
}
