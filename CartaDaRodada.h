#pragma once

#include "Carta.h"
#include "Jogador.h"

class CartaDaRodada
{
	public:
		int NumeroDaRodada = 0;
		bool CartaCoberta;
		Carta *CartaJogadaNaRodada;
		Jogador* JogadorDaCarta;

		CartaDaRodada(int Rodada);
		void CartaJogada(Carta& carta, Jogador& jogador);
};

