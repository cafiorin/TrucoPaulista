#include "pch.h"
#include "Rodada.h"
#include "Jogador.h"

void Rodada::CartaJogada(const Carta& carta, Jogador& jogador)
{
	CartaDaRodada* cartaRodada = new CartaDaRodada(NumeroDaRodada);
	cartaRodada->CartaJogada(carta, jogador);
	cartas[CartasAdicionadas] = cartaRodada;
	jogador.CartaQueFoiUsada(&carta);
	CartasAdicionadas++;
}

CartaDaRodada* Rodada::RetornaMaiorCartaDaRodada() 
{
	int indice_maior_carta = 0;
	int maior_valor = 0;

	for (int i = 0; i < CartasAdicionadas; i++) 
	{
		CartaDaRodada* carta = cartas[i];
		if (carta && 
			!carta->CartaCoberta && 
			carta->CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira()) >= maior_valor) 
		{
			indice_maior_carta = i;
		}
	}

	return cartas[indice_maior_carta] && !cartas[indice_maior_carta]->CartaCoberta ? cartas[indice_maior_carta] : nullptr;
}