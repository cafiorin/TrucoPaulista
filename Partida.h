#pragma once

#include "Placar.h"
#include "Jogador.h"
#include "Rodada.h"
#include "Baralho.h"


class Partida
{
private:
	int NumeroDaRodada;
	Jogador* QuemComecaRodada;
	int QuantoValeARodada;

	Placar* placar;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	Rodada* Rodadas[3];

	Baralho* BaralhoMesa;
	Carta* Vira;

public:

	Partida();

	void InicializarPartida();

	void InicializarRodada();

	void DistribuiCartas();

	void DistribuiCartaProJogador(Jogador* jogador);

	Jogador* ObtemJogadorHumano1();

	Carta* ObtemVira() { return Vira; }

};

