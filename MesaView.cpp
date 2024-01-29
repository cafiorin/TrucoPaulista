#include "pch.h"
#include "MesaView.h"
#include "Resource.h"
#include "CartasBitmap.h"

MesaView::MesaView(CTrucoPaulistaDlg* pDialog)
{
	m_pDialog = pDialog;

	m_PicMesa = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC4));
	m_PicBaralho = dynamic_cast<CStatic *>(pDialog->GetDlgItem(IDC_PIC15));
	m_PicVira = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC14));
	m_CartaH1_R1 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H1_R1));
	m_CartaH2_R1 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H2_R1));
	m_CartaH1_R2 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H1_R2));
	m_CartaH2_R2 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H2_R2));
	m_CartaH1_R3 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H1_R3));
	m_CartaH2_R3 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_H2_R3));
	m_CartaBOT1_R1 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT1_R1));
	m_CartaBOT1_R2 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT1_R2));
	m_CartaBOT1_R3 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT1_R3));
	m_CartaBOT2_R1 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT2_R1));
	m_CartaBOT2_R2 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT2_R2));
	m_CartaBOT2_R3 = dynamic_cast<CStatic*>(pDialog->GetDlgItem(IDC_PIC_CARTA_BOT2_R3));
}

void MesaView::Inicializa()
{
	//Desenha a Mesa
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_MESA);
	m_pDialog->SetBitmapOnStaticControl(*m_PicMesa, bitmap);

	//Desenha o Baralho
	CBitmap bitmapVerso;
	bitmapVerso.LoadBitmap(IDB_BITMAP_VERSO);
	m_pDialog->SetBitmapOnStaticControl(*m_PicBaralho, bitmapVerso);

	//Esconde o Vira ate o jogo comecar
	m_PicVira->ShowWindow(SW_HIDE);

	InicializaRodada(0);
}

void MesaView::InicializaRodada(int idViraResource)
{
	m_CartaH1_R1->ShowWindow(SW_HIDE);
	m_CartaH1_R2->ShowWindow(SW_HIDE);
	m_CartaH1_R3->ShowWindow(SW_HIDE);

	m_CartaH2_R1->ShowWindow(SW_HIDE);
	m_CartaH2_R2->ShowWindow(SW_HIDE);
	m_CartaH2_R3->ShowWindow(SW_HIDE);

	m_CartaBOT1_R1->ShowWindow(SW_HIDE);
	m_CartaBOT1_R2->ShowWindow(SW_HIDE);
	m_CartaBOT1_R3->ShowWindow(SW_HIDE);

	m_CartaBOT2_R1->ShowWindow(SW_HIDE);
	m_CartaBOT2_R2->ShowWindow(SW_HIDE);
	m_CartaBOT2_R3->ShowWindow(SW_HIDE);

	if (idViraResource > 0)
	{
		CartasBitmap cartaVira(idViraResource);
		m_pDialog->SetBitmapOnStaticControl(*m_PicVira, *cartaVira.Getbitmap());

		m_PicVira->ShowWindow(SW_SHOW);
	}
}

void MesaView::JogadorJogouACarta(Jogador* jogador, const Carta* carta, bool cartaCoberta, int rodada, int numeroDeJogadores)
{
	int numeroDoJogador = jogador->ObtemNumeroJogador();
	CStatic* pictureControl = nullptr;

	if (numeroDeJogadores == 2)
	{
		CStatic* jogadorPorRodada[3][2] = 
		{
			{m_CartaH2_R1, m_CartaBOT1_R1},
			{m_CartaH2_R2, m_CartaBOT1_R2},
			{m_CartaH2_R3, m_CartaBOT1_R3}
		};

		pictureControl = jogadorPorRodada[rodada-1][numeroDoJogador - 1];
	}
	else // duplas
	{
		CStatic* jogadorPorRodada[3][4] =
		{
			{m_CartaH1_R1, m_CartaH2_R1, m_CartaBOT1_R1, m_CartaBOT2_R1},
			{m_CartaH1_R2, m_CartaH2_R2, m_CartaBOT1_R2, m_CartaBOT2_R2},
			{m_CartaH1_R3, m_CartaH2_R3, m_CartaBOT1_R3, m_CartaBOT2_R3}
		};
		
		pictureControl = jogadorPorRodada[rodada - 1][numeroDoJogador - 1];
	}

	if (pictureControl != nullptr)
	{
		CartasBitmap bitmap(cartaCoberta ? IDB_BITMAP_VERSO : carta->idResource );
		m_pDialog->SetBitmapOnStaticControl(*pictureControl, *bitmap.Getbitmap());
		pictureControl->ShowWindow(SW_SHOW);
	}
}

