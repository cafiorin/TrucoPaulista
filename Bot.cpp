#include "pch.h"
#include "Bot.h"

Bot::Bot(int numero, std::string nome) : Jogador(numero, nome, true) {
	LimparDecisoesDoBot();
}

Bot::~Bot() {}

void Bot::VerificarSeDeveAceitarOuCorrer(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira) {
	LimparDecisoesDoBot();

	switch (tipo_rodada) {
	case PrimeiraRodada:
		VerificarSeDeveAceitarPrimeiraRodada(posicao, carta_mais_alta_rodada, vira);
		break;
	case SegundaRodada:
	case TerceiraRodada:
	case Melando:
		VerificarSeDeveAceitarSegundaRodada(posicao, carta_mais_alta_rodada, dupla_esta_ganhando_ou_empatado, vira);
		break;
	default:
		break;
	}
}

void Bot::VerificarSeDeveAceitarPrimeiraRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira) {
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();
	std::vector<const Carta*> cartas = OrdenarCartasDaMao(vira);
	bool deve_aceitar;

	if (posicao == Primeiro) {
		switch (valor_mao)
		{
		case Otimo:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			SetAceitarTruco(deve_aceitar);
			break;
		case Bom:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			SetAceitarTruco(deve_aceitar);
			break;
		case Medio:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			SetAceitarTruco(deve_aceitar);
			break;
		case Fraco:
			SetAceitarTruco(false);
			break;
		case Ruim:
			SetAceitarTruco(false);
			break;
		default:
			break;
		}
	}
	else {
		// Jogador eh o ultimo a jogar da dupla
		const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
		bool eh_da_sua_dupla = carta_mais_alta_rodada.second;

		switch (valor_mao)
		{
		case Otimo:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			SetAceitarTruco(deve_aceitar);
			break;
		case Bom:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			SetAceitarTruco(deve_aceitar);
			break;
		case Medio:
			eh_da_sua_dupla ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		case Fraco:
			eh_da_sua_dupla ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		case Ruim:
			eh_da_sua_dupla ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		default:
			break;
		}
	}
}

