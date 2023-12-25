#include "pch.h"
#include "Bot.h"

Bot::Bot(int numero, std::string nome) : Jogador(numero, nome) {}
Bot::~Bot() {}

void Bot::FazerUmaJogada(NumeroDaRodada tipo_rodada, PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada) {
	ValorDasCartasNaMao valor_mao = AnalisarMaoDeCartas();

	switch (tipo_rodada) {
	case PrimeiraRodada:
		JogarPrimeiraRodada(posicao, adversario_esta_trucando, carta_mais_alta_rodada, valor_mao);
		break;
	case SegundaRodada:
		// TODO
		break;
	case TerceiraRodada:
		// TODO
		break;
	case Melando:
		// TODO
		break;
	default:
		break;
	}
}

void Bot::JogarPrimeiraRodada(PosicaoNaDuplaParaJogar posicao, bool adversario_esta_trucando, std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao) {
	if (posicao == Primeiro) {
		if (adversario_esta_trucando) {
			JogarComoPrimeiroEComAdversarioTrucando(carta_mais_alta_rodada, valor_mao);
		}
		else {
			JogarComoPrimeiroEComAdversarioNaoTrucando(carta_mais_alta_rodada, valor_mao);
		}
	}
	else if (posicao == Pe) {
		if (adversario_esta_trucando) {
			JogarComoPeEComAdversarioTrucando(carta_mais_alta_rodada, valor_mao);
		}
		else {
			JogarComoPeEComAdversarioNaoTrucando(carta_mais_alta_rodada, valor_mao);
		}
	}
}

void Bot::JogarComoPrimeiroEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao) {
	std::vector<const Carta*> cartas = OrdenarCartasDaMao();

	bool deve_trucar;

	switch (valor_mao) {
	case Otimo:
		// Jogar a carta mais fraca
		// TODO: Enviar mensagem para MFC??
		// Enviar: (cartas[0])
		break;
	case Bom:
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		// Jogar a carta mais forte e truca (probabilidade media)
		// TODO: Enviar mensagem para MFC??
		// Enviar: (cartas[2], deve_trucar[FALSE/TRUE])
		break;
	case Medio:
		// Jogar a carta mais forte
		// TODO: Enviar mensagem para MFC??
		// Enviar: (cartas[2])
		break;
	case Fraco:
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		// Jogar a carta mais fraca e truca (probabilidade baixa)
		// TODO: Enviar mensagem para MFC??
		// Enviar: (cartas[0], deve_trucar[FALSE/TRUE])
		break;
	case Ruim:
		// Jogar a carta mais fraca
		// TODO: Enviar mensagem para MFC??
		// Enviar: (cartas[0])
		break;
	default:
		break;
	}
}

void Bot::JogarComoPrimeiroEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao) {
	std::vector<const Carta*> cartas = OrdenarCartasDaMao();

	bool deve_aceitar;

	switch (valor_mao) {
	case Otimo:
		deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
		if (deve_aceitar) {
			// Jogar a carta mais forte
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[2], deve_aceitar[TRUE])
		}
		else {
			// TODO: Enviar mensagem para MFC??
			// Enviar: (deve_aceitar[FALSE])
		}
		break;
	case Bom:
		deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		if (deve_aceitar) {
			// Jogar a carta mais forte
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[2], deve_aceitar[TRUE])
		}
		else {
			// TODO: Enviar mensagem para MFC??
			// Enviar: (deve_aceitar[FALSE])
		}
		break;
	case Medio:
		deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		if (deve_aceitar) {
			// Jogar a carta mais forte
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[2], deve_aceitar[TRUE])
		}
		else {
			// TODO: Enviar mensagem para MFC??
			// Enviar: (deve_aceitar[FALSE])
		}
		break;
	case Fraco:
		// correr
		// TODO: Enviar mensagem para MFC??
		// Enviar: (deve_aceitar[FALSE])
		break;
	case Ruim:
		// correr
		// TODO: Enviar mensagem para MFC??
		// Enviar: (deve_aceitar[FALSE])
		break;
	default:
		break;
	}
}

void Bot::JogarComoPeEComAdversarioTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao) {
	std::vector<const Carta*> cartas = OrdenarCartasDaMao();

	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;

	bool deve_aceitar;

	switch (valor_mao) {
	case Otimo:
		if (cartas[2]->valor > carta_mais_alta->valor) {
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
			// Jogar a carta mais forte e truca (probabilidade alta)
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[2], deve_aceitar[FALSE/TRUE])
		}
		else {
			// TODO: Enviar mensagem para MFC??
			// Enviar: (deve_aceitar[FALSE])
		}
		break;

	case Bom:
		if (cartas[2]->valor > carta_mais_alta->valor) {
			deve_aceitar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			// Jogar a carta mais forte e truca (probabilidade media)
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[2], deve_aceitar[FALSE/TRUE])
		}
		else {
			// TODO: Enviar mensagem para MFC??
			// Enviar: (deve_aceitar[FALSE])
		}
		break;

	case Medio:
		// TODO: Enviar mensagem para MFC??
		// Enviar: (deve_aceitar[FALSE])
		break;

	case Fraco:
		// TODO: Enviar mensagem para MFC??
		// Enviar: (deve_aceitar[FALSE])
		break;

	case Ruim:
		// TODO: Enviar mensagem para MFC??
		// Enviar: (deve_aceitar[FALSE])
		break;

	default:
		break;
	}
}

