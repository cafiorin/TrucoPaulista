#include "pch.h"
#include "Partida.h"
#include "BotJogaSozinho.h"

Partida::Partida(IEventosDaPartida* eventosPartida)
{
	EventosDaPartida = eventosPartida;
	placar = new Placar();

	Dupla1[0] = new Jogador(1, "Humano1", 1, false);
	Dupla1[1] = new Jogador(3, "Humano2", 1, false);
	Dupla2[0] = new BotJogaSozinho(2, "Bot1", 2);
	Dupla2[1] = new BotJogaSozinho(4, "Bot2", 2);

	BaralhoMesa = nullptr;
	Vira = nullptr;
	UltimoJogadorAJogar = nullptr;
	Rodadas = nullptr;
}

Partida::~Partida()
{
	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];

	delete Rodadas;

	delete BaralhoMesa;
	delete Vira;
	delete placar;
}

void Partida::InicializarPartida(int quantosJogadores)
{
	QuantosJogadores = quantosJogadores;

	delete Rodadas;
	Rodadas = new RodadasController(placar, quantosJogadores == 4);

	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];

	if (QuantosJogadores == 2)
	{
		Dupla1[0] = new Jogador(1, "Humano1",1, false);
		Dupla1[1] = new Jogador(3, "Humano2",1, false);
		Dupla2[0] = new BotJogaSozinho(2, "Bot1", 2);
		Dupla2[1] = new BotJogaSozinho(4, "Bot2", 2);
	}
	else
	{
		Dupla1[0] = new Jogador(1, "Humano1", 1,false);
		Dupla1[1] = new Jogador(3, "Humano2", 1,false);
		Dupla2[0] = new Bot(2, "Bot1Duplas", 2);
		Dupla2[1] = new Bot(4, "Bot2Duplas", 2);

	}

	placar->Inicializar();
	EventosDaPartida->onInicioDaPartida();
	QuemComecaRodada = Dupla1[0];
	Rodadas->SetPlacar(placar);
	Rodadas->SetDuplas(Dupla1);

	InicializarRodada();
}

void Partida::GanhouPartida()
{
}

