#include "pch.h"
#include "Rodada.h"

void Rodada::CartaJogada(const Carta& carta, Jogador& Jogador)
{
	 CartaDaRodada* cartaRodada = new CartaDaRodada(NumeroDaRodada);
	 cartaRodada->CartaJogada(carta, Jogador);
	 cartas[CartasAdicionadas] = cartaRodada;

	 CartasAdicionadas++;
}