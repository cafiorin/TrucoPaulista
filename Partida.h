#pragma once

#include "Placar.h"
#include "Jogador.h"
#include "Rodada.h"
#include "Baralho.h"
#include "IEventosDaPartida.h"


class Partida
{
private:
	int NumeroDaRodada;
	Jogador* QuemComecaRodada;
	Jogador* UltimoJogadorAJogar;

	int QuantoValeARodada;
	int QuantasVezesTrucou;
	int QuantosJogadores = 2;
	Placar* placar;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	Rodada* Rodadas[3];

	Baralho* BaralhoMesa;
	Carta* Vira;
	IEventosDaPartida* EventosDaPartida;

public:

	Partida(IEventosDaPartida* eventosPartida);
	~Partida();
	
	void InicializarPartida(int quantosJogadores);

	void InicializarPartidaCliente();

	bool InicializarRodada();

	void DistribuiCartas();

	void DistribuiCartaProJogador(Jogador* jogador);
	void GanhouPartida();
	Jogador* ObtemJogadorHumano1();

	Jogador* ObtemJogadorBot1();

	Carta* ObtemVira() { return Vira; }

	int ObtemNumeroDaRodada() { return NumeroDaRodada; }

	int ObtemNumeroDeJogadores() { return QuantosJogadores; }

	void JogadorJogouACarta(Jogador* jogador, const Carta* carta);

	Jogador* QuemJoga();

	void JogadorTrucou(Jogador* jogador);

	void ProximoPasso(Jogador* jogador, AcaoRealizada acao);

	void JogadorCorreu(Jogador* jogador);
	
	void JogadorAceitou(Jogador* jogador);

	int RodadaAtual() { return NumeroDaRodada - 1; };
	void AcabouRodada(Jogador* ganhou);

	bool RodadaEstaComecando();

	bool UltimaRodada() { return NumeroDaRodada == 3; };

	bool RodadaEstaCompleta();

	bool ValidaQuemGanhouARodada();

	void ProximoJogadorJoga();
	
	Jogador* GetProximoJogador();
	
	Jogador* GetOponenteJogador(Jogador* jogador);

	bool ValidaQuemGanhouAsRodadas();

	int PontosDaDupla1() { return placar->PontosDaDupla1; }

	int PontosDaDupla2() { return placar->PontosDaDupla2; }


};

