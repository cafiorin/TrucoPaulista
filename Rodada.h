#pragma once


#include "CartaDaRodada.h"


class Rodada
{
public:

	int NumeroDaRodada;
	int CartasAdicionadas;
	CartaDaRodada* cartas[4];

	Rodada(int _rodada) : NumeroDaRodada(_rodada)
	{
		CartasAdicionadas = 0;
	}

	void CartaJogada(const Carta& carta, Jogador& Jogador);
};

