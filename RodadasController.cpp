#include "pch.h"
#include "RodadasController.h"


RodadasController::RodadasController()
{
	NumeroDaRodada = 1;

	Rodadas[0] = nullptr;
	Rodadas[1] = nullptr;
	Rodadas[2] = nullptr;
	Vira = nullptr;
}


RodadasController::~RodadasController()
{
	delete Rodadas[0];
	delete Rodadas[1];
	delete Rodadas[2];

	delete Vira;
}
