#pragma once

class Rodada;
class Jogador;
class Carta;
class CartaDaRodada;

class RodadasController
{

private:
	Rodada* Rodadas[3];
	Carta* Vira;

	int NumeroDaRodada;
	int QuantoValeARodada;
	int QuantasVezesTrucou;
	bool JogoDeDupla;

public:
	RodadasController(bool jogoDeDuplas);
	~RodadasController();

	int QualRodadaEsta() { return NumeroDaRodada; }
	void ProximaRodada() { if (NumeroDaRodada < 3) NumeroDaRodada++; }
	bool EhAUltimaRodada() { return NumeroDaRodada == 3; }
	int NumeroDeJogadores() { return (JogoDeDupla ? 4 : 2); }

	int IndiceDaRodadaAtual() { return NumeroDaRodada - 1; }
	bool RodadaEstaCompleta();
	bool RodadaEstaComecando();
	Jogador* QuemGanhouARodadaAtual();
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

	Carta* QualOVira() { return Vira; }
	void CartaJogada(const Carta* carta, Jogador* jogador);
	bool RetornarSeEhPrimeiroParaJogarNaRodadaAtual();
	CartaDaRodada* RetornaMaiorCartaDaRodadaAtual();

	int MaiorCarta(const Carta* carta1, const Carta* carta2);
};


