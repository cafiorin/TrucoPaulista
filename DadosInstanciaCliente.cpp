#include "pch.h"
#include "DadosInstanciaCliente.h"


DadosInstanciaCliente::DadosInstanciaCliente()
{
	m_InstanciaClienteRodando = false;
}

void DadosInstanciaCliente::Inicializa()
{
	m_InstanciaClienteRodando = true;
	InicializaRodada();
}

void DadosInstanciaCliente::InicializaRodada(int numRodada)
{
	m_RodadaAtual = numRodada;
}

void DadosInstanciaCliente::ProximaRodada()
{
	m_RodadaAtual++;
}

