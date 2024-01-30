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

	void CartaJogada(const Carta& carta, Jogador& Jogador, bool cartaCoberta);

	Jogador* QuemGanhou()
	{
		if (Rodadas->NumeroDeJogadores() == 2) 
		{
			if (Rodadas->MaiorCartaDaRodada(cartas[0], cartas[1]) == 0)
				return cartas[0]->JogadorDaCarta;

			if (Rodadas->MaiorCartaDaRodada(cartas[0], cartas[1]) == -1)
				return nullptr;
		
			return cartas[1]->JogadorDaCarta; //quando tiver duplas move pra dentro do if
		}

		//4 jogadores
		Jogador* ganhou = nullptr;
		CartaDaRodada tempCartas[] = { *cartas[0], *cartas[1], *cartas[2], *cartas[3] };

		std::sort(std::begin(tempCartas), std::end(tempCartas),
			[this](const CartaDaRodada& a, const CartaDaRodada& b)
			{
				return (Rodadas->MaiorCartaDaRodada(&a, &b) == 1);
			});

		if (tempCartas[3].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira()) == tempCartas[2].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira())
			&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroDaDupla() != tempCartas[2].JogadorDaCarta->ObtemNumeroDaDupla())))
			return nullptr; //empate

		return (tempCartas[3].JogadorDaCarta);
	}

	bool FoiEmpate()
	{
		if (Rodadas->NumeroDeJogadores() == 2) //1 contra 1
		{
			return (Rodadas->MaiorCartaDaRodada(cartas[0], cartas[1]) == -1);
		}
		else
		{
			//4 jogadores
			Jogador* ganhou = nullptr;
			CartaDaRodada tempCartas[] = { *cartas[0], *cartas[1], *cartas[2], *cartas[3] };

			std::sort(std::begin(tempCartas), std::end(tempCartas),
				[this](const CartaDaRodada& a, const CartaDaRodada& b)
				{
					return (Rodadas->MaiorCartaDaRodada(&a, &b) == 1);
				});

			if (tempCartas[3].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira()) == tempCartas[2].CartaJogadaNaRodada->ObtemValor(Rodadas->QualOVira())
				&& ((tempCartas[3].JogadorDaCarta->ObtemNumeroDaDupla() != tempCartas[2].JogadorDaCarta->ObtemNumeroDaDupla())))
				return true; //empate

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

