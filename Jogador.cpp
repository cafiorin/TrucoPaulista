#include "pch.h"
#include "Jogador.h"
#include "RodadasController.h"
#include "Enums.h"
#include <random>
#include <algorithm> 

void Jogador::RecebeCartas(const Carta& carta1, const Carta& carta2, const Carta& carta3) 
{
    // Atribui as cartas ordenadas aos elementos do array mao
    mao[0] = std::make_unique<Carta>(carta1);
    mao[1] = std::make_unique<Carta>(carta2);
    mao[2] = std::make_unique<Carta>(carta3);

    CartaUsada[0] = false;
    CartaUsada[1] = false;
    CartaUsada[2] = false;

    status = EsperandoJogada;
}


void Jogador::OrdenaCartas()
{
    Carta tempMao[] = { *mao[0], *mao[1], *mao[2] };

    std::sort(std::begin(tempMao), std::end(tempMao),
        [this](const Carta& a, const Carta& b)
        {
            return (MesaDaRodada->MaiorCarta(&a, &b) == 1); 
        });

    *mao[0] = tempMao[0];
    *mao[1] = tempMao[1];
    *mao[2] = tempMao[2];
}


bool Jogador::TemCartaMaiorNaMao(const Carta* cartaDoAdversario)
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


const Carta* Jogador::PrimeiraCartaMaiorNaMao(const Carta* cartaDoAdversario)
{
	const Carta* maior = nullptr;

	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i] &&
			MesaDaRodada->MaiorCarta(mao[i].get(), cartaDoAdversario) == 0)
		{
			maior = mao[i].get();
			break;
		}
	}

	return maior;
}

const Carta* Jogador::PegaAMelhorOuPiorCartaNaMao(bool melhor)
{
	const Carta* cartaProcurada = nullptr;
	int comparaMelhor = melhor ? 0 : 1;

	for (int i = 0; i <= 2; i++)
	{
		if (!CartaUsada[i])
		{
			if (cartaProcurada == nullptr)
			{
				cartaProcurada = mao[i].get();
			}
			else
			{
				if (MesaDaRodada->MaiorCarta(mao[i].get(), cartaProcurada) == comparaMelhor)
				{
					cartaProcurada = mao[i].get();
				}
			}
		}
	}

	ASSERT(cartaProcurada != nullptr);
	return cartaProcurada;
}

void Jogador::InicializaRodada(RodadasController* mesaDaRodada)
{
	MesaDaRodada = mesaDaRodada;
	OrdenaCartas();
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();
}

ValorDasCartasNaMao Jogador::AnalisarMaoDeCartas()
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

void Jogador::CalcularQualidadeDasCartas(int valor, int& otimas, int& medias, int& ruims)
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

ValorDasCartasNaMao Jogador::AnalisarValorFinal(int otimas, int medias, int ruims)
{
	switch (MesaDaRodada->QualRodadaEsta())
	{
	case 1:
	{
		if (otimas >= 2)
		{
			return Otimo;
		}
		else if (otimas == 1)
		{
			return Bom;
		}
		else if (medias >= 2)
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

bool Jogador::AceitarTruco()
{
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();

	if (QualidadeDasCartasNaRodada == Otimo)
	{
		return CalcularSeDeveTrucarOuCorrerOuAceitar(Alta);
	}
	else if (QualidadeDasCartasNaRodada == Bom || QualidadeDasCartasNaRodada == Medio)
	{
		return CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
	}

	return CalcularSeDeveTrucarOuCorrerOuAceitar(Baixa);
}

bool Jogador::PedeTruco()
{
	QualidadeDasCartasNaRodada = AnalisarMaoDeCartas();

	bool deveTrucar = false;

	if (PodeTrucar())
	{
		if (MesaDaRodada->RodadaEstaComecando())
		{
			if (QualidadeDasCartasNaRodada == Bom)
			{
				deveTrucar = CalcularSeDeveTrucarOuCorrerOuAceitar(Media);
			}
			else if (QualidadeDasCartasNaRodada == Fraco)
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

bool Jogador::CalcularSeDeveFazerAcao(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade)
{
	return CalcularSeDeveTrucarOuCorrerOuAceitar(probabilidade);
}

bool Jogador::CalcularSeDeveTrucarOuCorrerOuAceitar(ProbabilidadeDeTrucarOuCorrerOuAceitar probabilidade)
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

void Jogador::CartaQueFoiUsada(const Carta* cartaUsada)
{
	for (int i = 0; i < 3; i++)
	{
		if (cartaUsada == mao[i].get())
		{
			CartaUsada[i] = true;
			return;
		}
	}
}
