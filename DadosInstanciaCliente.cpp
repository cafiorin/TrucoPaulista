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

void DadosInstanciaCliente::InicializaRodada()
{
	m_RodadaAtual = 1;
}

void DadosInstanciaCliente::ProximaRodada()
{
	m_RodadaAtual++;
}

