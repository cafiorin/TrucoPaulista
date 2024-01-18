#include "pch.h"
#include "PartidaMessagesController.h"
#include "TrucoPaulistaDlg.h"

PartidaMessagesController::PartidaMessagesController(CTrucoPaulistaDlg* trucoPaulistaView, bool server)
{
	TrucoPaulistaView = trucoPaulistaView;
	Server = server;//diferenciar caso a mesg seja dos 2 lados
}

void PartidaMessagesController::OnReceiveMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
		case WM_MESSAGE_ATUALIZA_PLACAR:
		{
			int PontosDaDupla1 = LOWORD(pMsg->lParam);  // Obtém o primeiro inteiro
			int PontosDaDupla2 = HIWORD(pMsg->lParam);  // Obtém o segundo inteiro
			TrucoPaulistaView->AtualizaPlacar(PontosDaDupla1, PontosDaDupla2);
		}
		break;


		case WM_MESSAGE_ATUALIZA_CARTAS:
		{
			unsigned int c1c2 = LOWORD(pMsg->lParam);  
			int c1 = LOBYTE(c1c2);
			int c2 = HIBYTE(c1c2);

			unsigned int c3c4 = HIWORD(pMsg->lParam);  
			int c3 = LOBYTE(c3c4);
			int c4 = HIBYTE(c3c4);
			TrucoPaulistaView->AtualizaCartasCliente(c1,c2,c3,c4);
		}
		break;

		default:
			break;
	}
}

void PartidaMessagesController::EnviaMsgDeAtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2)
{
	EnviaMsgParaJogador(WM_MESSAGE_ATUALIZA_PLACAR, 0, MAKELPARAM(PontosDaDupla1, PontosDaDupla2));
}

void PartidaMessagesController::EnviaCartasParaJogador(int c1, int c2, int c3, int c4)
{
	unsigned int c1c2 = c2 << 8 | c1;
	unsigned int c3c4 = c4 << 8 | c3;

	EnviaMsgParaJogador(WM_MESSAGE_ATUALIZA_CARTAS, 0, MAKELPARAM(c1c2, c3c4));
}

void PartidaMessagesController::EnviaMsgParaJogador(UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetHandle();
	if (hwnd != NULL)
		::PostMessage(GetHandle(), WM_MESSAGE_ATUALIZA_CARTAS, wParam, lParam);
}

