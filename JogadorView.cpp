#include "pch.h"
#include "Enums.h"
#include "JogadorView.h"
#include "afxdialogex.h"
#include "Jogador.h"
#include "DadosInstanciaCliente.h"
#include "CartasBitmap.h"
#include "TrucoPaulistaDlg.h"
#include "Partida.h"

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

	}
}