#pragma once

#include "Carta.h"
#include "Jogador.h"

class CartaDaRodada
{
	public:
		int NumeroDaRodada = 0;
		bool CartaCoberta;
		const Carta *CartaJogadaNaRodada;
		Jogador* JogadorDaCarta;

		CartaDaRodada(int Rodada);
		void CartaJogada(const Carta& carta, Jogador& jogador);
};

