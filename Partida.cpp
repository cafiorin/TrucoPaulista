#include "pch.h"
#include "Partida.h"

void Partida::InicializarPartida()
{
	placar->Inicializar();

	NumeroDaRodada = 1;
	QuemComecaRodada = Dupla1[0];
	QuantoValeARodada = 1;
}

void Partida::InicializarRodada()
{
	NumeroDaRodada = 1;
	QuemComecaRodada = Dupla1[0]; //Pegar quem ganhou a rodada anterior
	QuantoValeARodada = 1;
}