void Bot::VerificarSeDeveAceitarSegundaRodada(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, bool dupla_esta_ganhando_ou_empatado, const Carta* vira) {
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();
	std::vector<const Carta*> cartas = OrdenarCartasDaMao(vira);
	bool deve_aceitar;

	if (posicao == Primeiro) {
		switch (valor_mao)
		{
		case Otimo:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			SetAceitarTruco(deve_aceitar);
			break;
		case Bom:
			if (dupla_esta_ganhando_ou_empatado) {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			}
			else {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			SetAceitarTruco(deve_aceitar);
			break;
		case Medio:
			if (dupla_esta_ganhando_ou_empatado) {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
			SetAceitarTruco(deve_aceitar);
			break;
		case Fraco:
			if (dupla_esta_ganhando_ou_empatado) {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else {
				deve_aceitar = false;
			}
			break;
		case Ruim:
			if (dupla_esta_ganhando_ou_empatado) {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
			else {
				deve_aceitar = false;
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

		switch (valor_mao)
		{
		case Otimo:
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			SetAceitarTruco(deve_aceitar);
			break;
		case Bom:
			if (dupla_esta_ganhando_ou_empatado) {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			}
			else {
				deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			SetAceitarTruco(deve_aceitar);
			break;
		case Medio:
			eh_da_sua_dupla && dupla_esta_ganhando_ou_empatado ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		case Fraco:
			eh_da_sua_dupla && dupla_esta_ganhando_ou_empatado ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		case Ruim:
			eh_da_sua_dupla && dupla_esta_ganhando_ou_empatado ? SetAceitarTruco(true) : SetAceitarTruco(false);
			break;
		default:
			break;
		}
	}
}

void Bot::FazerUmaJogada(NumeroDaRodadaAtual tipo_rodada, PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	// TODO: Adicionar logica para Segunda e Terceiras Rodadas e Mao de Onze
	LimparDecisoesDoBot();

	switch (tipo_rodada)
	{
	case PrimeiraRodada:
	case SegundaRodada:
	case TerceiraRodada:
		JogarRodadaNormal(posicao, carta_mais_alta_rodada, vira);
		break;
	case Melando:
		JogarRodadaMelando(posicao, carta_mais_alta_rodada, vira);
		break;
	default:
		break;
	}
}

void Bot::JogarRodadaNormal(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	if (posicao == Primeiro)
	{

		JogarComoPrimeiro(carta_mais_alta_rodada, vira);

	}
	else if (posicao == Pe)
	{

		JogarComoPe(carta_mais_alta_rodada, vira);
	}
}

void Bot::JogarRodadaMelando(PosicaoNaDuplaParaJogar posicao, std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	std::vector<const Carta*> cartas = OrdenarCartasDaMao(vira);

	bool deve_trucar;

	switch (valor_mao) {
	case Otimo:
		// Jogar a carta mais forte ou truca (probabilidade alta)
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		if (PodeTrucar() && deve_trucar) {
			SetPedeTruco(true);
		}
		else {
			SetJogadaBot(cartas[2]);
		}
		break;
	case Bom:
		// Jogar a carta mais forte ou truca (probabilidade alta)
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		if (PodeTrucar() && deve_trucar) {
			SetPedeTruco(true);
		}
		else {
			SetJogadaBot(cartas[2]);
		}		
		break;
	case Medio:
		// Jogar a carta mais forte
		SetJogadaBot(cartas[2]);
		break;
	case Fraco:
		// Jogar a carta mais forte
		SetJogadaBot(cartas[2]);
		break;
	case Ruim:
		// Jogar a carta mais forte
		SetJogadaBot(cartas[2]);
		break;
	default:
		break;
	}
}

void Bot::JogarComoPrimeiro(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	std::vector<const Carta*> cartas = OrdenarCartasDaMao(vira);

	bool deve_trucar;

	switch (valor_mao) {
	case Otimo:
		// Jogar a carta mais fraca
		SetJogadaBot(cartas[0]);
		break;
	case Bom:
		// Jogar a carta mais forte ou truca (probabilidade media)
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		if (PodeTrucar() && deve_trucar) {
			SetPedeTruco(true);
		}
		else {
			SetJogadaBot(cartas[2]);
		}
		break;
	case Medio:
		// Jogar a carta mais forte
		SetJogadaBot(cartas[2]);
		break;
	case Fraco:
		// Jogar a carta mais fraca ou truca (probabilidade baixa)
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		if (PodeTrucar() && deve_trucar) {
			SetPedeTruco(true);
		}
		else {
			SetJogadaBot(cartas[0]);
		}
		break;
	case Ruim:
		// Jogar a carta mais fraca
		SetJogadaBot(cartas[0]);
		break;
	default:
		break;
	}
}

void Bot::JogarComoPe(std::pair<const Carta*, bool> carta_mais_alta_rodada, const Carta* vira)
{
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	std::vector<const Carta*> cartas = OrdenarCartasDaMao(vira);

	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;

	bool deve_trucar;

	switch (valor_mao)
	{
	case Otimo:
		if (eh_carta_da_dupla)
		{
			// Jogar a carta mais fraca
			SetJogadaBot(cartas[0]);
		}
		else
		{
			if (carta_mais_alta && cartas[2]->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
			{
				// Jogar a carta mais forte ou truca (probabilidade alta)
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
				if (PodeTrucar() && deve_trucar) {
					SetPedeTruco(true);
				}
				else {
					SetJogadaBot(cartas[2]);
				}
			}
			else
			{
				// Jogar a carta mais fraca
				SetJogadaBot(cartas[0]);
			}
		}
		break;
	case Bom:
		if (eh_carta_da_dupla)
		{
			// Jogar a carta mais fraca
			SetJogadaBot(cartas[0]);
		}
		else
		{
			if (carta_mais_alta && cartas[2]->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
			{
				// Jogar a carta mais forte ou truca (probabilidade media)
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
				if (PodeTrucar() && deve_trucar) {
					SetPedeTruco(true);
				}
				else {
					SetJogadaBot(cartas[2]);
				}
			}
			else {
				// Jogar a carta mais fraca
				SetJogadaBot(cartas[0]);
			}
		}
		break;
	case Medio:
		if (eh_carta_da_dupla)
		{
			// Jogar a carta mais fraca
			SetJogadaBot(cartas[0]);
		}
		else {
			if (carta_mais_alta && cartas[2]->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
			{
				// Jogar a carta mais forte ou truca (probabilidade baixa)
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
				if (PodeTrucar() && deve_trucar) {
					SetPedeTruco(true);
				}
				else {
					SetJogadaBot(cartas[2]);
				}
			}
			else
			{
				// Jogar a carta mais fraca
				SetJogadaBot(cartas[0]);
			}
		}
		break;
	case Fraco:
		if (eh_carta_da_dupla)
		{
			// Jogar a carta mais fraca
			SetJogadaBot(cartas[0]);
		}
		else {
			if (carta_mais_alta && cartas[2]->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
			{
				// Jogar a carta mais forte
				SetJogadaBot(cartas[2]);
			}
			else
			{
				// Jogar a carta mais fraca
				SetJogadaBot(cartas[0]);
			}
		}
		break;
	case Ruim:
		if (eh_carta_da_dupla)
		{
			// Jogar a carta mais fraca
			SetJogadaBot(cartas[0]);
		}
		else
		{
			if (carta_mais_alta && cartas[2]->ObtemValor(vira) > carta_mais_alta->ObtemValor(vira))
			{
				// Jogar a carta mais forte
				SetJogadaBot(cartas[2]);
			}
			else {
				// Jogar a carta mais fraca
				SetJogadaBot(cartas[0]);
			}
		}
		break;
	default:
		break;
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

ValorDasCartasNaMao Bot::AnalisarMaoDeCartas()
{
	// TODO: Verificar como vai ocorrer deleção das cartas a cada rodada que passar
	// TODO: Organizar Analise de cartas com base na deleção das cartas
	const Carta* carta1 = this->PrimeiraCartaNaMao();
	const Carta* carta2 = this->SegundaCartaNaMao();
	const Carta* carta3 = this->TerceiraCartaNaMao();

	std::map<ValorDasCartasNaMao, int> valor_final =
	{
		{Otimo, 0},
		{Medio, 0},
		{Ruim, 0}
	};

	PreencherValorFinalCartas(carta1, valor_final);
	PreencherValorFinalCartas(carta2, valor_final);
	PreencherValorFinalCartas(carta3, valor_final);

	return AnalisarValorFinal(valor_final);

}

void Bot::PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final)
{
	if (carta->valor > 11)
	{
		valor_final[Otimo]++;
	}
	else if (carta->valor >= 9 && carta->valor <= 11)
	{
		valor_final[Medio]++;
	}
	else if (carta->valor < 9)
	{
		valor_final[Ruim]++;
	}
}

ValorDasCartasNaMao Bot::AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final)
{
	if (valor_final[Otimo] == 3)
	{
		return Otimo;
	}
	else if (valor_final[Otimo] == 2)
	{
		return Bom;
	}
	else if (valor_final[Otimo] == 1)
	{
		return Medio;
	}
	else if (valor_final[Medio] >= 1)
	{
		return Fraco;
	}
	else
	{
		return Ruim;
	}
}

void Bot::LimparDecisoesDoBot() {
	deve_aceitar_o_truco_ = false;
	deve_pedir_truco_ = false;
	jogada_bot_ = nullptr;
}

bool Bot::AceitarTruco() {
	return deve_aceitar_o_truco_;
}

bool Bot::PedeTruco() {
	return deve_pedir_truco_;
}

void Bot::SetAceitarTruco(bool decisao) {
	deve_aceitar_o_truco_ = decisao;
}

void Bot::SetPedeTruco(bool decisao) {
	deve_pedir_truco_ = decisao;
}

void Bot::SetJogadaBot(const Carta* carta_escolhida) {
	jogada_bot_ = carta_escolhida;
}

const Carta* Bot::GetJogadaBot() {
	return jogada_bot_;
}