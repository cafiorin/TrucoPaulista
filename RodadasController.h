#pragma once

#include "Rodada.h"

class RodadasController
{
private:
	Rodada* Rodadas[3];

	int NumeroDaRodada;
	int QuantoValeARodada;
	int QuantasVezesTrucou;
	bool JogoDeDupla;

public:
	RodadasController(bool jogoDeDuplas);
	~RodadasController();

	int QualRodadaEsta() { return NumeroDaRodada; }
	void ProximaRodada() { if (NumeroDaRodada < 3) NumeroDaRodada++; }
	bool EhAUltimaRodada() { return NumeroDaRodada == 3; };

	int IndiceDaRodadaAtual() { return NumeroDaRodada - 1; };
	bool RodadaEstaCompleta() { return (Rodadas[IndiceDaRodadaAtual()]->CartasAdicionadas == (JogoDeDupla ? 4 : 2)); }
	bool RodadaEstaComecando() {return (Rodadas[IndiceDaRodadaAtual()]->CartasAdicionadas == 0);}
	Jogador* QuemGanhouARodadaAtual() { return Rodadas[IndiceDaRodadaAtual()]->QuemGanhou(); }
	Jogador* JaTemosUmVencedor();

	int QuantoEstaValendoARodada() { return QuantoValeARodada; }

	bool PodeTrucarAinda() { return (QuantasVezesTrucou <= 4); }


	void TrucoAceitoParaRodada() 
	{
		if (PodeTrucarAinda())
			QuantasVezesTrucou++;

		QuantoValeARodada = 3 * QuantasVezesTrucou;	
	}

	void InicializarRodada(Carta* vira);
	
	void CartaJogada(const Carta* carta, Jogador* jogador )
	{
		Rodadas[IndiceDaRodadaAtual()]->CartaJogada(*carta, *jogador);
	}

	bool RetornarSeEhPrimeiroParaJogarNaRodadaAtual()
	{
		return Rodadas[IndiceDaRodadaAtual()]->RetornarSeEhPrimeiroParaJogar();
	}

	CartaDaRodada* RetornaMaiorCartaDaRodadaAtual()
	{
		return Rodadas[NumeroDaRodada]->RetornaMaiorCartaDaRodada();
	}
};


