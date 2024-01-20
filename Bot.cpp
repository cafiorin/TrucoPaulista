#include "pch.h"
#include "Bot.h"
#include "Jogador.h"
#include "RodadasController.h"


Bot::Bot(int numero, std::string nome, int numeroDaDupla) : Jogador(numero, nome, numeroDaDupla, true)
{
}

Bot::~Bot()
{
}

bool Bot::AceitarTruco()
{
	const Carta* vira = MesaDaRodada->QualOVira();
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);
	bool dupla_esta_ganhando_ou_empatado = !MesaDaRodada->BotEstaoPerdendo();

	if (MesaDaRodada->QualRodadaEsta() == 1)
	{
		return VerificarSeDeveAceitarPrimeiraRodada(carta_mais_alta_rodada, vira);
	}
	else 
	{
		return VerificarSeDeveAceitarSegundaRodada(carta_mais_alta_rodada, dupla_esta_ganhando_ou_empatado, vira);
	}
}

bool Bot::VerificarSeDeveAceitarPrimeiraRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();
	bool deve_aceitar = false;

	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual())
	{
		switch (valor_mao)
		{
			case Otimo:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			case Bom:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			case Medio:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		}
	}
	else
	{
		// Jogador eh o ultimo a jogar da dupla
		const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
		bool eh_da_sua_dupla = carta_mais_alta_rodada.second;

		switch (valor_mao)
		{
			case Otimo:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
				break;

			case Bom:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
				break;

			case Medio:
			case Fraco:
			case Ruim:
				deve_aceitar = eh_da_sua_dupla;
				break;
		}
	}

	return deve_aceitar;
}

bool Bot::VerificarSeDeveAceitarSegundaRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();
	bool deve_aceitar = false;

	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual()) 
	{
		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);

		case Bom:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(dupla_esta_ganhando_ou_empatado? Alta : Media);

		case Medio:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(dupla_esta_ganhando_ou_empatado ? Media : Baixa);

		case Fraco:
			if (dupla_esta_ganhando_ou_empatado) 
			{
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			break;
		case Ruim:
			if (dupla_esta_ganhando_ou_empatado) 
			{
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
			break;
		}
	}
	else 
	{
		// Jogador eh o ultimo a jogar da dupla
		const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
		bool eh_da_sua_dupla = carta_mais_alta_rodada.second;

		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);

		case Bom:
				return CalcularSeDeveTrucarOuCorrerOuAceitar(dupla_esta_ganhando_ou_empatado ? Alta : Media);
		case Medio:
		case Fraco:
		case Ruim:
			deve_aceitar = eh_da_sua_dupla && dupla_esta_ganhando_ou_empatado;
		}
	}

	return deve_aceitar;
}

bool Bot::PedeTruco()
{
	if (!PodeTrucar())
	{
		return false;
	}

	const Carta* vira = MesaDaRodada->QualOVira();
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);
	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual())
	{
		// Jogador eh o primeiro a jogar da dupla
		switch (valor_mao)
		{
		case Otimo:
		case Bom:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);

		case Medio:
		case Fraco:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);

		case Ruim:
			return false;
		}
	}
	else
	{
		// Jogador eh o ultimo a jogar da dupla
		if (!eh_carta_da_dupla)
		{
			switch (valor_mao)
			{
				case Otimo:
					if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
					{
						return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
					}
					break;
				
				case Bom:
					if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
					{
						return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
					}
					break;

				case Medio:
					if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
					{
						return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);

					}
					break;
			}
		}
	}

	return false;
}

const Carta* Bot::FazerUmaJogada()
{
	NumeroDaRodadaAtual rodada = MesaDaRodada->RetornarNumeroDaRodadaAtual();

	if (rodada == Melando)
		return JogarRodadaMelando();

	return JogarRodadaNormal();
}

const Carta* Bot::JogarRodadaNormal()
{
	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual())
	{
		return JogarComoPrimeiro();
	}
	else
	{
		return JogarComoPe();
	}
}

const Carta* Bot::JogarRodadaMelando()
{
	return Jogador::PegaAMelhorOuPiorCartaNaMao(true);
}

const Carta* Bot::JogarComoPrimeiro()
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	switch (valor_mao) 
	{
	case Bom:
	case Medio:
		return Jogador::PegaAMelhorOuPiorCartaNaMao(true);

	}

	return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
}

const Carta* Bot::JogarComoPe()
{
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);

	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;

	if (!eh_carta_da_dupla && carta_mais_alta)
	{
		const Carta* melhorCartaDaMao = Jogador::PrimeiraCartaMaiorNaMao(carta_mais_alta);
		if (melhorCartaDaMao != nullptr)
		{
			return melhorCartaDaMao;
		}
	}

	return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
}

