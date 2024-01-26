#pragma once
#include "TrucoPaulistaDlg.h"

#define WM_CUSTOM_MESSAGE_INICIO (WM_USER + 1)

#define WM_CUSTOM_MESSAGE (WM_USER + 2)
#define WM_MESSAGE_ATUALIZA_PLACAR (WM_USER + 3)
#define WM_MESSAGE_ATUALIZA_CARTAS (WM_USER + 4)
#define WM_MESSAGE_SOLICITA_JOGADOR_JOGAR (WM_USER + 5)
#define WM_MESSAGE_JOGADOR_JOGOU_CARTA (WM_USER + 6)
#define WM_MESSAGE_ATUALIZA_CARTA_JOGADA (WM_USER + 7)
#define WM_MESSAGE_FIM_RODADA (WM_USER + 8)
#define WM_MESSAGE_FIM_PARTIDA (WM_USER + 9)
#define WM_MESSAGE_JOGADOR_TRUCOU (WM_USER + 10)
#define WM_MESSAGE_ATUALIZAR_MESA (WM_USER + 11)
#define WM_MESSAGE_INICIALIZA_RODADA  (WM_USER + 12)
#define WM_MESSAGE_CORRE_TRUCO  (WM_USER + 13)
#define WM_MESSAGE_ENVIA_TRUCO  (WM_USER + 14)
#define WM_MESSAGE_ENVIA_INICIO_PARTIDA  (WM_USER + 15)
#define WM_MESSAGE_ENVIA_ATUALIZA_TENTO  (WM_USER + 16)

#define WM_CUSTOM_MESSAGE_FIM (WM_USER + 100)

class PartidaMessagesController
{
public:
	CTrucoPaulistaDlg* TrucoPaulistaView;
	bool Server;
	HWND GetHandle() { return ::FindWindow(NULL, _T("Truco Paulista - HUMANO 2")); }
	HWND GetHandleServer() { return ::FindWindow(NULL, _T("Truco Paulista - HUMANO 1")); }
	PartidaMessagesController(CTrucoPaulistaDlg* trucoPaulistaView, bool server);
	void EnviaInicializaRodada();
	void OnReceiveMessage(MSG* pMsg);
	void EnviaMsgDeAtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2);
	void EnviaCartasParaJogador(int c1, int c2, int c3, int c4);
	void SolicitaJogadorAJogar();
	void JogadorJogouCarta(int numeroCarta, bool cartaCoberta);
	
	void AtualizaCartaJogada(int NumeroDaRodada, int NumeroJogador, int idResource);
	void EnviaAceitouTruco(int jogadorquetrucou);
	void EnviaInicializaRodada(int JogadorQueComeca);
	void EnviaCorreTruco(int jogadorQueCorre);
	void EnviaInicioDaPartida(int PontosDaDupla1, int PontosDaDupla2);
	void EnviaTruco(int jogadorQueTrucou);
	void EnviaMsgParaJogador(UINT message, WPARAM wParam, LPARAM lParam);
	void EnviaMsgParaServer(UINT message, WPARAM wParam, LPARAM lParam);
	void EnviaFimDaPartida(int jogadorVencedor);
	void EnviaFimDaRodada(int rodada, int jogadorVencedor);
	void EnviaMsgDeAtualizaTento(int tento);
};

