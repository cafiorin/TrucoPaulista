#include "pch.h"
#include "Partida.h"
#include "BotJogaSozinho.h"
#include <thread>

Partida::Partida(IEventosDaPartida* eventosPartida)
{
	EventosDaPartida = eventosPartida;
	placar = new Placar();

	Dupla1[0] = new Jogador(1, "Humano1", 1, false, false);
	Dupla2[0] = new BotJogaSozinho(2, "Bot1", 2);
	Dupla1[1] = new Jogador(3, "Humano2", 1, false, false);
	Dupla2[1] = new BotJogaSozinho(4, "Bot2", 2);

	BaralhoMesa = nullptr;
	Vira = nullptr;
	UltimoJogadorAJogar = nullptr;
	Rodadas = nullptr;
	m_TipoDePartida = TipoDePartida::Cliente;
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

void Partida::AtualizarEventosDaPartida(IEventosDaPartida* eventosPartida) {
	EventosDaPartida = eventosPartida;
}

void Partida::Create2Jogadores(bool duasInstancias)
{
	Dupla1[0] = new Jogador(1, "Humano1", 1, false, m_TipoDePartida != TipoDePartida::Cliente);
	Dupla1[1] = new Jogador(3, "Humano2", 1, false, m_TipoDePartida == TipoDePartida::Cliente || m_TipoDePartida == TipoDePartida::QuatroJogadores);
	Dupla2[0] = new Bot(2, "Bot1Duplas", 2);
	Dupla2[1] = new Bot(4, "Bot2Duplas", 2);
}

void Partida::InicializarPartida(TipoDePartida tipoDePartida)
{
	m_TipoDePartida = tipoDePartida;
	QuantosJogadores = 4;
	DuasInstancias = false;

	switch (tipoDePartida)
	{
	case TipoDePartida::DoisJogadores:
		QuantosJogadores = 2;
		break;

	case TipoDePartida::QuatroJogadores_umremoto:
		DuasInstancias = true;
		break;
	}

	delete Rodadas;
	Rodadas = new RodadasController(placar, QuantosJogadores == 4);

	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];

	if (QuantosJogadores == 2)
	{
		Dupla1[0] = new Jogador(1, "Humano1", 1, false, true);
		Dupla1[1] = new Jogador(3, "Humano2", 1, false, false);
		Dupla2[0] = new BotJogaSozinho(2, "Bot1", 2);
		Dupla2[1] = new BotJogaSozinho(4, "Bot2", 2);
	}
	else
	{
		Create2Jogadores(DuasInstancias);
	}

	placar->Inicializar();
	EventosDaPartida->onInicioDaPartida();
	QuemComecaRodada = Dupla1[0];
	Rodadas->SetPlacar(placar);
	Rodadas->SetDuplas(Dupla1);
}

