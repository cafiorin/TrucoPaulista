#include "pch.h"
#include "Rodada.h"

void Rodada::CartaJogada(const Carta& carta, Jogador& Jogador)
{
	CartaDaRodada* cartaRodada = new CartaDaRodada(NumeroDaRodada);
	cartaRodada->CartaJogada(carta, Jogador);
	cartas[CartasAdicionadas] = cartaRodada;

	CartasAdicionadas++;
}

CartaDaRodada* Rodada::RetornaMaiorCartaDaRodada() {
	int i = 0;
	int indice_maior_carta = 0;
	int maior_valor = 0;

	for (CartaDaRodada* carta : cartas) {
		if (carta && !carta->CartaCoberta && carta->CartaJogadaNaRodada->ObtemValor(Vira) >= maior_valor) {
			indice_maior_carta = i;
		}
		i++;
	}

	return cartas[indice_maior_carta] && !cartas[indice_maior_carta]->CartaCoberta ? cartas[indice_maior_carta] : nullptr;
}