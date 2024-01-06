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
	Jogador* UltimoQueJogouACarta;

	int QuantoValeARodada;
	int QuantosJogadores = 2;
	Placar* placar;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	Rodada* Rodadas[3];

	Baralho* BaralhoMesa;
	Carta* Vira;

public:

	Partida();
	~Partida();
	
	void InicializarPartida(int quantosJogadores);

	void InicializarPartidaCliente();

	void InicializarRodada();

	void DistribuiCartas();

	void DistribuiCartaProJogador(Jogador* jogador);
	void GanhouPartida();
	Jogador* ObtemJogadorHumano1();

	Jogador* ObtemJogadorBot1();

	Carta* ObtemVira() { return Vira; }

	int ObtemNumeroDeJogadores() { return QuantosJogadores; }

	void JogadorJogouACarta(Jogador* jogador, const Carta* carta);

	Jogador* QuemJoga();

};

