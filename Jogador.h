#pragma once
#include <stdio.h>
#include <string>
#include "Carta.h"

class Jogador
{

private:
	int NumeroJogador;
	std::string Nome;
	Carta *mao[3];
	StatusJogador status;

public:

	Jogador(int numero, std::string nome) : NumeroJogador(numero), Nome(nome)
	{
		status = EsperandoCartas;
	}

	void RecebeCartas(Carta& carta1, Carta& carta2, Carta& carta3)
	{
		mao[0] = &carta1;
		mao[1] = &carta2;
		mao[2] = &carta3;

		status = EsperandoJogada;
	}

	Carta* CartasNaMao()
	{
		return *mao;
	}
};

