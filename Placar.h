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

	bool EhMaoDe11()
	{
		return (PontosDaDupla1 == 11 || PontosDaDupla2 == 11);
	}

};

