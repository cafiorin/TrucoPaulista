#include "pch.h"
#include "Partida.h"
#include "BotJogaSozinho.h"

Partida::Partida(IEventosDaPartida* eventosPartida)
{
	EventosDaPartida = eventosPartida;
	placar = new Placar();

	Dupla1[0] = new Jogador(1, "Humano1", false);
	Dupla1[1] = new Jogador(3, "Humano2", false);
	Dupla2[0] = new BotJogaSozinho(2, "Bot1");
	Dupla2[1] = new BotJogaSozinho(4, "Bot2");

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
	Rodadas = new RodadasController(quantosJogadores == 4);

	delete Dupla1[0];
	delete Dupla1[1];
	delete Dupla2[0];
	delete Dupla2[1];

	if (QuantosJogadores == 2)
	{
		Dupla1[0] = new Jogador(1, "Humano1", false);
		Dupla1[1] = new Jogador(3, "Humano2", false);
		Dupla2[0] = new BotJogaSozinho(2, "Bot1");
		Dupla2[1] = new BotJogaSozinho(4, "Bot2");
	}
	else
	{
		Dupla1[0] = new Jogador(1, "Humano1", false);
		Dupla1[1] = new Jogador(3, "Humano2", false);
		Dupla2[0] = new Bot(2, "Bot1Duplas");
		Dupla2[1] = new Bot(4, "Bot2Duplas");

	}

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
	ProximoPasso(jogador, AcaoRealizada::Jogou);
}

void Partida::JogadorTrucou(Jogador* jogador)
{
	jogador->NaoPodeMaisPedirTruco();
	if (Rodadas->PodeTrucarAinda())
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
			// TODO (BOT): Testar metodos e ver se funciona ok
			/**
			NumeroDaRodadaAtual rodada_atual = RetornarNumeroDaRodadaAtual();
			PosicaoNaDuplaParaJogar posicao = RetornarPosicaoNaDuplaParaJogar();
			std::pair<const Carta*, bool> carta_mais_alta = RetornarCartaMaisAltaDaRodadaESeEhDaDupla(proximoJogador);
			bool dupla_esta_ganhando_ou_empatado = RetornarSeDuplaEstaGanhandoOuEmpatado(proximoJogador);

			static_cast<Bot*>(proximoJogador)->VerificarSeDeveAceitarOuCorrer(rodada_atual, posicao, carta_mais_alta, dupla_esta_ganhando_ou_empatado, Vira);
			*/
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

	if(UltimoJogadorAJogar == Dupla1[0])
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

NumeroDaRodadaAtual Partida::RetornarNumeroDaRodadaAtual() 
{
	//informação : O Jogador agora tem um objeto de contexto da Rodada : o MesaDaRodada , onde tem todas as informações necessarias para jogar uma carta


	if (placar->PontosDaDupla1 == placar->PontosDaDupla2) 
	{
		return Melando;
	}
	else if (placar->EhMaoDe11())
	{
		return MaoDeOnze;
	}

	switch (Rodadas->QualRodadaEsta()) 
	{
		case 1:
			return PrimeiraRodada;

		case 2:
			return SegundaRodada;

		case 3:
			return TerceiraRodada;

		default:
			return PrimeiraRodada;
	}
}

PosicaoNaDuplaParaJogar Partida::RetornarPosicaoNaDuplaParaJogar() 
{
	//informação : O Jogador agora tem um objeto de contexto da Rodada : o MesaDaRodada , onde tem todas as informações necessarias para jogar uma carta

	if (Rodadas->RetornarSeEhPrimeiroParaJogarNaRodadaAtual())
	{
		return Primeiro;
	}
	
	return Pe;
}

std::pair<const Carta*, bool> Partida::RetornarCartaMaisAltaDaRodadaESeEhDaDupla(Jogador* jogador_atual) 
{
	//informação : O Jogador agora tem um objeto de contexto da Rodada : o MesaDaRodada , onde tem todas as informações necessarias para jogar uma carta

	std::pair<const Carta*, bool> res;

	CartaDaRodada* maior_carta_da_rodada = Rodadas->RetornaMaiorCartaDaRodadaAtual();
	if (maior_carta_da_rodada) 
	{
		res.first = maior_carta_da_rodada->CartaJogadaNaRodada;
		res.second = VerificarSeEhMesmaDupla(jogador_atual, maior_carta_da_rodada->JogadorDaCarta);
	}
	else 
	{
		res.first = nullptr;
		res.second = false;
	}

	return res;
}

bool Partida::VerificarSeEhMesmaDupla(Jogador* jogador1, Jogador* jogador2) 
{
	//informação : O Jogador agora tem um objeto de contexto da Rodada : o MesaDaRodada , onde tem todas as informações necessarias para jogar uma carta

	int numero_de_matchs = 0;

	for (Jogador* jogador : Dupla1) 
	{
		if (jogador->ObtemNumeroJogador() == jogador1->ObtemNumeroJogador() || 
			jogador->ObtemNumeroJogador() == jogador2->ObtemNumeroJogador()) 
		{
			numero_de_matchs++;
		}
	}

	return numero_de_matchs == 2 ? true : false;
}

bool Partida::RetornarSeDuplaEstaGanhandoOuEmpatado(Jogador* jogador_atual) 
{
	//informação : O Jogador agora tem um objeto de contexto da Rodada : o MesaDaRodada , onde tem todas as informações necessarias para jogar uma carta

	bool esta_ganhando_ou_empatado = false;

	if (placar->PontosDaDupla1 == placar->PontosDaDupla2) 
	{
		esta_ganhando_ou_empatado = true;
	} 
	else if (placar->PontosDaDupla1 > placar->PontosDaDupla2) 
	{
		if (Dupla1[0]->ObtemNumeroJogador() == jogador_atual->ObtemNumeroJogador() || 
			Dupla1[1]->ObtemNumeroJogador() == jogador_atual->ObtemNumeroJogador()) 
		{
			esta_ganhando_ou_empatado = true;
		}
	}

	return esta_ganhando_ou_empatado;
}
