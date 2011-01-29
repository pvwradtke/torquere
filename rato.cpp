#include "rato.h"

#include <c2d2/chien2d2.h>
#include <c2d2/ator.h>

#include "animal.h"
#include "jogo_atores.h"

static bool AtualizaRato(Ator *a, unsigned int mapa);

Animacao animRato[] ={
	// Ordem: número de quadros, tempo entre os quadros, vetor com a seqüência de quadros
	//  direita: 0
	{1, 1, {1}},
	//  esquerda: 1
	{1, 1, {4}},
	// ATOXADO_MORRENDO: 9
	{1, 1, {12}}
};

InfoAnimal infoRato = {
	//velocidade
	1,
	//velocidade ataque
	8,
	//tempo bote
	60,
	//tempo ataque
	100
};


bool CarregaRato()
{
	return ATOR_CarregaAtorEstatico(
		RATO, 
		"imagens/darkphoenix.png", 
		32, 
		42, 
		4, 
		2,
		24, 
		39, 
		animRato, 
		false, 
		0, 
		0, 
		&AtualizaRato
	);
}



static bool AtualizaRato(Ator *a, unsigned int mapa)
{
	return AtualizaAnimal(a, &infoRato, mapa);
}
