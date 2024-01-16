#pragma once

#include "Rodada.h"


class Placar
{
public:
	int PontosDaDupla1;
	int PontosDaDupla2;
	
	int PartidasVencidasDaDupla1;
	int PartidasVencidasDaDupla2;

	Placar();

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

