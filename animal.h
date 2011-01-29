#ifndef ANIMAL_H
#define ANIMAL_H

#include <c2d2/ator.h>

// Enumeração dos estados dos animais do jogo
enum 
{
	ANIMAL_ANDANDO=ATOR_PROG_INI, 
	ANIMAL_MORRENDO,
	ANIMAL_PREPARA_ATAQUE,
	ANIMAL_ATACANDO
};

enum
{
	ANIM_ANDANDO_DIREITA,
	ANIM_ANDANDO_ESQUERDA,
	ANIM_MORRENDO
};

struct InfoAnimal
{
	int velocidade;
	int velocidadeAtaque;

	int tempoBote;
	int tempoAtaque;
};

bool AtualizaAnimal(Ator *a, InfoAnimal *info, unsigned int mapa);

#endif
