#include "pch.h"
#include "CartaDaRodada.h"

CartaDaRodada::CartaDaRodada(int Rodada):NumeroDaRodada(Rodada)
{
	CartaCoberta = false;
	CartaJogadaNaRodada = nullptr;
	JogadorDaCarta = nullptr;
}

void CartaDaRodada::CartaJogada(Carta& carta, Jogador& jogador)
{
	if (&carta != nullptr)
	{
		CartaJogadaNaRodada = &carta;
	}
	else
	{
		CartaCoberta = true;
	}

	JogadorDaCarta = &jogador;
}
