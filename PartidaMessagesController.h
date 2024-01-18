#pragma once
#include "TrucoPaulistaDlg.h"

#define WM_CUSTOM_MESSAGE_INICIO (WM_USER + 1)

#define WM_CUSTOM_MESSAGE (WM_USER + 2)
#define WM_MESSAGE_ATUALIZA_PLACAR (WM_USER + 3)
#define WM_MESSAGE_ATUALIZA_CARTAS (WM_USER + 4)

#define WM_CUSTOM_MESSAGE_FIM (WM_USER + 100)

class PartidaMessagesController
{
public:
	CTrucoPaulistaDlg* TrucoPaulistaView;
	bool Server;
	HWND GetHandle() { return ::FindWindow(NULL, _T("Truco Paulista - HUMANO 2")); }
	PartidaMessagesController(CTrucoPaulistaDlg* trucoPaulistaView, bool server);

	void OnReceiveMessage(MSG* pMsg);
	void EnviaMsgDeAtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2);
	void EnviaCartasParaJogador(int c1, int c2, int c3, int c4);

	void EnviaMsgParaJogador(UINT message, WPARAM wParam, LPARAM lParam);
};

