#include "pch.h"
#include "BotJogaSozinho.h"
#include "RodadasController.h"

BotJogaSozinho::BotJogaSozinho(int numero, std::string nome) : Jogador(numero, nome, true) {}
BotJogaSozinho::~BotJogaSozinho() {}

void BotJogaSozinho::FazerUmaJogadaRebatendo()
{
	//Não precisa de parametros pelo objeto MesaDaRodada ele tem todas as informações das Rodadas
	
	//Escolher a primeira carta maior para rebater (se tiver)
}

void BotJogaSozinho::FazerUmaJogadaComecando()
{
	//Não precisa de parametros pelo objeto MesaDaRodada ele tem todas as informações das Rodadas

	//

	bool deve_trucar;

	switch (QualidadeDasCartasNaRodada) 
	{
	case Otimo:
		// Jogar a carta mais fraca
		break;

	case Bom:
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
		if (PodeTrucar() && deve_trucar) 
		{
			//SetPedeTruco(true);
		}
		else 
		{
			// Jogar a carta mais forte 
		}
		break;

	case Medio:
		// Jogar a carta mais forte
		break;

	case Fraco:
		// Jogar a carta mais fraca ou truca (probabilidade baixa)
		deve_trucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
		if (PodeTrucar() && deve_trucar) 
		{
			//SetPedeTruco(true);
		}
		else 
		{
			//Jogar a carta mais fraca
		}
		break;

	case Ruim:
		// Jogar a carta mais fraca
		break;

	default:
		break;
	}



}

void BotJogaSozinho::InicializaRodada(RodadasController* mesaDaRodada)
{
	Jogador::InicializaRodada(mesaDaRodada);
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();
}

ValorDasCartasNaMao BotJogaSozinho::AnalisarMaoDeCartas()
{
	int Otimas = 0;
	int Medias = 0;
	int Ruims = 0;
	// TODO: Verificar como vai ocorrer deleção das cartas a cada rodada que passar
	// TODO: Organizar Analise de cartas com base na deleção das cartas
	const Carta* carta1 = this->PrimeiraCartaNaMao();
	const Carta* carta2 = this->SegundaCartaNaMao();
	const Carta* carta3 = this->TerceiraCartaNaMao();

	Carta* vira = MesaDaRodada->QualOVira();
	int ValorCarta1 = carta1->ObtemValor(vira);
	int ValorCarta2 = carta2->ObtemValor(vira);
	int ValorCarta3 = carta3->ObtemValor(vira);

	CalcularQualidadeDasCartas(ValorCarta1, Otimas, Medias, Ruims);
	CalcularQualidadeDasCartas(ValorCarta2, Otimas, Medias, Ruims);
	CalcularQualidadeDasCartas(ValorCarta3, Otimas, Medias, Ruims);

	return AnalisarValorFinal(Otimas, Medias, Ruims);
}

void BotJogaSozinho::CalcularQualidadeDasCartas(int valor, int &otimas, int &medias, int &ruims)
{
	if (valor > 11)
	{
		otimas++;
	}
	else if (valor >= 9 && valor <= 11)
	{
		medias++;
	}
	else if (valor < 9)
	{
		ruims++;
	}
}

ValorDasCartasNaMao BotJogaSozinho::AnalisarValorFinal(int otimas, int medias, int ruims)
{
	if (otimas == 3)
	{
		return Otimo;
	}
	else if (otimas == 2)
	{
		return Bom;
	}
	else if (otimas == 1)
	{
		return Medio;
	}
	else if (medias >= 1)
	{
		return Fraco;
	}
	else
	{
		return Ruim;
	}
}



bool BotJogaSozinho::AceitarTruco()
{
	return Jogador::AceitarTruco();
}

bool BotJogaSozinho::PedeTruco()
{
	return Jogador::PedeTruco();
}

bool BotJogaSozinho::CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade)
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

