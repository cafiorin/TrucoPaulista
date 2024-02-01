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
		CartaDaRodada(int numRodada, bool cartaCoberta, const Carta *cartaJogada, Jogador *jogador) : NumeroDaRodada(numRodada),
																									  CartaCoberta(cartaCoberta),
																									  CartaJogadaNaRodada(cartaJogada),
																									  JogadorDaCarta(jogador)
		{ }
		void CartaJogada(const Carta& carta, Jogador& jogador);
};

