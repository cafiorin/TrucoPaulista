#include "pch.h"
#include "Partida.h"

Partida::Partida(IEventosDaPartida* eventosPartida)
{
	EventosDaPartida = eventosPartida;
	placar = new Placar();
	NumeroDaRodada = 1;

	Dupla1[0] = new Jogador(1, "Humano1", false);
	Dupla1[1] = new Jogador(3, "Humano2", false);
	Dupla2[0] = new Jogador(2, "Bot1", true);
	Dupla2[1] = new Jogador(4, "Bot2", true);

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
	QuemComecaRodada = Dupla1[0]; 

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

bool Partida::InicializarRodada()
{
	NumeroDaRodada = 1;
	QuantoValeARodada = 1;
	QuantasVezesTrucou = 0;
	DistribuiCartas();

	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	Rodadas[0] = new Rodada(1, Vira, QuantosJogadores);
	Rodadas[1] = new Rodada(2, Vira, QuantosJogadores);
	Rodadas[2] = new Rodada(3, Vira, QuantosJogadores);

	if (placar->PontosDaDupla1 == 11 || 
		placar->PontosDaDupla2 == 11)
	{
		Dupla1[0]->NaoPodeMaisPedirTruco();
		Dupla1[1]->NaoPodeMaisPedirTruco();
		Dupla2[0]->NaoPodeMaisPedirTruco();
		Dupla2[1]->NaoPodeMaisPedirTruco();
	}
	else
	{
		Dupla1[0]->JaPodePedirTruco();
		Dupla1[1]->JaPodePedirTruco();
		Dupla2[0]->JaPodePedirTruco();
		Dupla2[1]->JaPodePedirTruco();
	}

	EventosDaPartida->onInicioDaRodada(NumeroDaRodada);

	return (QuemComecaRodada->EhUmBot());
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

	delete Vira;
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
	jogador->NaoPodeMaisPedirTruco();
	if (QuantoValeARodada <= 10)
		GetOponenteJogador(jogador)->JaPodePedirTruco();
	else
		GetOponenteJogador(jogador)->NaoPodeMaisPedirTruco();

	ProximoPasso(jogador, AcaoRealizada::Trucou);
}

void Partida::JogadorCorreu(Jogador* jogador)
{
	ProximoPasso(jogador, AcaoRealizada::Correu);
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
	if (RodadaEstaCompleta() && acao != AcaoRealizada::Correu)
	{
		if (ValidaQuemGanhouARodada())
			return;

		NumeroDaRodada++;
	}

	switch (acao)
	{
	case AcaoRealizada::Jogou:
	{
		ProximoJogadorJoga();
	}
	break;

	case AcaoRealizada::Trucou:
	{// implementar ações do bot, hoje a classe bot não esta sendo chamada, ela precisa ser ajustada para que possa ser chamada neste trecho de codigo
		Jogador* proximoJogador = GetProximoJogador();
		if (proximoJogador->EhUmBot())
		{
			if (proximoJogador->AceitarTruco())
			{
				JogadorAceitou(proximoJogador);
			}
			else
			{
				JogadorCorreu(proximoJogador);
				return;
			}
		}
		else
		{
			//Solicita Truco ao jogador
			EventosDaPartida->onPedeTruco();
		}
	}
	break;

	case AcaoRealizada::Correu:
	{
		Jogador* proximoJogador = GetProximoJogador();
		QuemComecaRodada = proximoJogador;
		AcabouRodada(proximoJogador);
	}
	break;

	case AcaoRealizada::Aceitou:
	{
		if (QuantasVezesTrucou <= 4)
			QuantasVezesTrucou++;

		QuantoValeARodada = 3 * QuantasVezesTrucou;

		EventosDaPartida->onAceitouTruco(UltimoJogadorAJogar);
		ProximoJogadorJoga();
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
	Jogador* ganhou = Rodadas[RodadaAtual()]->QuemGanhou();
	if (ganhou != nullptr)
		QuemComecaRodada = ganhou;
	EventosDaPartida->onFimDaRodada(NumeroDaRodada, ganhou);

	return ValidaQuemGanhouAsRodadas();
}

Jogador* Partida::GetProximoJogador()
{
	return (UltimoJogadorAJogar == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
}

Jogador* Partida::GetOponenteJogador(Jogador* jogador)
{
	return (jogador == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
}

void Partida::ProximoJogadorJoga()
{
	if (QuantosJogadores == 2)
	{
		Jogador* jogadorAjogar = GetProximoJogador();

		if (RodadaEstaComecando())
			jogadorAjogar = QuemComecaRodada;

		if (jogadorAjogar->EhUmBot())
		{
			if (jogadorAjogar->PedeTruco())
			{
				JogadorTrucou(jogadorAjogar);
			}
			else
			{
				const Carta* cartaJogada = jogadorAjogar->getjogadabot(RodadaAtual());
				EventosDaPartida->onBotJogouACarta(NumeroDaRodada, jogadorAjogar, cartaJogada);
				JogadorJogouACarta(jogadorAjogar, cartaJogada);
			}
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
			if (Rodadas[0]->QuemGanhou() == nullptr)
			{
				Jogador* ganhou = Rodadas[1]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}

			if (Rodadas[1]->QuemGanhou() == nullptr)
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}

			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}
		}
		else if (NumeroDaRodada == 3)
		{
			if (Rodadas[2]->QuemGanhou() == nullptr)
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}

			if (Rodadas[0]->QuemGanhou() == Rodadas[1]->QuemGanhou() ||
				Rodadas[0]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[0]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}
			else if (Rodadas[1]->QuemGanhou() == Rodadas[2]->QuemGanhou())
			{
				Jogador* ganhou = Rodadas[1]->QuemGanhou();
				QuemComecaRodada = ganhou;
				AcabouRodada(ganhou);
				return true;
			}

		}

	}

	return false;
}

