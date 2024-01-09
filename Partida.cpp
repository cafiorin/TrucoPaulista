#include "pch.h"
#include "Partida.h"

Partida::Partida(IEventosDaPartida *eventosPartida)
{
	EventosDaPartida = eventosPartida;
	placar = new Placar();
	NumeroDaRodada = 1;

	Dupla1[0] = new Jogador(1, "Humano1",false);
	Dupla1[1] = new Jogador(3, "Humano2",false);
	Dupla2[0] = new Jogador(2, "Bot1",true);
	Dupla2[1] = new Jogador(4, "Bot2",true);

	BaralhoMesa = new Baralho();

	Rodadas[0] = nullptr;
	Rodadas[1] = nullptr;
	Rodadas[2] = nullptr;
	Vira = nullptr;
	UltimoJogadorAJogar = nullptr;
}

Partida::~Partida()
{
	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];

	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	delete BaralhoMesa;
	delete Vira;
	delete placar;
}

void Partida::InicializarPartida(int quantosJogadores)
{
	QuantosJogadores = quantosJogadores;
	placar->Inicializar();
	EventosDaPartida->onInicioDaPartida();

	InicializarRodada();
}

void Partida::InicializarPartidaCliente()
{
	placar->Inicializar();
	InicializarRodada();
}

void Partida::GanhouPartida()
{
}

void Partida::InicializarRodada()
{
	NumeroDaRodada = 1;
	QuemComecaRodada = Dupla1[0]; //Pegar quem ganhou a rodada anterior
	QuantoValeARodada = 1;

	DistribuiCartas();

	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	Rodadas[0] = new Rodada(1, Vira, QuantosJogadores);
	Rodadas[1] = new Rodada(2, Vira, QuantosJogadores);
	Rodadas[2] = new Rodada(3, Vira, QuantosJogadores);

	EventosDaPartida->onInicioDaRodada(NumeroDaRodada);
}

void Partida::DistribuiCartas()
{
	BaralhoMesa->Embaralhar();
	
	DistribuiCartaProJogador(Dupla1[0]);
	DistribuiCartaProJogador(Dupla1[1]);
	DistribuiCartaProJogador(Dupla2[0]);
	DistribuiCartaProJogador(Dupla2[1]);

	Vira = new Carta(&BaralhoMesa->PegarCartaDoTopo());
	
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

Jogador* Partida::ObtemJogadorBot1()
{
	return Dupla2[0];
}

void Partida::JogadorJogouACarta(Jogador* jogador, const Carta* carta)
{
	Rodadas[RodadaAtual()]->CartaJogada(*carta, *jogador);
	ProximoPasso(jogador, AcaoRealizada::Jogou);
}

void Partida::JogadorTrucou(Jogador* jogador)
{
	ProximoPasso(jogador, AcaoRealizada::Trucou);
}

void Partida::JogadorCorreu(Jogador* jogador)
{
	ProximoPasso(jogador, AcaoRealizada::Trucou);
}

bool Partida::RodadaEstaCompleta()
{
	return (Rodadas[RodadaAtual()]->CartasAdicionadas == QuantosJogadores);
}

void Partida::ProximoPasso(Jogador* jogador, AcaoRealizada acao)
{
	UltimoJogadorAJogar = jogador;

	switch (acao)
	{
		case AcaoRealizada::Jogou:
		{
			if (RodadaEstaCompleta())
			{
				ValidaQuemGanhouARodada();
			}
			
			ProximoJogadorJoga();
		}
		break;

		case AcaoRealizada::Trucou:
		{
			
		}
		break;

		case AcaoRealizada::Correu:
		{

		}
		break;
	}

}

Jogador* Partida::QuemJoga()
{
	return QuemComecaRodada;
}

void Partida::ValidaQuemGanhouARodada()
{
	Jogador *ganhou = Rodadas[RodadaAtual()]->QuemGanhou();
	QuemComecaRodada = ganhou;
	EventosDaPartida->onFimDaRodada(NumeroDaRodada, ganhou);
}

void Partida::ProximoJogadorJoga()
{
	if (RodadaEstaCompleta() && UltimaRodada())
	{
		ValidaQuemGanhouAsRodadas();
	}
	else
	{
		//ProximoJogadorJoga
		if (QuantosJogadores == 2)
		{
			Jogador* jogadorAjogar = (UltimoJogadorAJogar == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
			if (jogadorAjogar->EhUmBot())
			{
				jogadorAjogar->getjogadabot(NumeroDaRodada);
			}
			else
			{
				//Solicita a jogar
				EventosDaPartida->solicitaJogadorJogar(jogadorAjogar);
			}
			
		}
		else
		{
			//TODO
		}
	}
}

void Partida::ValidaQuemGanhouAsRodadas()
{
}

