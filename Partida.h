#pragma once

#include "Placar.h"
#include "Jogador.h"
#include "Rodada.h"
#include "Baralho.h"
#include "IEventosDaPartida.h"
#include "Enums.h"
#include "Bot.h"
#include "RodadasController.h"


class Partida
{
private:
	Jogador* QuemComecaRodada;
	Jogador* UltimoJogadorAJogar;

	int QuantosJogadores = 2;
	bool DuasInstancias;
	Placar* placar;

	Jogador* Dupla1[2];
	Jogador* Dupla2[2];

	RodadasController* Rodadas;
	Baralho* BaralhoMesa;
	Carta* Vira;
	IEventosDaPartida* EventosDaPartida;

public:

	Partida(IEventosDaPartida* eventosPartida);
	~Partida();
	
	void InicializarPartida(int quantosJogadores, bool duasInstancias);

	bool InicializarRodada();

	void DistribuiCartas();

	void DistribuiCartaProJogador(Jogador* jogador);
	void GanhouPartida();
	
	Jogador* ObtemJogadorHumano1();
	Jogador* ObtemJogadorBot1();
	Jogador* ObtemJogadorHumano2();
	Jogador* ObtemJogadorBot2();

	Carta* ObtemVira() { return Vira; }

	int ObtemNumeroDaRodada() { return Rodadas->QualRodadaEsta(); }

	int ObtemNumeroDeJogadores() { return QuantosJogadores; }

	void JogadorJogouACarta(Jogador* jogador, const Carta* carta, bool cartaCoberta);

	Jogador* QuemJoga();
	Jogador* GetJogadorByID(int idJogador);
	void JogadorTrucou(Jogador* jogador);

	void ProximoPasso(Jogador* jogador, AcaoRealizada acao);

	void JogadorCorreu(Jogador* jogador);
	
	void JogadorAceitou(Jogador* jogador);

	void AcabouRodada(Jogador* ganhou);

	bool ValidaQuemGanhouARodada();

	void ProximoJogadorJoga(bool trucou=false);
	
	Jogador* GetProximoJogador();
	Jogador* GetJogadorAnterior();

	Jogador* GetJogadorAtual() { return UltimoJogadorAJogar; }
	
	Jogador* GetOponenteJogador(Jogador* jogador);
	Jogador* GetDuplaDoJogador(Jogador* jogador);

	bool ValidaQuemGanhouAsRodadas();

	int PontosDaDupla1() { return placar->PontosDaDupla1; }
	int PontosDaDupla2() { return placar->PontosDaDupla2; }

	int PartidasVencidasDaDupla1() { return placar->PartidasVencidasDaDupla1; }
	int PartidasVencidasDaDupla2() { return placar->PartidasVencidasDaDupla2; }

	Placar* GetPlacar() { return placar; }

	RodadasController* GetRodada() { return Rodadas; }

	void DuplaNaoPodePedirTruco(Jogador* jogador);
	void DuplaOponenteTruco(Jogador* jogador, bool podeTrucar);

	CString ObterMensagemDeQuantoVale()
	{
		return Rodadas->ObterMensagemDeQuantoVale();
	}

	int ObterValorDaRodada()
	{
		return Rodadas->QuantoEstaValendoARodada();
	}
};

