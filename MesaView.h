#pragma once
#include "TrucoPaulistaDlg.h"
class MesaView
{
private:
	CStatic* m_PicBaralho;
	CStatic* m_PicVira;
	CStatic* m_CartaH1_R1;
	CStatic* m_CartaH2_R1;
	CStatic* m_CartaH1_R2;
	CStatic* m_CartaH2_R2;
	CStatic* m_CartaH1_R3;
	CStatic* m_CartaH2_R3;
	CStatic* m_CartaBOT1_R1;
	CStatic* m_CartaBOT1_R2;
	CStatic* m_CartaBOT1_R3;
	CStatic* m_CartaBOT2_R1;
	CStatic* m_CartaBOT2_R2;
	CStatic* m_CartaBOT2_R3;
	CStatic* m_PicMesa;

	CTrucoPaulistaDlg* m_pDialog;

public:
	MesaView(CTrucoPaulistaDlg* pDialog);
	void Inicializa();
	void InicializaRodada(int idViraResource);
	void JogadorJogouACarta(Jogador* jogador, const Carta *carta, bool cartaCoberta, int rodada, int numeroDeJogadores);
	void JogadorJogouACartaCliente(int rodada, int numeroJogador, int carta);

};

