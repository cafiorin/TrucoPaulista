#pragma once

#include "CartaDaRodada.h"
#include "RodadasController.h"
#include <algorithm>

class Rodada
{
public:

	int NumeroDaRodada;
	int CartasAdicionadas;
	CartaDaRodada* cartas[4];
	RodadasController* Rodadas;

	Rodada(int rodada , RodadasController* rodadas) : NumeroDaRodada(rodada)
	{
		Rodadas = rodadas;
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
		if (Rodadas->NumeroDeJogadores() == 2) 
		{
			if (Rodadas->MaiorCarta(cartas[0]->CartaJogadaNaRodada, cartas[1]->CartaJogadaNaRodada) == 0)
				return cartas[0]->JogadorDaCarta;

			if (Rodadas->MaiorCarta(cartas[0]->CartaJogadaNaRodada, cartas[1]->CartaJogadaNaRodada) == -1)
				return nullptr;
		}
		else
		{
			Jogador* ganhou = nullptr;
			Carta tempCartas[] = { *cartas[0]->CartaJogadaNaRodada, *cartas[1]->CartaJogadaNaRodada, *cartas[2]->CartaJogadaNaRodada, *cartas[3]->CartaJogadaNaRodada };

			std::sort(std::begin(tempCartas), std::end(tempCartas),
				[this](const Carta& a, const Carta& b)
				{
					return (Rodadas->MaiorCarta(&a, &b) == 1);
				});

			if(tempCartas[3].ObtemValor(Rodadas->QualOVira()) == tempCartas[2].ObtemValor(Rodadas->QualOVira()))
				return nullptr;

			if (tempCartas[3].id == cartas[0]->CartaJogadaNaRodada->id)
				return cartas[0]->JogadorDaCarta;

			if (tempCartas[3].id == cartas[1]->CartaJogadaNaRodada->id)
				return cartas[0]->JogadorDaCarta;

			if (tempCartas[3].id == cartas[2]->CartaJogadaNaRodada->id)
				return cartas[0]->JogadorDaCarta;

			return cartas[3]->JogadorDaCarta;
		}
		return cartas[1]->JogadorDaCarta; //quando tiver duplas move pra dentro do if
	}

	bool FoiEmpate()
	{
		if (cartas[2] == nullptr) //1 contra 1
		{
			return (Rodadas->MaiorCarta(cartas[0]->CartaJogadaNaRodada, cartas[1]->CartaJogadaNaRodada) == -1);
		}
		else
		{
			Jogador* ganhou = nullptr;
			Carta tempCartas[] = { *cartas[0]->CartaJogadaNaRodada, *cartas[1]->CartaJogadaNaRodada, *cartas[2]->CartaJogadaNaRodada, *cartas[3]->CartaJogadaNaRodada };

			std::sort(std::begin(tempCartas), std::end(tempCartas),
				[this](const Carta& a, const Carta& b)
				{
					return (Rodadas->MaiorCarta(&a, &b) == 1);
				});

			return (tempCartas[3].ObtemValor(Rodadas->QualOVira()) == tempCartas[2].ObtemValor(Rodadas->QualOVira()));
		}
		return false; //quando tiver duplas move pra dentro do if
	}

	CartaDaRodada* RetornaMaiorCartaDaRodada();

	bool RetornarSeEhPrimeiroParaJogar()
	{
		if (Rodadas->NumeroDeJogadores() == 2)
		{
			return (CartasAdicionadas == 0);
		}
		else
		{
			return (CartasAdicionadas == 0 || CartasAdicionadas == 1);
		}
	}


};

