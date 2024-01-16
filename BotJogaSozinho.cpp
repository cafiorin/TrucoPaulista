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


