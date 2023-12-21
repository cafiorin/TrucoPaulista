#include "pch.h"
#include "Partida.h"

Partida::Partida()
{
	placar = new Placar();
	NumeroDaRodada = 1;

	Dupla1[0] = new Jogador(1, "Humano1");
	Dupla1[1] = new Jogador(3, "Humano2");
	Dupla2[0] = new Jogador(2, "Bot1");
	Dupla2[1] = new Jogador(4, "Bot2");

	Rodadas[0] = new Rodada(1);
	Rodadas[1] = new Rodada(2);
	Rodadas[2] = new Rodada(3);

	BaralhoMesa = new Baralho();
	Vira = nullptr;
}



void Partida::InicializarPartida()
{
	placar->Inicializar();
	InicializarRodada();
}

void Partida::InicializarRodada()
{
	NumeroDaRodada = 1;
	QuemComecaRodada = Dupla1[0]; //Pegar quem ganhou a rodada anterior
	QuantoValeARodada = 1;

	DistribuiCartas();
}

void Partida::DistribuiCartas()
{
	BaralhoMesa->Embaralhar();
	
	DistribuiCartaProJogador(Dupla1[0]);
	DistribuiCartaProJogador(Dupla1[1]);
	DistribuiCartaProJogador(Dupla2[0]);
	DistribuiCartaProJogador(Dupla2[1]);

	Vira = &BaralhoMesa->PegarCartaDoTopo();
}


void Partida::DistribuiCartaProJogador(Jogador* jogador)
{
	Carta c1 = BaralhoMesa->PegarCartaDoTopo();
	Carta c2 = BaralhoMesa->PegarCartaDoTopo();
	Carta c3 = BaralhoMesa->PegarCartaDoTopo();

	jogador->RecebeCartas(c1, c2, c3);
}

Jogador* Partida::ObtemJogadorHumano1()
{
	return Dupla1[0];
}