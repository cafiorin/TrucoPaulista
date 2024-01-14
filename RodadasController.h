#pragma once

#include "Rodada.h"

class RodadasController
{
private:
	Rodada* Rodadas[3];
	Carta* Vira;
	int NumeroDaRodada;

	int QuantoValeARodada;
	int QuantasVezesTrucou;
	bool JogoDeDupla;

public:
	RodadasController();
	~RodadasController();

	int QualRodadaEsta() { return NumeroDaRodada; }
};
