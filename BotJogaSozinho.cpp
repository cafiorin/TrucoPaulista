#include "pch.h"
#include "BotJogaSozinho.h"
#include "RodadasController.h"

BotJogaSozinho::BotJogaSozinho(int numero, std::string nome, int numeroDaDupla) : Jogador(numero, nome, numeroDaDupla, true, false)
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
			if (MesaDaRodada->QualRodadaEsta() == 1 && CalcularSeDeveFazerAcao(Media))
			{
				return PegaAMelhorOuPiorCartaNaMao(false);
			}
			else
			{
				if (TemCartaMaiorNaMao(cartaDoAdversario))
				{
					const Carta* cartaMaisAlta = PrimeiraCartaMaiorNaMao(cartaDoAdversario);
					if (cartaMaisAlta != nullptr)
					{
						return cartaMaisAlta;
					}
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


