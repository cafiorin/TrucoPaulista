#pragma once


class Jogador;
class DadosInstanciaCliente;
class CTrucoPaulistaDlg;
class Partida;

class JogadorView
{

public:

	JogadorView(CTrucoPaulistaDlg* pDialog, int idCarta1, int idCarta2, int idCarta3, int idSuaVez, int idTruco, int idCorrer, Jogador* jogador, DadosInstanciaCliente* cliente, Partida* partida);

	CStatic* m_Carta1View;
	CStatic* m_Carta2View;
	CStatic* m_Carta3View;
	CWnd* m_TextSuaVez;
	CWnd* m_BotaoTruco;
	CWnd* m_BotaoCorrer;
	CTrucoPaulistaDlg* m_pDialog;
	Partida* m_Partida;

	Jogador* m_Jogador;
	DadosInstanciaCliente* m_Cliente;

	void AtualizaStatusDoJogador(StatusJogador status);

};

