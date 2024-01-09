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

	BaralhoMesa = nullptr;

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
	delete BaralhoMesa;
	BaralhoMesa = new Baralho();
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

void Partida::JogadorAceitou(Jogador* jogador)
{
	ProximoPasso(jogador, AcaoRealizada::Aceitou);
}


bool Partida::RodadaEstaCompleta()
{
	return (Rodadas[RodadaAtual()]->CartasAdicionadas == QuantosJogadores);
}

bool Partida::RodadaEstaComecando()
{
	return (Rodadas[RodadaAtual()]->CartasAdicionadas == 0);
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
				if (ValidaQuemGanhouARodada())
					return;

				NumeroDaRodada++;
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

bool Partida::ValidaQuemGanhouARodada()
{
	Jogador *ganhou = Rodadas[RodadaAtual()]->QuemGanhou();
	QuemComecaRodada = ganhou;
	EventosDaPartida->onFimDaRodada(NumeroDaRodada, ganhou);

	return ValidaQuemGanhouAsRodadas();
}

void Partida::ProximoJogadorJoga()
{
	if (QuantosJogadores == 2)
	{
		Jogador* jogadorAjogar = (UltimoJogadorAJogar == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
		
		if (RodadaEstaComecando())
			jogadorAjogar = QuemComecaRodada;

		if (jogadorAjogar->EhUmBot())
		{
			const Carta *cartaJogada = jogadorAjogar->getjogadabot(RodadaAtual());
			EventosDaPartida->onBotJogouACarta(NumeroDaRodada, jogadorAjogar, cartaJogada);
			JogadorJogouACarta(jogadorAjogar, cartaJogada);
		}
		else if (!RodadaEstaCompleta())
		{
			//Solicita a jogar
			EventosDaPartida->solicitaJogadorJogar(Dupla1[0]);
		}
	}
	else
	{
		//TODO 4 jogadores
	}
}

void Partida::AcabouRodada(Jogador* ganhou)
{
	if (ganhou == Dupla1[0])
	{
		placar->PontosDaDupla1 += QuantoValeARodada;
		if (placar->PontosDaDupla1 >= 12)
		{
			placar->PontosDaDupla1 = 12;
			EventosDaPartida->onFimDaPartida(ganhou);
			return;
		}
	}
	else
	{
		placar->PontosDaDupla2 += QuantoValeARodada;
		if (placar->PontosDaDupla2 >= 12)
		{
			placar->PontosDaDupla2 = 12;
			EventosDaPartida->onFimDaPartida(ganhou);
			return;
		}
	}

	EventosDaPartida->onAcabouARodada(ganhou);


}


bool Partida::ValidaQuemGanhouAsRodadas()
{
	if (NumeroDaRodada > 1 && RodadaEstaCompleta())
	{
		if (NumeroDaRodada == 2)
		{
			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				AcabouRodada(ganhou);
				return true;
			}
		}
		else if (NumeroDaRodada == 3)
		{
			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou() ||
				Rodadas[0]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				AcabouRodada(ganhou);
				return true;
			}
			else if (Rodadas[1]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[1]->QuemGanhou();
				AcabouRodada(ganhou);
				return true;
			}

		}

	}

	return false;
}

