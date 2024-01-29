#include "pch.h"
#include "Enums.h"
#include "JogadorView.h"
#include "afxdialogex.h"
#include "Jogador.h"
#include "DadosInstanciaCliente.h"
#include "CartasBitmap.h"
#include "TrucoPaulistaDlg.h"
#include "Partida.h"
#include "MesaView.h"

void JogadorView::ControiJogadoresView(CTrucoPaulistaDlg* pDialog, DadosInstanciaCliente* cliente, Partida* partida)
{
	delete pDialog->m_JogadorHumano1View;
	delete pDialog->m_JogadorHumano2View;
	delete pDialog->m_JogadorBot1View;
	delete pDialog->m_JogadorBot2View;

	if (partida->ObtemNumeroDeJogadores() == 2)
	{
		pDialog->m_JogadorHumano1View = new JogadorView(pDialog, IDC_PIC1, IDC_PIC2, IDC_PIC3, IDC_SUAVEZ_H1, IDC_TRUCAR, IDC_CORRER, partida->ObtemJogadorHumano1(), cliente, partida);
		pDialog->m_JogadorBot1View = new JogadorView(pDialog, IDC_PIC13, IDC_PIC12, IDC_PIC8, 0, 0, 0, partida->ObtemJogadorBot1(), cliente, partida);
		pDialog->m_JogadorHumano2View = new JogadorView(pDialog, IDC_PIC13, IDC_PIC12, IDC_PIC8, IDC_SUAVEZ_H2, IDC_TRUCAR2, IDC_CORRER2, partida->ObtemJogadorHumano2(), cliente, partida);
		pDialog->m_JogadorBot2View = new JogadorView(pDialog, IDC_PIC9, IDC_PIC11, IDC_PIC10, 0, 0, 0, partida->ObtemJogadorBot2(), cliente, partida);
	}
	else
	{
		pDialog->m_JogadorHumano1View = new JogadorView(pDialog, IDC_PIC1, IDC_PIC2, IDC_PIC3, IDC_SUAVEZ_H1, IDC_TRUCAR, IDC_CORRER, partida->ObtemJogadorHumano1(), cliente, partida);
		pDialog->m_JogadorHumano2View = new JogadorView(pDialog, IDC_PIC13, IDC_PIC12, IDC_PIC8, IDC_SUAVEZ_H2, IDC_TRUCAR2, IDC_CORRER2, partida->ObtemJogadorHumano2(), cliente, partida);
		pDialog->m_JogadorBot1View = new JogadorView(pDialog, IDC_PIC5, IDC_PIC7, IDC_PIC6, 0, 0, 0, partida->ObtemJogadorBot1(), cliente, partida);
		pDialog->m_JogadorBot2View = new JogadorView(pDialog, IDC_PIC9, IDC_PIC11, IDC_PIC10, 0, 0, 0, partida->ObtemJogadorBot2(), cliente, partida);
	}
}

void JogadorView::AtualizaStatusDosJogadores(CTrucoPaulistaDlg* pDialog, StatusJogador status)
{
	JogadorView* jogadores[4] = { pDialog->m_JogadorHumano1View, pDialog->m_JogadorHumano2View, pDialog->m_JogadorBot1View , pDialog->m_JogadorBot2View };

	for (int i = 0; i < 4; i++)
	{
		JogadorView* jogador = jogadores[i];
		jogador->AtualizaStatusDoJogador(status);
	}
}

void JogadorView::AtualizaStatusDoJogadorEscolhido(CTrucoPaulistaDlg* pDialog, StatusJogador status, Jogador* jogadorParaAtualizar)
{
	JogadorView* jogadores[4] = { pDialog->m_JogadorHumano1View, pDialog->m_JogadorHumano2View, pDialog->m_JogadorBot1View , pDialog->m_JogadorBot2View };

	for (int i = 0; i < 4; i++)
	{
		JogadorView* jogador = jogadores[i];
		if (jogador->m_Jogador->ObtemNumeroJogador() == jogadorParaAtualizar->ObtemNumeroJogador())
		{
			jogador->AtualizaStatusDoJogador(status);
			break;
		}
	}
}


JogadorView::JogadorView(CTrucoPaulistaDlg* pDialog, int idCarta1, int idCarta2, int idCarta3, int idSuaVez, int idTruco, int idCorrer, Jogador* jogador, DadosInstanciaCliente *cliente, Partida* partida)
{
	m_Carta1View = dynamic_cast<CStatic*>(pDialog->GetDlgItem(idCarta1));
	m_Carta2View = dynamic_cast<CStatic*>(pDialog->GetDlgItem(idCarta2));
	m_Carta3View = dynamic_cast<CStatic*>(pDialog->GetDlgItem(idCarta3));

	if (!jogador->EhUmBot())
	{
		m_TextSuaVez = pDialog->GetDlgItem(idSuaVez);
		m_BotaoTruco = pDialog->GetDlgItem(idTruco);
		m_BotaoCorrer = pDialog->GetDlgItem(idCorrer);

		m_Carta1View->ModifyStyle(0, SS_NOTIFY);
		m_Carta1View->ModifyStyle(0, SS_NOTIFY);
		m_Carta1View->ModifyStyle(0, SS_NOTIFY);
	}

	m_Jogador = jogador;
	m_Cliente = cliente;
	m_pDialog = pDialog;
	m_Partida = partida;
}

