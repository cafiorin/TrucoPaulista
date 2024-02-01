#pragma once

class Partida;
class CTrucoPaulistaDlg;
class Jogador;

class PlacarView
{
public:
	PlacarView(CTrucoPaulistaDlg* pDialog, Partida* partida);

	CTrucoPaulistaDlg* m_pDialog;
	Partida* m_Partida;

	void AtualizaTento();
	void AtualizaPlacarDePartidas();
	void AtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2);
	void InicializaRodadasCheckBox();
	void QuemGanhouARodadaCheckBox(int numeroRodada, Jogador* jogadorQueGanhou);
	void InicializaRodada();

	void LimpaOutput();
	void EscreveNoOutput(const CString& novaLinha);
};