void Partida::RecomecarPartida(TipoDePartida tipoDePartida) {
	m_TipoDePartida = tipoDePartida;
	QuantosJogadores = 4;
	DuasInstancias = false;

	switch (tipoDePartida)
	{
	case TipoDePartida::DoisJogadores:
		QuantosJogadores = 2;
		break;
	}

	EventosDaPartida->onInicioDaPartida();

	if (Rodadas->QualRodadaEsta() == 1 && Rodadas->PegarRodadaAtual()->CartasAdicionadas == 0) {
		QuemComecaRodada = Dupla1[0];
	}
	else {
		if (Rodadas->PegarRodadaAtual()->CartasAdicionadas == 0)
			QuemComecaRodada = Rodadas->QuemGanhouUltimaRodada();
		else
			QuemComecaRodada = GetProximoJogador();
	}

	Rodadas->SetPlacar(placar);
	Rodadas->SetDuplas(Dupla1);
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

void Partida::RecomecarRodada() {
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

	Dupla1[0]->RecomecarRodada(Rodadas);
	Dupla1[1]->RecomecarRodada(Rodadas);
	Dupla2[0]->RecomecarRodada(Rodadas);
	Dupla2[1]->RecomecarRodada(Rodadas);

	EventosDaPartida->onInicioDaRodada(Rodadas->QualRodadaEsta());
}

void Partida::DistribuiCartas()
{
	delete BaralhoMesa;
	BaralhoMesa = new Baralho();
	BaralhoMesa->Embaralhar();

	std::thread t1(&Partida::DistribuiCartaProJogador, this, Dupla1[0]);
	std::thread t2(&Partida::DistribuiCartaProJogador, this, Dupla1[1]);
	std::thread t3(&Partida::DistribuiCartaProJogador, this, Dupla2[0]);
	std::thread t4(&Partida::DistribuiCartaProJogador, this, Dupla2[1]);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

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

void Partida::JogadorJogouACarta(Jogador* jogador, const Carta* carta, bool cartaCoberta)
{
	Rodadas->CartaJogada(carta, jogador, cartaCoberta);
	EventosDaPartida->onCartaJogada(Rodadas->QualRodadaEsta(), jogador, carta, cartaCoberta);
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
		return;
	}
	break;

	case AcaoRealizada::Trucou:
	{
		Jogador* proximoJogador = GetProximoJogador();
		if (proximoJogador->EhUmBot())
		{
			if (proximoJogador->AceitarTruco())
			{
				JogadorAceitou(proximoJogador);
				return;
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
			EventosDaPartida->onPedeTruco(proximoJogador);
		}
	}
	break;

	case AcaoRealizada::Correu:
	{
		Jogador* jogador = GetJogadorAnterior();
		QuemComecaRodada = jogador;
		AcabouRodada(jogador);
	}
	break;

	case AcaoRealizada::Aceitou:
	{
		Rodadas->TrucoAceitoParaRodada();
		EventosDaPartida->onAceitouTruco(UltimoJogadorAJogar);
		ProximoJogadorJoga(true);
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

Jogador* Partida::GetJogadorAnterior()
{
	int idProxJogador = UltimoJogadorAJogar->ObtemNumeroJogador();

	if (QuantosJogadores == 2)
	{
		idProxJogador = (idProxJogador == 1 ? 2 : 1);
	}
	else
	{
		idProxJogador = idProxJogador - 1 < 1 ? 4 : idProxJogador - 1;
	}

	return GetJogadorByID(idProxJogador);
}

Jogador* Partida::GetProximoJogador()
{
	int idProxJogador = UltimoJogadorAJogar->ObtemNumeroJogador();

	if (QuantosJogadores == 2)
	{
		idProxJogador = (idProxJogador == 1 ? 2 : 1);
	}
	else
	{
		idProxJogador = idProxJogador + 1 > 4 ? 1 : idProxJogador + 1;
	}

	return GetJogadorByID(idProxJogador);
}

Jogador* Partida::GetOponenteJogador(Jogador* jogador)
{
	if (jogador == Dupla1[0])
		return Dupla2[0];

	if (jogador == Dupla1[1])
		return Dupla2[1];

	if (jogador == Dupla2[0])
		return Dupla1[0];

	return Dupla1[1];
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

void Partida::ProximoJogadorJoga(bool trucou/*=false*/)
{
	Jogador* jogadorAjogar = trucou ? GetJogadorAnterior() : GetProximoJogador();

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
			bool cartaCoberta = cartaJogada == nullptr;
			EventosDaPartida->onBotJogouACarta(Rodadas->QualRodadaEsta(), jogadorAjogar, cartaJogada, cartaCoberta);
			JogadorJogouACarta(jogadorAjogar, cartaJogada, cartaCoberta);
		}
	}
	else if (!Rodadas->RodadaEstaCompleta())
	{
		EventosDaPartida->solicitaJogadorJogar(jogadorAjogar);
	}
}

void Partida::AcabouRodada(Jogador* ganhou)
{
	if (ganhou == Dupla1[0] || ganhou == Dupla1[1])
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