void JogadorView::AtualizaStatusDoJogador(StatusJogador status)
{
	switch (status)
	{
	case StatusJogador::Inicia:
	{
		m_Carta1View->ShowWindow(SW_HIDE);
		m_Carta2View->ShowWindow(SW_HIDE);
		m_Carta3View->ShowWindow(SW_HIDE);

		if (!m_Jogador->EhUmBot())
		{
			m_TextSuaVez->ShowWindow(SW_HIDE);
			m_BotaoTruco->ShowWindow(SW_HIDE);
			m_BotaoCorrer->ShowWindow(SW_HIDE);
		}
	}
	break;

	case StatusJogador::RecebeuCartas:
	{
		if (m_Jogador->PodeMostrarAsCartas())
		{
			CartasBitmap cartaBitmap1(m_Jogador->PrimeiraCartaNaMao()->idResource);
			CartasBitmap cartaBitmap2(m_Jogador->SegundaCartaNaMao()->idResource);
			CartasBitmap cartaBitmap3(m_Jogador->TerceiraCartaNaMao()->idResource);

			m_pDialog->SetBitmapOnStaticControl(*m_Carta1View, *cartaBitmap1.Getbitmap());
			m_pDialog->SetBitmapOnStaticControl(*m_Carta2View, *cartaBitmap2.Getbitmap());
			m_pDialog->SetBitmapOnStaticControl(*m_Carta3View, *cartaBitmap3.Getbitmap());
		}
		else
		{
			if (!m_Jogador->EhUmBot() || m_Partida->ObtemNumeroDeJogadores() == 2)
			{
				CBitmap bitmapVerso;
				bitmapVerso.LoadBitmap(IDB_BITMAP_VERSO);

				m_pDialog->SetBitmapOnStaticControl(*m_Carta1View, bitmapVerso);
				m_pDialog->SetBitmapOnStaticControl(*m_Carta2View, bitmapVerso);
				m_pDialog->SetBitmapOnStaticControl(*m_Carta3View, bitmapVerso);
			}
			else if (m_Jogador->EhUmBot())
			{
				CBitmap bitmap;
				bitmap.LoadBitmap(IDB_BITMAP_VERSO_90);

				m_pDialog->SetBitmapOnStaticControl(*m_Carta1View, bitmap);
				m_pDialog->SetBitmapOnStaticControl(*m_Carta2View, bitmap);
				m_pDialog->SetBitmapOnStaticControl(*m_Carta3View, bitmap);
			}

		}

		m_Carta1View->ShowWindow(SW_SHOW);
		m_Carta2View->ShowWindow(SW_SHOW);
		m_Carta3View->ShowWindow(SW_SHOW);
	}
	break;

	case StatusJogador::SuaVez:
	{
		if (!m_Jogador->EhUmBot())
		{
			m_TextSuaVez->ShowWindow(SW_SHOW);

			if (m_Cliente->InstanciaEstaRodando())
			{
				if (m_Cliente->JogadorPodePedirTruco())
					m_BotaoTruco->ShowWindow(SW_SHOW);
			}
			else
			{
				if (m_Jogador->PodeTrucar())
					m_BotaoTruco->ShowWindow(SW_SHOW);
			}
			m_BotaoCorrer->ShowWindow(SW_SHOW);
		}
	}
	break;

	case StatusJogador::NaoEhSuaVez:
	{
		if (!m_Jogador->EhUmBot())
		{
			m_TextSuaVez->ShowWindow(SW_HIDE);
			m_BotaoTruco->ShowWindow(SW_HIDE);
			m_BotaoCorrer->ShowWindow(SW_HIDE);
		}
	}
	break;



	case StatusJogador::Truca:
	{
		m_BotaoTruco->ShowWindow(SW_HIDE);
	}
	break;

	}
}

	void JogadorView::JogouACarta(const Carta * carta, bool cartaCoberta)
	{
		m_pDialog->m_MesaView->JogadorJogouACarta(m_Jogador, carta, cartaCoberta, m_Partida->ObtemNumeroDaRodada(), m_Partida->ObtemNumeroDeJogadores());

		if (m_Jogador->PrimeiraCartaNaMao()->idResource == carta->idResource)
		{
			m_Carta1View->ShowWindow(SW_HIDE);
		}
		else if (m_Jogador->PrimeiraCartaNaMao()->idResource == carta->idResource)
		{
			m_Carta2View->ShowWindow(SW_HIDE);
		}
		else if (m_Jogador->PrimeiraCartaNaMao()->idResource == carta->idResource)
		{
			m_Carta3View->ShowWindow(SW_HIDE);
		}
	}
