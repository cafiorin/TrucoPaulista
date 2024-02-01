#pragma once
class DadosInstanciaCliente
{
private:
	bool m_InstanciaClienteRodando;
	bool m_JogadorPodePedirTruco;
	int m_RodadaAtual;

public:
	DadosInstanciaCliente();
	void Inicializa();
	void InicializaRodada(int numRodada = 1);
	void ProximaRodada();
	void SetaPodePedirTruco(bool podePedir) { m_JogadorPodePedirTruco = podePedir; }

	bool InstanciaEstaRodando() { return m_InstanciaClienteRodando; }
	int ObtemRodadaAtual() { return m_RodadaAtual; }
	bool JogadorPodePedirTruco() { return m_JogadorPodePedirTruco; }

};

