#pragma once

#include "CartaDaRodada.h"
#include "RodadasController.h"

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
			//TODO: Duplas
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
			//TODO: Duplas
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

