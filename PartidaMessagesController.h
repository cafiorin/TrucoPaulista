#pragma once
#include "TrucoPaulistaDlg.h"

#define WM_CUSTOM_MESSAGE_INICIO (WM_USER + 1)

#define WM_CUSTOM_MESSAGE (WM_USER + 2)
#define WM_MESSAGE_ATUALIZA_PLACAR (WM_USER + 3)
#define WM_MESSAGE_ATUALIZA_CARTAS (WM_USER + 4)
#define WM_MESSAGE_SOLICITA_JOGADOR_JOGAR (WM_USER + 5)
#define WM_MESSAGE_JOGADOR_JOGOU_CARTA (WM_USER + 6)
#define WM_MESSAGE_ATUALIZA_CARTA_JOGADA (WM_USER + 7)

#define WM_CUSTOM_MESSAGE_FIM (WM_USER + 100)

class PartidaMessagesController
{
public:
	CTrucoPaulistaDlg* TrucoPaulistaView;
	bool Server;
	HWND GetHandle() { return ::FindWindow(NULL, _T("Truco Paulista - HUMANO 2")); }
	HWND GetHandleServer() { return ::FindWindow(NULL, _T("Truco Paulista - HUMANO 1")); }
	PartidaMessagesController(CTrucoPaulistaDlg* trucoPaulistaView, bool server);

	void OnReceiveMessage(MSG* pMsg);
	void EnviaMsgDeAtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2);
	void EnviaCartasParaJogador(int c1, int c2, int c3, int c4);
	void SolicitaJogadorAJogar();
	void JogadorJogouCarta(int numeroCarta);
	void AtualizaCartaJogada(int NumeroDaRodada, int NumeroJogador, int idResource);

	void EnviaMsgParaJogador(UINT message, WPARAM wParam, LPARAM lParam);
	void EnviaMsgParaServer(UINT message, WPARAM wParam, LPARAM lParam);

};

