#pragma once

class Rodada;
class Jogador;
class Carta;
class CartaDaRodada;
class Placar;

class RodadasController
{

private:
	Rodada* Rodadas[3];
	Carta* Vira;
	Placar* placar_;
	Jogador* Dupla1[2];

	int NumeroDaRodada;
	int QuantoValeARodada;
	int QuantasVezesTrucou;
	bool JogoDeDupla;

public:
	RodadasController(Placar *placar, bool jogoDeDuplas);
	~RodadasController();

	int QualRodadaEsta() { return NumeroDaRodada; }
	void ProximaRodada() { if (NumeroDaRodada < 3) NumeroDaRodada++; }
	bool EhAUltimaRodada() { return NumeroDaRodada == 3; }
	int NumeroDeJogadores() { return (JogoDeDupla ? 4 : 2); }

	int IndiceDaRodadaAtual() { return NumeroDaRodada - 1; }
	Rodada* PegarRodadaAtual() { return Rodadas[IndiceDaRodadaAtual()]; }
	bool RodadaEstaCompleta();
	bool RodadaEstaComecando();
	Jogador* QuemGanhouARodadaAtual();
	Jogador* JaTemosUmVencedor();

	bool BotFezAPrimeira();

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
	void CartaJogada(const Carta* carta, Jogador* jogador, bool cartaCoberta);
	const Carta* QualCartaJogadaNaRodada();
	bool RetornarSeEhPrimeiroParaJogarNaRodadaAtual();
	CartaDaRodada* RetornaMaiorCartaDaRodadaAtual();
	int MaiorCartaDaRodada(const CartaDaRodada* carta1, const CartaDaRodada* carta2);

	int MaiorCarta(const Carta* carta1, const Carta* carta2);

	void SetPlacar(Placar* placar) { placar_ = placar; };
	void SetDuplas(Jogador* duplas[2]) { 
		Dupla1[0] = duplas[0];
		Dupla1[1] = duplas[1];
	}

	// Metodos usados para o Bot tomar alguma decisao
	NumeroDaRodadaAtual RetornarNumeroDaRodadaAtual();
	std::pair<const Carta*, bool> RetornarCartaMaisAltaDaRodadaESeEhDaDupla(Jogador* jogador_atual);
	bool BotEstaoPerdendo();
	bool JogadoresSaoDupla(Jogador* jogador1, Jogador* jogador2);

};


