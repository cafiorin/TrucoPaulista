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
			unsigned int c1c2 = LOWORD(pMsg->lParam);
			int PontosDaDupla1 = LOBYTE(c1c2);
			int PontosDaDupla2 = HIBYTE(c1c2);
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

		case WM_MESSAGE_SOLICITA_JOGADOR_JOGAR:
		{
			TrucoPaulistaView->SolicitaAcaoJogadorCliente();
		}
		break;

		case WM_MESSAGE_JOGADOR_JOGOU_CARTA:
		{
			unsigned int numeroCarta = LOWORD(pMsg->lParam);
			TrucoPaulistaView->JogouACartaCliente(numeroCarta);
		}
		break;

		case WM_MESSAGE_ATUALIZA_CARTA_JOGADA:
		{
			unsigned int chave1 = LOWORD(pMsg->lParam);
			int numeroJogador = LOBYTE(chave1);
			int numeroDaRodada = HIBYTE(chave1);

			unsigned int carta = HIWORD(pMsg->lParam);
			TrucoPaulistaView->AtualizaCartasJogadasCliente(numeroDaRodada, numeroJogador, carta);
		}
		break;

		case WM_MESSAGE_TERMINOU_RODADA:
		{
			
		}
		break;	

		case WM_MESSAGE_FIM_PARTIDA:
		{
			
		}
		break;

		case WM_MESSAGE_JOGADOR_TRUCOU:
		{
			unsigned int jogador = LOWORD(pMsg->lParam);
			TrucoPaulistaView->ShowMessageJogadorAceitouTruco(jogador);
		}
		break;

		case WM_MESSAGE_INICIALIZA_RODADA:
		{
			unsigned int jogador = LOWORD(pMsg->lParam);
			TrucoPaulistaView->InicializaRodadaCliente(jogador);
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

void PartidaMessagesController::SolicitaJogadorAJogar()
{
	EnviaMsgParaJogador(WM_MESSAGE_SOLICITA_JOGADOR_JOGAR, 0, 0);
}

void PartidaMessagesController::JogadorJogouCarta(int numeroCarta)
{
	EnviaMsgParaServer(WM_MESSAGE_JOGADOR_JOGOU_CARTA, 0, numeroCarta);
}

void PartidaMessagesController::AtualizaCartaJogada(int NumeroDaRodada, int NumeroJogador, int idResource)
{
	unsigned int chave1 = NumeroDaRodada << 8 | NumeroJogador;
	EnviaMsgParaJogador(WM_MESSAGE_ATUALIZA_CARTA_JOGADA, 0, MAKELPARAM(chave1, idResource));
}

void PartidaMessagesController::EnviaFimDaPartida(int jogadorVencedor)
{
	EnviaMsgParaJogador(WM_MESSAGE_FIM_PARTIDA, 0,jogadorVencedor);
}
void PartidaMessagesController::EnviaAceitouTruco(int jogadorquetrucou)
{
	EnviaMsgParaJogador(WM_MESSAGE_JOGADOR_TRUCOU, 0, jogadorquetrucou);
}

void PartidaMessagesController::EnviaInicializaRodada(int JogadorQueComeca)
{
	EnviaMsgParaJogador(WM_MESSAGE_INICIALIZA_RODADA, 0, JogadorQueComeca);
}




// metodos para enviar as mensagens
void PartidaMessagesController::EnviaMsgParaJogador(UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetHandle();
	if (hwnd != NULL)
		::PostMessage(hwnd, message, wParam, lParam);
}

void PartidaMessagesController::EnviaMsgParaServer(UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetHandleServer();
	if (hwnd != NULL)
		::PostMessage(hwnd, message, wParam, lParam);
}
