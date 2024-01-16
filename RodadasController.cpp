#include "pch.h"

#include "Rodada.h"
#include "Carta.h"
#include "Jogador.h"
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
	Vira = nullptr;
}


RodadasController::~RodadasController()
{
	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];
}

void RodadasController::InicializarRodada(Carta *vira)
{
	Vira = vira;

	NumeroDaRodada = 1;
	QuantoValeARodada = 1;
	QuantasVezesTrucou = 0;

	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	Rodadas[0] = new Rodada(1, this);
	Rodadas[1] = new Rodada(2, this);
	Rodadas[2] = new Rodada(3, this);
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

bool RodadasController::RodadaEstaCompleta()
{ 
	return (Rodadas[IndiceDaRodadaAtual()]->CartasAdicionadas == (JogoDeDupla ? 4 : 2)); 
}

bool RodadasController::RodadaEstaComecando()
{ 
	return (Rodadas[IndiceDaRodadaAtual()]->CartasAdicionadas == 0); 
}

Jogador* RodadasController::QuemGanhouARodadaAtual()
{ 
	return Rodadas[IndiceDaRodadaAtual()]->QuemGanhou(); 
}

void RodadasController::CartaJogada(const Carta* carta, Jogador* jogador)
{
	Rodadas[IndiceDaRodadaAtual()]->CartaJogada(*carta, *jogador);
}

const Carta* RodadasController::QualCartaJogadaNaRodada()
{
	return Rodadas[IndiceDaRodadaAtual()]->cartas[0]->CartaJogadaNaRodada;
}


bool RodadasController::RetornarSeEhPrimeiroParaJogarNaRodadaAtual()
{
	return Rodadas[IndiceDaRodadaAtual()]->RetornarSeEhPrimeiroParaJogar();
}

CartaDaRodada* RodadasController::RetornaMaiorCartaDaRodadaAtual()
{
	return Rodadas[NumeroDaRodada]->RetornaMaiorCartaDaRodada();
}

int RodadasController::MaiorCarta(const Carta* carta1, const Carta* carta2)
{
	int valor1 = carta1->ObtemValor(Vira);
	int valor2 = carta2->ObtemValor(Vira);

	if (valor1 > valor2)
		return 0;

	if (valor1 == valor2)
		return -1;

	return 1;
}

bool RodadasController::BotFezAPrimeira()
{
	return (Rodadas[0]->QuemGanhou() != nullptr && Rodadas[0]->QuemGanhou()->EhUmBot());
}
