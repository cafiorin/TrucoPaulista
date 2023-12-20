#pragma once

#include "Placar.h"
#include "Jogador.h"
#include "Rodada.h"
#include "Baralho.h"


class Partida
{
public:
	int NumeroDaRodada;
	Jogador* QuemComecaRodada;
	int QuantoValeARodada;

	Placar* placar;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];
	
	Rodada* Rodadas[3];

	Baralho* BaralhoMesa;
	Carta* Vira;

	Partida()
	{
		placar = new Placar();
		NumeroDaRodada = 1;

		Dupla1[0] = new Jogador(1, "Humano1");
		Dupla1[1] = new Jogador(3, "Humano2");
		Dupla2[0] = new Jogador(2, "Bot1");
		Dupla2[1] = new Jogador(4, "Bot2");

		Rodadas[0] = new Rodada(1);
		Rodadas[1] = new Rodada(2);
		Rodadas[2] = new Rodada(3);

		BaralhoMesa = new Baralho();
		Vira = nullptr;
	}

	void InicializarPartida();

	void InicializarRodada();

};

