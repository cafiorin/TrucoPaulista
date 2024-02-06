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
	//Jogador* Dupla1[2];

	int NumeroDaRodada;
	int QuantoValeARodada;
	int QuantasVezesTrucou;
	bool JogoDeDupla;

public:
	RodadasController(Placar* placar, Carta* vira, bool jogoDeDuplas, int valorRodada, int quantasVezesTrucou, int numRodada): 
		placar_(placar),  Vira(vira), JogoDeDupla(jogoDeDuplas), 
		QuantoValeARodada(valorRodada), QuantasVezesTrucou(quantasVezesTrucou),
		NumeroDaRodada(numRodada){}
	RodadasController(Placar *placar, bool jogoDeDuplas);
	~RodadasController();

	void RecriarRodada(Rodada* rodada[3], int numeroRodadaAtual);

	int QualRodadaEsta() { return NumeroDaRodada; }
	void ProximaRodada() { if (NumeroDaRodada < 3) NumeroDaRodada++; }
	bool EhAUltimaRodada() { return NumeroDaRodada == 3; }
	int NumeroDeJogadores() { return (JogoDeDupla ? 4 : 2); }

	int IndiceDaRodadaAtual() { return NumeroDaRodada - 1; }
	Rodada* PegarRodadaAtual() { return Rodadas[IndiceDaRodadaAtual()]; }
	Rodada* PegarRodada(int indiceRodada) { return Rodadas[indiceRodada]; }
	bool RodadaEstaCompleta();
	bool RodadaEstaComecando();
	Jogador* QuemGanhouARodadaAtual();
	Jogador* QuemGanhouUltimaRodada();
	Jogador* JaTemosUmVencedor();

	CString ObterMensagemDeQuantoVale()
	{
		CString resultado;

		switch (QuantoValeARodada)
		{
		case 3:
			resultado = _T("Seis");
			break;
		case 6:
			resultado = _T("Nove");
			break;
		case 9:
			resultado = _T("Doze");
			break;
		default:
			resultado = _T("Truco");
			break;
		}

		return resultado;
	}


	bool BotFezAPrimeira();

	int QuantoEstaValendoARodada() { return QuantoValeARodada; }

	bool PodeTrucarAinda() { return (QuantasVezesTrucou <= 4); }


	void TrucoAceitoParaRodada() 
	{
		if (PodeTrucarAinda())
			QuantasVezesTrucou++;

		QuantoValeARodada = 3 * QuantasVezesTrucou;	
	}

	int QuantosVezesTrucou() const {
		return QuantasVezesTrucou;
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
		//Dupla1[0] = duplas[0];
		//Dupla1[1] = duplas[1];
	}

	// Metodos usados para o Bot tomar alguma decisao
	NumeroDaRodadaAtual RetornarNumeroDaRodadaAtual();
	std::pair<const Carta*, bool> RetornarCartaMaisAltaDaRodadaESeEhDaDupla(Jogador* jogador_atual);
	bool BotEstaoPerdendo();
	bool JogadoresSaoDupla(Jogador* jogador1, Jogador* jogador2);

};


