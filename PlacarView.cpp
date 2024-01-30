#include "pch.h"
#include "PlacarView.h"
#include "TrucoPaulistaDlg.h"
#include "Partida.h"
#include "Jogador.h"
#include "Resource.h"

PlacarView::PlacarView(CTrucoPaulistaDlg* pDialog, Partida* partida)
{
	m_pDialog = pDialog;
	m_Partida = partida;

	//Rodada

	//Pontos

	//Tentos

	//Partidas


}

void PlacarView::AtualizaTento()
{
	int valor = m_Partida->ObterValorDaRodada();
	CString str;
	str.Format(_T("%d"), valor);
	m_pDialog->GetDlgItem(IDC_TENTOS)->SetWindowText(str);
}

void PlacarView::AtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2)
{
	CString str;
	str.Format(_T("%d"), PontosDaDupla1);
	m_pDialog->GetDlgItem(IDC_PONTOS_DUPLA1)->SetWindowText(str);

	str.Format(_T("%d"), PontosDaDupla2);
	m_pDialog->GetDlgItem(IDC_PONTOS_DUPLA2)->SetWindowText(str);
}


void PlacarView::AtualizaPlacarDePartidas()
{
	CString str;
	str.Format(_T("%d"), m_Partida->PartidasVencidasDaDupla1());
	m_pDialog->GetDlgItem(IDC_PONTOS_PARTIDA_DUPLA1)->SetWindowText(str);
	str.Format(_T("%d"), m_Partida->PartidasVencidasDaDupla2());
	m_pDialog->GetDlgItem(IDC_PONTOS_PARTIDA_DUPLA2)->SetWindowText(str);
}

void PlacarView::InicializaRodadasCheckBox()
{
	for (int i = IDC_CHECK1; i <= IDC_CHECK6; i++)
	{
		CButton* pCheckBox = (CButton*)m_pDialog->GetDlgItem(i);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_UNCHECKED);
	}
}

void PlacarView::QuemGanhouARodadaCheckBox(int numeroRodada, Jogador* jogadorQueGanhou)
{
	if (jogadorQueGanhou == nullptr) // Empatou
	{
		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		CButton* pCheckBox = (CButton*)m_pDialog->GetDlgItem(baseCheckBox);
		pCheckBox->SetCheck(BST_CHECKED);

		pCheckBox = (CButton*)m_pDialog->GetDlgItem(baseCheckBox + 1);
		pCheckBox->SetCheck(BST_CHECKED);
	}
	else
	{
		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		baseCheckBox = jogadorQueGanhou->EhUmBot() ? baseCheckBox + 1 : baseCheckBox;
		CButton* pCheckBox = (CButton*)m_pDialog->GetDlgItem(baseCheckBox);
		pCheckBox->SetCheck(BST_CHECKED);
	}
}

void PlacarView::LimpaOutput()
{
	CEdit* pEdit = static_cast<CEdit*>(m_pDialog->GetDlgItem(IDC_EDIT_TEXT_OUTPUT));
	CString strTextoAtual;
	strTextoAtual = _T("");
	pEdit->SetWindowText(strTextoAtual);

}

void PlacarView::EscreveNoOutput(const CString& novaLinha)
{
	CEdit* pEdit = static_cast<CEdit*>(m_pDialog->GetDlgItem(IDC_EDIT_TEXT_OUTPUT));
	CString strTextoAtual;
	pEdit->GetWindowText(strTextoAtual);
	strTextoAtual += novaLinha + _T("\r\n");
	pEdit->SetWindowText(strTextoAtual);
	pEdit->LineScroll(pEdit->GetLineCount());
}

void PlacarView::InicializaRodada()
{
	m_pDialog->GetDlgItem(IDC_RB2PLAYERS)->ShowWindow(SW_HIDE);
	m_pDialog->GetDlgItem(IDC_RB4PLAYERS)->ShowWindow(SW_HIDE);
	m_pDialog->GetDlgItem(IDC_RB4PLAYERS_REMOTE)->ShowWindow(SW_HIDE);
	m_pDialog->GetDlgItem(IDC_BTN_START)->ShowWindow(SW_HIDE);
	m_pDialog->GetDlgItem(IDC_EDIT_TEXT_OUTPUT)->ShowWindow(SW_SHOW);

	InicializaRodadasCheckBox();
}