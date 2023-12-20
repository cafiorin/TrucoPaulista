#pragma once

#include "Rodada.h"


class Placar
{
public:
	int PontosDaDupla1;
	int PontosDaDupla2;

	Rodada* RodadaAtual;

	void Inicializar()
	{
		PontosDaDupla1 = 0;
		PontosDaDupla2 = 0;
	}
};