bool Partida::InicializarRodada()
{
	if (placar->EhMaoDe11())
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

	DistribuiCartas();

	Rodadas->InicializarRodada(Vira);
	Dupla1[0]->InicializaRodada(Rodadas);
	Dupla1[1]->InicializaRodada(Rodadas);
	Dupla2[0]->InicializaRodada(Rodadas);
	Dupla2[1]->InicializaRodada(Rodadas);

	EventosDaPartida->onInicioDaRodada(Rodadas->QualRodadaEsta());

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

Jogador* Partida::ObtemJogadorHumano2()
{
	return Dupla1[1];
}


Jogador* Partida::ObtemJogadorBot1()
{
	return Dupla2[0];
}

Jogador* Partida::ObtemJogadorBot2()
{
	return Dupla2[1];
}


void Partida::JogadorJogouACarta(Jogador* jogador, const Carta* carta)
{
	Rodadas->CartaJogada(carta, jogador);
	EventosDaPartida->onCartaJogada(Rodadas->QualRodadaEsta(), jogador, carta);
	ProximoPasso(jogador, AcaoRealizada::Jogou);
}

void Partida::DuplaNaoPodePedirTruco(Jogador* jogador)
{
	jogador->NaoPodeMaisPedirTruco();
	Jogador* dupla = GetDuplaDoJogador(jogador);
	dupla->NaoPodeMaisPedirTruco();

	
}

void Partida::DuplaOponenteTruco(Jogador* jogador, bool podeTrucar)
{
	Jogador* oponente = GetOponenteJogador(jogador);
	Jogador* dupla = GetDuplaDoJogador(oponente);

	if (podeTrucar)
	{
		oponente->JaPodePedirTruco();
		dupla->JaPodePedirTruco();
	}
	else
	{
		oponente->NaoPodeMaisPedirTruco();
		dupla->NaoPodeMaisPedirTruco();
	}

}


void Partida::JogadorTrucou(Jogador* jogador)
{
	jogador->NaoPodeMaisPedirTruco();
	DuplaNaoPodePedirTruco(jogador);

	if (Rodadas->PodeTrucarAinda())
	{
		DuplaOponenteTruco(jogador, true);
	}
	else
	{
		DuplaOponenteTruco(jogador, false);
	}

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

void Partida::ProximoPasso(Jogador* jogador, AcaoRealizada acao)
{
	UltimoJogadorAJogar = jogador;
	if (Rodadas->RodadaEstaCompleta() && acao != AcaoRealizada::Correu)
	{
		if (ValidaQuemGanhouARodada())
			return;

		Rodadas->ProximaRodada();
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
		Rodadas->TrucoAceitoParaRodada();
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

Jogador* Partida::GetJogadorByID(int idJogador)
{
	switch (idJogador)
	{
		case 1:
			return Dupla1[0];
			break;
		case 2:
			return Dupla2[0];
			break;
		case 3:
			return Dupla1[1];
			break;
		case 4:
			return Dupla2[1];
			break;
	}

	return nullptr;
}

bool Partida::ValidaQuemGanhouARodada()
{
	Jogador* ganhou = Rodadas->QuemGanhouARodadaAtual();
	if (ganhou != nullptr)
		QuemComecaRodada = ganhou;
	EventosDaPartida->onFimDaRodada(Rodadas->QualRodadaEsta(), ganhou);

	return ValidaQuemGanhouAsRodadas();
}

Jogador* Partida::GetProximoJogador()
{
	if (QuantosJogadores == 2)
	{
		return (UltimoJogadorAJogar == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
	}

	if (UltimoJogadorAJogar == Dupla1[0])
		return Dupla2[0];

	if (UltimoJogadorAJogar == Dupla2[0])
		return Dupla1[1];

	if (UltimoJogadorAJogar == Dupla1[1])
		return Dupla2[1];

	return Dupla1[0];
}

Jogador* Partida::GetOponenteJogador(Jogador* jogador)
{
	return (jogador == Dupla1[0] ? Dupla2[0] : Dupla1[0]);
}

Jogador* Partida::GetDuplaDoJogador(Jogador* jogador)
{
	if (jogador == Dupla1[0]) 
		return Dupla1[1];

	if (jogador == Dupla1[1])
		return Dupla1[0];

	if (jogador == Dupla2[0])
		return Dupla2[1];

	return Dupla2[0];
}


void Partida::ProximoJogadorJoga()
{
	Jogador* jogadorAjogar = GetProximoJogador();

	if (Rodadas->RodadaEstaComecando())
		jogadorAjogar = QuemComecaRodada;

	if (jogadorAjogar->EhUmBot())
	{
		if (jogadorAjogar->PedeTruco())
		{
			JogadorTrucou(jogadorAjogar);
		}
		else
		{
			const Carta* cartaJogada = jogadorAjogar->FazerUmaJogada();
			EventosDaPartida->onBotJogouACarta(Rodadas->QualRodadaEsta(), jogadorAjogar, cartaJogada);
			JogadorJogouACarta(jogadorAjogar, cartaJogada);
		}
	}
	else if (!Rodadas->RodadaEstaCompleta())
	{
		EventosDaPartida->solicitaJogadorJogar(jogadorAjogar);
	}
}

void Partida::AcabouRodada(Jogador* ganhou)
{
	if (ganhou == Dupla1[0])
	{
		placar->PontosDaDupla1 += Rodadas->QuantoEstaValendoARodada();
		if (placar->PontosDaDupla1 >= 12)
		{
			placar->PontosDaDupla1 = 12;
			placar->PartidasVencidasDaDupla1++;
			EventosDaPartida->onFimDaPartida(ganhou);
			return;
		}
	}
	else
	{
		placar->PontosDaDupla2 += Rodadas->QuantoEstaValendoARodada();
		if (placar->PontosDaDupla2 >= 12)
		{
			placar->PontosDaDupla2 = 12;
			placar->PartidasVencidasDaDupla2++;
			EventosDaPartida->onFimDaPartida(ganhou);
			return;
		}
	}

	EventosDaPartida->onAcabouARodada(ganhou);


}


bool Partida::ValidaQuemGanhouAsRodadas()
{
	Jogador* ganhou = Rodadas->JaTemosUmVencedor();
	if (ganhou != nullptr)
	{
		QuemComecaRodada = ganhou;
		AcabouRodada(ganhou);
		return true;
	}
	return false;
}
