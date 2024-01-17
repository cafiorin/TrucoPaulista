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
			CartaDaRodada tempCartas[] = { *cartas[0], *cartas[1], *cartas[2], *cartas[3] };

			std::sort(std::begin(tempCartas), std::end(tempCartas),
				[this](const CartaDaRodada& a, const CartaDaRodada& b)
				{
					return (Rodadas->MaiorCartaDaRodada(&a, &b) == 1);
				});

			if(tempCartas[3].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira()) == tempCartas[2].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira())
				&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroJogador() == 1 && tempCartas[2].JogadorDaCarta->ObtemNumeroJogador() == 3) == false) 
				&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroJogador() == 3 && tempCartas[2].JogadorDaCarta->ObtemNumeroJogador() == 1) == false)
				&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroJogador() == 2 && tempCartas[2].JogadorDaCarta->ObtemNumeroJogador() == 4) == false)
				&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroJogador() == 4 && tempCartas[2].JogadorDaCarta->ObtemNumeroJogador() == 2) == false))
				return nullptr;

			return (tempCartas[3].JogadorDaCarta);
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