void Bot::JogarComoPeEComAdversarioNaoTrucando(std::pair<const Carta*, bool> carta_mais_alta_rodada, ValorDasCartasNaMao& valor_mao) {
	std::vector<const Carta*> cartas = OrdenarCartasDaMao();

	const Carta* carta_mais_alta = carta_mais_alta_rodada.first;
	bool eh_carta_da_dupla = carta_mais_alta_rodada.second;

	bool deve_trucar;

	switch (valor_mao) {
	case Otimo:
		if (eh_carta_da_dupla) {
			// Jogar a carta mais fraca
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[0])
		}
		else {
			if (cartas[2]->valor > carta_mais_alta->valor) {
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
				// Jogar a carta mais forte e truca (probabilidade alta)
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[2], deve_trucar[FALSE/TRUE])
			}
			else {
				// Jogar a carta mais fraca
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[0])
			}
		}
		break;
	case Bom:
		if (eh_carta_da_dupla) {
			// Jogar a carta mais fraca
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[0])
		}
		else {
			if (cartas[2]->valor > carta_mais_alta->valor) {
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
				// Jogar a carta mais forte e truca (probabilidade media)
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[2], deve_trucar[FALSE/TRUE])
			}
			else {
				// Jogar a carta mais fraca
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[0])
			}
		}
		break;
	case Medio:
		if (eh_carta_da_dupla) {
			// Jogar a carta mais fraca
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[0])
		}
		else {
			if (cartas[2]->valor > carta_mais_alta->valor) {
				deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
				// Jogar a carta mais forte e truca (probabilidade media)
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[2], deve_trucar[FALSE/TRUE])
			}
			else {
				// Jogar a carta mais fraca
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[0])
			}
		}
		break;
	case Fraco:
		if (eh_carta_da_dupla) {
			// Jogar a carta mais fraca
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[0])
		}
		else {
			if (cartas[2]->valor > carta_mais_alta->valor) {
				// Jogar a carta mais forte
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[2])
			}
			else {
				// Jogar a carta mais fraca
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[0])
			}
		}
		break;
	case Ruim:
		if (eh_carta_da_dupla) {
			// Jogar a carta mais fraca
			// TODO: Enviar mensagem para MFC??
			// Enviar: (cartas[0])
		}
		else {
			if (cartas[2]->valor > carta_mais_alta->valor) {
				// Jogar a carta mais forte
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[2])
			}
			else {
				// Jogar a carta mais fraca
				// TODO: Enviar mensagem para MFC??
				// Enviar: (cartas[0])
			}
		}
		break;
	default:
		break;
	}
}

bool Bot::CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade) {
	// Providing a seed value
	srand((unsigned)time(NULL));

	// Escolhe um numero aleatorio entre 1 and 100
	int numero = 1 + (rand() % 100);

	bool resultado = false;

	switch (probabilidade) {
	case Alta:
		if (numero <= 90) {
			resultado = true;
		}
		break;
	case Media:
		if (numero <= 50) {
			resultado = true;
		}
		break;
	case Baixa:
		if (numero <= 10) {
			resultado = true;
		}
		break;
	default:
		break;
	}

	return resultado;
}

std::vector<const Carta*> Bot::OrdenarCartasDaMao() {
	// TODO: Verificar como vai ocorrer deleção das cartas a cada rodada que passar
	// TODO: Organizar Ordenação com base na deleção das cartas
	std::vector<const Carta*> cartas;

	cartas.emplace_back(this->PrimeiraCartaNaMao());
	cartas.emplace_back(this->SegundaCartaNaMao());
	cartas.emplace_back(this->TerceiraCartaNaMao());

	std::sort(cartas.begin(), cartas.end(), [](const Carta* carta1, const Carta* carta2) {
		return carta1->valor < carta2->valor;
		});

	return cartas;
}

ValorDasCartasNaMao Bot::AnalisarMaoDeCartas() {
	// TODO: Verificar como vai ocorrer deleção das cartas a cada rodada que passar
	// TODO: Organizar Analise de cartas com base na deleção das cartas
	const Carta* carta1 = this->PrimeiraCartaNaMao();
	const Carta* carta2 = this->SegundaCartaNaMao();
	const Carta* carta3 = this->TerceiraCartaNaMao();

	std::map<ValorDasCartasNaMao, int> valor_final = {
		{Otimo, 0},
		{Medio, 0},
		{Ruim, 0}
	};

	PreencherValorFinalCartas(carta1, valor_final);
	PreencherValorFinalCartas(carta2, valor_final);
	PreencherValorFinalCartas(carta3, valor_final);

	return AnalisarValorFinal(valor_final);

}

void Bot::PreencherValorFinalCartas(const Carta* carta, std::map<ValorDasCartasNaMao, int>& valor_final) {
	if (carta->valor > 11) {
		valor_final[Otimo]++;
	}
	else if (carta->valor >= 9 && carta->valor <= 11) {
		valor_final[Medio]++;
	}
	else if (carta->valor < 9) {
		valor_final[Ruim]++;
	}
}

ValorDasCartasNaMao Bot::AnalisarValorFinal(std::map<ValorDasCartasNaMao, int>& valor_final) {
	if (valor_final[Otimo] == 3) {
		return Otimo;
	}
	else if (valor_final[Otimo] == 2) {
		return Bom;
	}
	else if (valor_final[Otimo] == 1) {
		return Medio;
	}
	else if (valor_final[Medio] >= 1) {
		return Fraco;
	}
	else {
		return Ruim;
	}
}