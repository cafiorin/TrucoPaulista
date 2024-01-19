#include "pch.h"
#include "Bot.h"
#include "Jogador.h"
#include "RodadasController.h"


Bot::Bot(int numero, std::string nome) : Jogador(numero, nome, true)
{
}

Bot::~Bot()
{
}

bool Bot::AceitarTruco()
{
	const Carta* vira = MesaDaRodada->QualOVira();
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);
	bool dupla_esta_ganhando_ou_empatado = MesaDaRodada->RetornarSeDuplaEstaGanhandoOuEmpatado(this);

	if (MesaDaRodada->QualRodadaEsta() == 1)
	{
		return VerificarSeDeveAceitarPrimeiraRodada(carta_mais_alta_rodada, vira);
	}
	else {
		return VerificarSeDeveAceitarSegundaRodada(carta_mais_alta_rodada, dupla_esta_ganhando_ou_empatado, vira);
	}
}

bool Bot::VerificarSeDeveAceitarPrimeiraRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

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
		case Fraco:
			return false;
		case Ruim:
			return false;
		default:
			return false;
		}
	}
	else
	{
		// Jogador eh o ultimo a jogar da dupla
		const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
		bool eh_da_sua_dupla = carta_mais_alta_rodada.second;
		bool deve_aceitar = false;

		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		case Bom:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		case Medio:
			eh_da_sua_dupla ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		case Fraco:
			eh_da_sua_dupla ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		case Ruim:
			eh_da_sua_dupla ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		default:
			return deve_aceitar;
		}
	}
}

bool Bot::VerificarSeDeveAceitarSegundaRodada(std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual()) {
		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		case Bom:
			if (dupla_esta_ganhando_ou_empatado) {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			}
			else {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
		case Medio:
			if (dupla_esta_ganhando_ou_empatado) {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
		case Fraco:
			if (dupla_esta_ganhando_ou_empatado) {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else {
				return false;
			}
			break;
		case Ruim:
			if (dupla_esta_ganhando_ou_empatado) {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
			else {
				return false;
			}
			break;
		default:
			break;
		}
	}
	else {
		// Jogador eh o ultimo a jogar da dupla
		const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
		bool eh_da_sua_dupla = carta_mais_alta_rodada.second;
		bool deve_aceitar = false;

		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		case Bom:
			if (dupla_esta_ganhando_ou_empatado) {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			}
			else {
				return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
		case Medio:
			eh_da_sua_dupla&& dupla_esta_ganhando_ou_empatado ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		case Fraco:
			eh_da_sua_dupla&& dupla_esta_ganhando_ou_empatado ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		case Ruim:
			eh_da_sua_dupla&& dupla_esta_ganhando_ou_empatado ? deve_aceitar = true : deve_aceitar = false;
			return deve_aceitar;
		default:
			return deve_aceitar;
		}
	}
}

bool Bot::PedeTruco()
{
	const Carta* vira = MesaDaRodada->QualOVira();
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);
	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	if (!PodeTrucar()) {
		return false;
	}


	if (MesaDaRodada->RetornarSeEhPrimeiroParaJogarNaRodadaAtual())
	{
		// Jogador eh o primeiro a jogar da dupla
		switch (valor_mao)
		{
		case Otimo:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		case Bom:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		case Medio:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		case Fraco:
			return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		case Ruim:
		default:
			return false;
		}
	}
	else
	{
		// Jogador eh o ultimo a jogar da dupla
		switch (valor_mao)
		{
		case Otimo:
			if (eh_carta_da_dupla)
			{
				return false;
			}
			else
			{
				if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
				{
					return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
				}
				else
				{
					return false;
				}
			}
		case Bom:
			if (eh_carta_da_dupla)
			{
				return false;
			}
			else
			{
				if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
				{
					return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);

				}
				else {
					return false;
				}
			}
		case Medio:
			if (eh_carta_da_dupla)
			{
				return false;
			}
			else
			{
				if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
				{
					return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);

				}
				else {
					return false;
				}
			}
		case Fraco:
		case Ruim:
		default:
			return false;
		}
	}

}

const Carta* Bot::FazerUmaJogada()
{
	NumeroDaRodadaAtual rodada = MesaDaRodada->RetornarNumeroDaRodadaAtual();

	switch (rodada)
	{
	case Melando:
		return JogarRodadaMelando();
	case PrimeiraRodada:
	case SegundaRodada:
	case TerceiraRodada:
	case MaoDeOnze:
		return JogarRodadaNormal();
	}
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

	switch (valor_mao) {
	case Otimo:
		// Jogar a carta mais fraca (blefe)
		return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
	case Bom:
		// Jogar a carta mais forte
		return Jogador::PegaAMelhorOuPiorCartaNaMao(true);
	case Medio:
		// Jogar a carta mais forte
		return Jogador::PegaAMelhorOuPiorCartaNaMao(true);
	case Fraco:
		// Jogar a carta mais fraca
		return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
	case Ruim:
	default:
		// Jogar a carta mais fraca
		return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
	}
}

const Carta* Bot::JogarComoPe()
{
	const Carta* vira = MesaDaRodada->QualOVira();
	std::pair<const Carta*, bool> carta_mais_alta_rodada = MesaDaRodada->RetornarCartaMaisAltaDaRodadaESeEhDaDupla(this);
	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;

	if (eh_carta_da_dupla)
	{
		// Jogar a carta mais fraca
		return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
	}
	else
	{
		if (carta_mais_alta && Jogador::PegaAMelhorOuPiorCartaNaMao(true)->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
		{
			// Jogar a carta mais forte
			return Jogador::PegaAMelhorOuPiorCartaNaMao(true);
		}
		else {
			// Jogar a carta mais fraca
			return Jogador::PegaAMelhorOuPiorCartaNaMao(false);
		}
	}
}

bool Bot::CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade)
{
	// Providing a seed value
	srand((unsigned)time(NULL));

	// Escolhe um numero aleatorio entre 1 and 100
	int numero = 1 + (rand() % 100);

	bool resultado = false;

	switch (probabilidade)
	{
	case Alta:
		// 90% de chance de aceite
		if (numero <= 90)
		{
			resultado = true;
		}
		break;
	case Media:
		// 50% de chance de aceite
		if (numero <= 50)
		{
			resultado = true;
		}
		break;
	case Baixa:
		// 10% de chance de aceite
		if (numero <= 10)
		{
			resultado = true;
		}
		break;
	default:
		break;
	}

	return resultado;
}

std::vector<const Carta*> Bot::OrdenarCartasDaMao(const Carta* vira)
{
	// TODO: Verificar como vai ocorrer deleção das cartas a cada rodada que passar
	// TODO: Organizar Ordenação com base na deleção das cartas
	// TODO: Ordenar usando o metodo Carta::ObtemValor(const Carta* vira)
	std::vector<const Carta*> cartas;

	cartas.emplace_back(this->PrimeiraCartaNaMao());
	cartas.emplace_back(this->SegundaCartaNaMao());
	cartas.emplace_back(this->TerceiraCartaNaMao());

	std::sort(cartas.begin(), cartas.end(), [](const Carta* carta1, const Carta* carta2)
		{
			return carta1->valor < carta2->valor;
		});

	return cartas;
}
