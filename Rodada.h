#pragma once


#include "CartaDaRodada.h"


class Rodada
{
public:

	int NumeroDaRodada;
	int CartasAdicionadas;
	CartaDaRodada* cartas[4];
	Carta* Vira;
	int QuantosJogadores;

	Rodada(int rodada , Carta *vira, int quantosJogadores) : NumeroDaRodada(rodada), QuantosJogadores(quantosJogadores)
	{
		Vira = vira;
		CartasAdicionadas = 0;


		cartas[0] = nullptr;
		cartas[1] = nullptr;
		cartas[2] = nullptr;
		cartas[3] = nullptr;
	}

	~Rodada()
	{
		delete cartas[0];
		delete cartas[1];
		delete cartas[2];
		delete cartas[3];
	}

	void CartaJogada(const Carta& carta, Jogador& Jogador);

	Jogador* QuemGanhou()
	{
		if (cartas[2] == nullptr) //1 contra 1
		{
			if (MaiorCarta(cartas[0]->CartaJogadaNaRodada, cartas[1]->CartaJogadaNaRodada) == 0)
				return cartas[0]->JogadorDaCarta;
		}
		else
		{
			//TODO: Duplas
		}
		return cartas[1]->JogadorDaCarta; //quando tiver duplas move pra dentro do if
	}

	int MaiorCarta(const Carta* carta1, const Carta* carta2)
	{
		if (carta1->ObtemValor(Vira) > carta2->ObtemValor(Vira))
			return 0;

		return 1;
	}

};

