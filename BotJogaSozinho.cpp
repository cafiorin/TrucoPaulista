#include "pch.h"
#include "BotJogaSozinho.h"
#include "RodadasController.h"

BotJogaSozinho::BotJogaSozinho(int numero, std::string nome) : Jogador(numero, nome, true)
{
}

BotJogaSozinho::~BotJogaSozinho()
{
}

const Carta* BotJogaSozinho::FazerUmaJogada()
{
	//return getjogadabot(MesaDaRodada->IndiceDaRodadaAtual());

	if (MesaDaRodada->RodadaEstaComecando())
	{
		return FazerUmaJogadaComecando();
	}
	else
	{
		return FazerUmaJogadaRebatendo();
	}
}

bool BotJogaSozinho::TemCartaMaiorNaMao(const Carta* cartaDoAdversario)
{
	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i] &&
			MesaDaRodada->MaiorCarta(mao[i].get(), cartaDoAdversario) == 0)
		{
			return true;
		}
	}
	return false;
}


const Carta* BotJogaSozinho::PrimeiraCartaMaiorNaMao(const Carta* cartaDoAdversario)
{
	const Carta* maior = nullptr;
	int cartaUsada = 0;

	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i] &&
			MesaDaRodada->MaiorCarta(mao[i].get(), cartaDoAdversario) == 0)
		{
			maior = mao[i].get();
			cartaUsada = i;
			break;
		}
	}

	CartaUsada[cartaUsada] = true;
	return maior;
}

const Carta* BotJogaSozinho::PegaAMelhorOuPiorCartaNaMao(bool melhor)
{
	const Carta* cartaProcurada = nullptr;
	int cartaUsada = -1;
	int comparaMelhor = melhor ? 0 : 1;

	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i])
		{
			if (cartaProcurada == nullptr)
			{
				cartaProcurada = mao[i].get();
				cartaUsada = i;
			}
			else
			{
				if (MesaDaRodada->MaiorCarta(mao[i].get(), cartaProcurada) == comparaMelhor)
				{
					cartaProcurada = mao[i].get();
					cartaUsada = i;
				}
			}
		}
	}

	ASSERT(cartaProcurada != nullptr && cartaUsada >= 0);
	CartaUsada[cartaUsada] = true;
	return cartaProcurada;
}

const Carta* BotJogaSozinho::FazerUmaJogadaRebatendo()
{
	const Carta* cartaDoAdversario = MesaDaRodada->QualCartaJogadaNaRodada();

	switch (QualidadeDasCartasNaRodada)
	{
		case Otimo:
		case Bom:
		case Medio:
		case Fraco:
		case Ruim:
			if (TemCartaMaiorNaMao(cartaDoAdversario))
			{
				const Carta* cartaMaisAlta = PrimeiraCartaMaiorNaMao(cartaDoAdversario);
				if (cartaMaisAlta != nullptr)
				{
					return cartaMaisAlta;
				}
			}
		break;
	}

	return PegaAMelhorOuPiorCartaNaMao(false);
}

const Carta* BotJogaSozinho::FazerUmaJogadaComecando()
{
	switch (QualidadeDasCartasNaRodada) 
	{
		case Bom:
		case Medio:
			return PegaAMelhorOuPiorCartaNaMao(true);
	}

	return PegaAMelhorOuPiorCartaNaMao(false);
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

	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i])
		{
			int ValorCarta = mao[i]->ObtemValor(MesaDaRodada->QualOVira());
			CalcularQualidadeDasCartas(ValorCarta, Otimas, Medias, Ruims);
		}
	}

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
	switch (MesaDaRodada->QualRodadaEsta())
	{
		case 1:
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
		break;

		case 2:
		{
			if (otimas == 2 || (otimas == 1 && MesaDaRodada->BotFezAPrimeira()))
			{
				return Otimo;
			}
			else if (otimas == 1)
			{
				return Bom;
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
		break;


		case 3:
		{
			if (otimas == 1)
			{
				return Otimo;
			}
			else if (medias == 1)
			{
				return Medio;
			}
			else
			{
				return Ruim;
			}
		}
		break;
	}


	return Ruim;
}

bool BotJogaSozinho::AceitarTruco()
{
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();

	if (QualidadeDasCartasNaRodada == Otimo)
	{
		return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
	}
	else if (QualidadeDasCartasNaRodada == Bom || QualidadeDasCartasNaRodada == Media)
	{
		return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
	}

	return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
}

bool BotJogaSozinho::PedeTruco()
{
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();

	bool deveTrucar=false;

	if (PodeTrucar())
	{
		if (MesaDaRodada->RodadaEstaComecando())
		{
			if (QualidadeDasCartasNaRodada == Bom)
			{
				deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else if(QualidadeDasCartasNaRodada == Fraco)
			{
				deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
			}
		}
		else //Rebatendo
		{
			const Carta* cartaDoAdversario = MesaDaRodada->QualCartaJogadaNaRodada();
			bool cartaMaisAlta = TemCartaMaiorNaMao(cartaDoAdversario);

			switch (QualidadeDasCartasNaRodada)
			{
				case Otimo:
					if (cartaMaisAlta)
					{
						deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
					}
					break;

				case Bom:
					if (cartaMaisAlta)
					{
						deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
					}
					break;

				case Medio:
					if (cartaMaisAlta)
					{
						deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
					}
					break;
			}
		}
	}
	return deveTrucar;
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

