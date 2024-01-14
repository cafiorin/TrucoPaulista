#include "pch.h"
#include "RodadasController.h"


RodadasController::RodadasController(bool jogoDeDupla)
{
	NumeroDaRodada = 1;
	QuantoValeARodada = 1;
	QuantasVezesTrucou = 0;
	JogoDeDupla = jogoDeDupla;

	Rodadas[0] = nullptr;
	Rodadas[1] = nullptr;
	Rodadas[2] = nullptr;
}


RodadasController::~RodadasController()
{
	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];
}

void RodadasController::InicializarRodada(Carta *vira)
{
	NumeroDaRodada = 1;
	QuantoValeARodada = 1;
	QuantasVezesTrucou = 0;

	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	Rodadas[0] = new Rodada(1, vira, JogoDeDupla ? 4 : 2);
	Rodadas[1] = new Rodada(2, vira, JogoDeDupla ? 4 : 2);
	Rodadas[2] = new Rodada(3, vira, JogoDeDupla ? 4 : 2);
}

Jogador* RodadasController::JaTemosUmVencedor()
{
	if (NumeroDaRodada > 1 && RodadaEstaCompleta())
	{
		if (NumeroDaRodada == 2)
		{
			if (Rodadas[0]->FoiEmpate())
			{
				return Rodadas[1]->QuemGanhou();
			}

			if (Rodadas[1]->FoiEmpate())
			{
				return Rodadas[0]->QuemGanhou();
			}

			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou())
			{
				return Rodadas[0]->QuemGanhou();
			}
		}
		else if (NumeroDaRodada == 3)
		{
			if (Rodadas[2]->FoiEmpate())
			{
				return Rodadas[0]->QuemGanhou();
			}

			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou() ||
				Rodadas[0]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				return Rodadas[0]->QuemGanhou();
			}
			else if (Rodadas[1]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				return Rodadas[1]->QuemGanhou();
			}
		}
	}

	return nullptr;
}
