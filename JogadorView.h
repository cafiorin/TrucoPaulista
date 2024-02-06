#pragma once


class Jogador;
class DadosInstanciaCliente;
class CTrucoPaulistaDlg;
class Partida;
class Carta;

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
	void JogouACarta(const Carta* carta, bool cartaCoberta=false);
	void JogarCartaNovamente(const Carta* carta, bool cartaCoberta, int rodadaDaCarta);
	void EscondeCartaJogada(int rodada);
	void AtualizaCartasCliente(int c1, int c2, int c3);

	static void ControiJogadoresView(CTrucoPaulistaDlg* pDialog, DadosInstanciaCliente* cliente, Partida* partida);
	static void AtualizaStatusDosJogadores(CTrucoPaulistaDlg* pDialog, StatusJogador status);
	static void AtualizaStatusDoJogadorEscolhido(CTrucoPaulistaDlg* pDialog, StatusJogador status, Jogador* jogadorParaAtualizar);
};

