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
	const Carta* maior = nullptr;

	if (!CartaUsada[0] && MesaDaRodada->MaiorCarta(PrimeiraCartaNaMao(), cartaDoAdversario) <= 0)
	{
		maior = PrimeiraCartaNaMao();
	}

	if (!CartaUsada[1] && MesaDaRodada->MaiorCarta(SegundaCartaNaMao(), cartaDoAdversario) <= 0)
	{
		if (maior != nullptr)
		{
			if (MesaDaRodada->MaiorCarta(maior, SegundaCartaNaMao()) > 0)
			{
				maior = SegundaCartaNaMao();
			}
		}
		else
		{
			maior = SegundaCartaNaMao();
		}
	}

	if (!CartaUsada[2] && MesaDaRodada->MaiorCarta(TerceiraCartaNaMao(), cartaDoAdversario))
	{
		if (maior != nullptr)
		{
			if (MesaDaRodada->MaiorCarta(maior, TerceiraCartaNaMao()) > 0)
			{
				maior = TerceiraCartaNaMao();
			}
		}
		else
		{
			maior = TerceiraCartaNaMao();
		}
	}

	return maior != nullptr;
}


const Carta* BotJogaSozinho::PrimeiraCartaMaiorNaMao(const Carta* cartaDoAdversario)
{
	const Carta* maior = nullptr;
	int cartaUsada = 0;

	if (!CartaUsada[0] && MesaDaRodada->MaiorCarta(PrimeiraCartaNaMao(), cartaDoAdversario)<=0)
	{
		maior = PrimeiraCartaNaMao();
		cartaUsada = 1;
	}

	if (!CartaUsada[1] && MesaDaRodada->MaiorCarta(SegundaCartaNaMao(), cartaDoAdversario)<=0)
	{
		if (maior != nullptr)
		{
			if (MesaDaRodada->MaiorCarta(maior, SegundaCartaNaMao()) > 0)
			{
				maior = SegundaCartaNaMao();
				cartaUsada = 2;
			}
		}
		else
		{
			maior = SegundaCartaNaMao();
			cartaUsada = 2;
		}
		cartaUsada = 2;
	}

	if (!CartaUsada[2] && MesaDaRodada->MaiorCarta(TerceiraCartaNaMao(), cartaDoAdversario))
	{
		if (maior != nullptr)
		{
			if (MesaDaRodada->MaiorCarta(maior, TerceiraCartaNaMao()) > 0)
			{
				maior = TerceiraCartaNaMao();
				cartaUsada = 3;
			}
		}
		else
		{
			maior = TerceiraCartaNaMao();
			cartaUsada = 3;
		}
	}

	if(cartaUsada > 0)
		CartaUsada[cartaUsada-1] = true;
	
	return maior;
}

const Carta* BotJogaSozinho::MelhorCartaNaMao()
{
	const Carta* maior = nullptr;
	int cartaUsada = 0;

	if (!CartaUsada[0] && !CartaUsada[1])
	{
		if (MesaDaRodada->MaiorCarta(PrimeiraCartaNaMao(), SegundaCartaNaMao()) <= 0)
		{
			maior = PrimeiraCartaNaMao();
			cartaUsada = 1;
		}
		else
		{
			maior = SegundaCartaNaMao();
			cartaUsada = 2;
		}
	}
	if (maior != nullptr)
	{
		if (MesaDaRodada->MaiorCarta(maior, TerceiraCartaNaMao()) > 0)
		{
			maior = TerceiraCartaNaMao();
			cartaUsada = 3;
		}
	}
	else if (!CartaUsada[1] && !CartaUsada[2])
	{
		if (MesaDaRodada->MaiorCarta(SegundaCartaNaMao(), TerceiraCartaNaMao()) <= 0)
		{
			maior = SegundaCartaNaMao();
			cartaUsada = 2;
		}
		else
		{
			maior = TerceiraCartaNaMao();
			cartaUsada = 3;
		}
	}
	else if (!CartaUsada[2])
	{
		maior = TerceiraCartaNaMao();
		cartaUsada = 3;
	}

	ASSERT(maior != nullptr && cartaUsada > 0);
	CartaUsada[cartaUsada - 1] = true;
	return maior;
}

const Carta* BotJogaSozinho::PiorCartaNaMao()
{
	const Carta* menor = nullptr;
	int cartaUsada = 0;

	if (!CartaUsada[0] && !CartaUsada[1])
	{
		if (MesaDaRodada->MaiorCarta(PrimeiraCartaNaMao(), SegundaCartaNaMao()) >= 0)
		{
			menor = PrimeiraCartaNaMao();
			cartaUsada = 1;
		}
		else
		{
			menor = SegundaCartaNaMao();
			cartaUsada = 2;
		}
	}
	if (menor != nullptr)
	{
		if (MesaDaRodada->MaiorCarta(menor, TerceiraCartaNaMao()) < 0)
		{
			menor = TerceiraCartaNaMao();
			cartaUsada = 3;
		}
	}
	else if (!CartaUsada[1] && !CartaUsada[2])
	{
		if (MesaDaRodada->MaiorCarta(SegundaCartaNaMao(), TerceiraCartaNaMao()) >= 0)
		{
			menor = SegundaCartaNaMao();
			cartaUsada = 2;
		}
		else
		{
			menor = TerceiraCartaNaMao();
			cartaUsada = 3;
		}
	}
	else if(!CartaUsada[2])
	{
		menor = TerceiraCartaNaMao();
		cartaUsada = 3;
	}

	ASSERT(menor != nullptr && cartaUsada > 0);
	CartaUsada[cartaUsada - 1] = true;
	return menor;
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
			const Carta* cartaMaisAlta = PrimeiraCartaMaiorNaMao(cartaDoAdversario);
			if (cartaMaisAlta != nullptr)
			{
				//Jogar a carta mais forte
				return cartaMaisAlta;
			}
			else
			{
				// Jogar a carta mais fraca
				return PiorCartaNaMao();
			}
		break;
	}

	return nullptr;
}

const Carta* BotJogaSozinho::FazerUmaJogadaComecando()
{
	switch (QualidadeDasCartasNaRodada) 
	{
		case Otimo:
			// Jogar a carta mais fraca
			return PiorCartaNaMao();
			break;

		case Bom:
			// Jogar a carta mais forte 
			return MelhorCartaNaMao();
			break;

		case Medio:
			// Jogar a carta mais forte
			return MelhorCartaNaMao();
			break;

		case Fraco:
			//Jogar a carta mais fraca
			return PiorCartaNaMao();
			break;

		case Ruim:
			// Jogar a carta mais fraca
			return PiorCartaNaMao();
			break;

		default:
			break;
	}

	return nullptr;
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

