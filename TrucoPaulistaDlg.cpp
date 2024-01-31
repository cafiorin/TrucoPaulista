// TrucoPaulistaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TrucoPaulista.h"
#include "afxdialogex.h"
#include "CartasBitmap.h"
#include "Baralho.h"
#include "Jogador.h"
#include "Partida.h"
#include "resource.h"
#include "TrucoPaulistaDlg.h"
#include "AboutDlg.h"
#include "PartidaMessagesController.h"
#include "PersistenciaController.h"
#include "MesaView.h"
#include "JogadorView.h"
#include "DadosInstanciaCliente.h"
#include "PlacarView.h"

#include <atlimage.h>
#include <windows.h>

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

CTrucoPaulistaDlg::CTrucoPaulistaDlg(CWnd* pParent) : CDialogEx(IDD_TRUCOPAULISTA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_JogadorHumano1View = nullptr;
	m_JogadorHumano2View = nullptr;
	m_JogadorBot1View = nullptr;
	m_JogadorBot2View = nullptr;
	partida = nullptr;
	partidaMessagesController = nullptr;
	persistencia = nullptr;
	cartaCoberta = nullptr;
	m_MesaView = nullptr;
	m_Cliente = nullptr;
	m_PlacarView = nullptr;
}

CTrucoPaulistaDlg::~CTrucoPaulistaDlg()
{
	delete partida;
	delete partidaMessagesController;
	delete persistencia;
	delete cartaCoberta;

	delete m_JogadorHumano1View;
	delete m_JogadorHumano2View;
	delete m_JogadorBot1View;
	delete m_JogadorBot2View;

	delete m_MesaView;
	delete m_Cliente;
	delete m_PlacarView;
}


BOOL CTrucoPaulistaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!VerifyInstances())
		return FALSE;

	CFont* currentFont = GetFont();
	LOGFONT lf;
	currentFont->GetLogFont(&lf);
	lf.lfHeight = 28;
	m_Font.DeleteObject();
	m_Font.CreateFontIndirect(&lf);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);


	m_MesaView = new MesaView(this);
	m_Cliente = new DadosInstanciaCliente();
	partida = new Partida(this);
	m_PlacarView = new PlacarView(this,partida);
	JogadorView::ControiJogadoresView(this, m_Cliente, partida);
	partidaMessagesController = new PartidaMessagesController(this, m_Instance == 1);
	persistencia = new PersistenciaController(partida);
	cartaCoberta = new CartaCoberta();

	InicializaTelaInicial();
	InitFontToText(IDC_SUAVEZ_H1);
	InitFontToText(IDC_SUAVEZ_H2);

	if (m_Instance == 2)
	{
		InicializarPartidaCliente();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrucoPaulistaDlg::InicializarPartidaCliente()
{
	InicializaRodada();
}

void CTrucoPaulistaDlg::InicializaTelaInicial()
{
	m_MesaView->Inicializa();
	JogadorView::AtualizaStatusDosJogadores(this, StatusJogador::Inicia);

	CButton* pRadioButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_RB2PLAYERS));
	if (pRadioButton)
	{
		pRadioButton->SetCheck(BST_CHECKED);
	}
}

void CTrucoPaulistaDlg::InicializaPartida()
{
	TwoInstances = false;
	TipoDePartida tipoDePartida = ObtemTipoDePartida();

	if (tipoDePartida == TipoDePartida::QuatroJogadores_umremoto)
	{
		CreateNewInstance();
		TwoInstances = true;
	}

	partida->InicializarPartida(tipoDePartida);
	JogadorView::ControiJogadoresView(this, m_Cliente, partida);
	partida->InicializarRodada();
	InicializaRodada();
}


void CTrucoPaulistaDlg::OnBnClickedSync()
{
	HWND hwndExistingInstance = ::FindWindow(NULL, m_Instance == 1 ? _T("Truco Paulista - HUMANO 2") : _T("Truco Paulista - HUMANO 1"));

	if (hwndExistingInstance != NULL)
	{
		::SetForegroundWindow(hwndExistingInstance);
		::PostMessage(hwndExistingInstance, WM_CUSTOM_MESSAGE, 0, 0);
	}
	else
	{
		CreateNewInstance();
	}
}


void CTrucoPaulistaDlg::OnBnClickedButton1()
{
	InicializaPartida();
}

void CTrucoPaulistaDlg::JogadorClicouNaCarta(Jogador *jogador, int posicaoDaCarta)
{
	if (JogadorSolicitado != jogador)
		return;

	if (m_Instance == 1 || partida->ObtemNumeroDeJogadores() == 2)
	{
		const Carta* carta = jogador->getjogadabot(posicaoDaCarta-1);
		m_JogadorHumano1View->JogouACarta(carta);
		partida->JogadorJogouACarta(jogador, carta, false);
	}
}

void CTrucoPaulistaDlg::JogadorParceiroClicouNaCarta(Jogador* jogador, int posicaoDaCarta)
{
	if (JogadorSolicitado != jogador || TwoInstances)
		return;

	if (m_Instance == 2)
	{
		int ID = IDC_PIC13 - posicaoDaCarta + 1;
		GetDlgItem(ID)->ShowWindow(SW_HIDE);
		partidaMessagesController->JogadorJogouCarta(posicaoDaCarta, false);
	}
	else if (partida->ObtemNumeroDeJogadores() == 4)
	{
		const Carta* carta = jogador->getjogadabot(posicaoDaCarta - 1);
		m_JogadorHumano2View->JogouACarta(carta);
		partida->JogadorJogouACarta(jogador, carta, false);
	}
}

void CTrucoPaulistaDlg::OnStnClickedPic3()
{
	JogadorClicouNaCarta(partida->ObtemJogadorHumano1(), 3);
}

void CTrucoPaulistaDlg::OnStnClickedPic2()
{
	JogadorClicouNaCarta(partida->ObtemJogadorHumano1(), 2);
}

void CTrucoPaulistaDlg::OnStnClickedPic1()
{
	JogadorClicouNaCarta(partida->ObtemJogadorHumano1(), 1);
}

void CTrucoPaulistaDlg::OnStnClickedPicParc3()
{
	JogadorParceiroClicouNaCarta(partida->ObtemJogadorHumano2(), 1);
}


void CTrucoPaulistaDlg::OnStnClickedPicParc2()
{
	JogadorParceiroClicouNaCarta(partida->ObtemJogadorHumano2(), 2);
}


void CTrucoPaulistaDlg::OnStnClickedPicParc1()
{
	JogadorParceiroClicouNaCarta(partida->ObtemJogadorHumano2(), 3);
}

int CTrucoPaulistaDlg::ObtemNumeroDaRodada()
{
	if (m_Instance == 1)
		return partida->ObtemNumeroDaRodada();

	return m_Cliente->ObtemRodadaAtual();
}

void CTrucoPaulistaDlg::JogadorCobriuACarta(int idControl)
{
	if (partida->ObtemNumeroDaRodada() > 1)
	{
		if (idControl >= IDC_PIC1 && idControl <= IDC_PIC3)
		{
			if (JogadorSolicitado == partida->ObtemJogadorHumano1())
			{
				const Carta* carta = JogadorSolicitado->getjogadabot(idControl - IDC_PIC1);
				m_JogadorHumano1View->JogouACarta(carta, true);
				partida->JogadorJogouACarta(JogadorSolicitado, carta, true);
			}
		}
		else if (JogadorSolicitado == partida->ObtemJogadorHumano2())
		{
			if (m_Instance == 2)
			{
				m_PicCartaParc1.ShowWindow(SW_HIDE);
				partidaMessagesController->JogadorJogouCarta(idControl - IDC_PIC_PARC1 + 1, true);
			}
			else if (!TwoInstances)
			{
				const Carta* carta = JogadorSolicitado->getjogadabot(idControl - IDC_PIC_PARC1);
				m_JogadorHumano2View->JogouACarta(carta, true);
				partida->JogadorJogouACarta(JogadorSolicitado, carta, true);
			}
		}
	}
}


void CTrucoPaulistaDlg::MouseLeftClick(int idControl)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::MouseLeftClick()\n"));

	JogadorCobriuACarta(idControl);
}


void CTrucoPaulistaDlg::onInicioDaPartida()
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onInicioDaPartida()\n"));
}

void CTrucoPaulistaDlg::onFimDaPartida(Jogador* JogadorQueGanhou)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onFimDaPartida()\n"));

	std::string playerName = JogadorQueGanhou->ObtemNome();
	CString strPlayerName(playerName.c_str());
	CString str;
	str.Format(_T("PARABENS !!!! O jogador %s ganhou a PARTIDA!!!!"), strPlayerName);

	AtualizaPlacarDePartidas();

	if (m_Instance == 1)
		partidaMessagesController->EnviaFimDaPartida(JogadorQueGanhou->ObtemNumeroJogador());

	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);

	partida->InicializarPartida(partida->ObtemTipoDePartida());
	JogadorView::ControiJogadoresView(this, m_Cliente, partida);
	partida->InicializarRodada();
	InicializaRodada();
}

void CTrucoPaulistaDlg::onInicioDaRodada(int numeroRodada)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onInicioDaRodada()\n"));

	CleanCheckBox();
	CleanOutput();
	solicitaJogadorJogar(partida->QuemJoga());
}

void CTrucoPaulistaDlg::onAceitouTruco(Jogador* jogador)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onAceitouTruco()\n"));

	if (jogador->EhUmBot())
	{
		std::string playerName = jogador->ObtemNome();
		CString strPlayerName(playerName.c_str());
		CString str;
		str.Format(_T("Jogador %s aceitou o Truco... Manda !"), strPlayerName);
		AddOutput(str);
		if (m_Instance == 1 && TwoInstances)
			partidaMessagesController->EnviaAceitouTruco(jogador->ObtemNumeroJogador());
		AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
	}

	AtualizaTento();

}

void CTrucoPaulistaDlg::onFimDaRodada(int numeroRodada, Jogador* JogadorQueGanhou)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onFimDaRodada()\n"));

	if (JogadorQueGanhou == nullptr)
	{
		CString str;
		str.Format(_T("Empatou a rodada %d..."), numeroRodada);
		AddOutput(str);

		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);

		pCheckBox = (CButton*)GetDlgItem(baseCheckBox + 1);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);
	}
	else
	{
		std::string playerName = JogadorQueGanhou->ObtemNome();
		CString strPlayerName(playerName.c_str());

		CString str;
		str.Format(_T("Jogador %s ganhou a rodada %d..."), strPlayerName, numeroRodada);
		AddOutput(str);

		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		baseCheckBox = JogadorQueGanhou->EhUmBot() ? baseCheckBox + 1 : baseCheckBox;

		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);

	}

	if (m_Instance == 1 && TwoInstances)
		partidaMessagesController->EnviaFimDaRodada(numeroRodada, JogadorQueGanhou ? JogadorQueGanhou->ObtemNumeroJogador() : 0);
}


void CTrucoPaulistaDlg::CleanOutput()
{
	CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_TEXT_OUTPUT));
	CString strTextoAtual;
	strTextoAtual = _T("");
	pEdit->SetWindowText(strTextoAtual);

}

void CTrucoPaulistaDlg::AddOutput(const CString& novaLinha)
{
	CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(IDC_EDIT_TEXT_OUTPUT));
	CString strTextoAtual;
	pEdit->GetWindowText(strTextoAtual);
	strTextoAtual += novaLinha + _T("\r\n");
	pEdit->SetWindowText(strTextoAtual);
	pEdit->LineScroll(pEdit->GetLineCount());
}

void CTrucoPaulistaDlg::AtualizaDeQuemEhAVezDeJogar(Jogador* jogador)
{
	if (jogador->ObtemNumeroJogador() == 1)
	{
		JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::SuaVez, jogador);
		JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::NaoEhSuaVez, partida->ObtemJogadorHumano2());
	}
	else if (jogador->ObtemNumeroJogador() == 3 && !TwoInstances)
	{
		JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::SuaVez, jogador);
		JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::NaoEhSuaVez, partida->ObtemJogadorHumano1());
	}
}

void CTrucoPaulistaDlg::solicitaJogadorJogar(Jogador* jogador)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::solicitaJogadorJogar()\n"));

	std::string playerName = jogador->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("Sua Vez %s..."), strPlayerName);
	AddOutput(str);

	AtualizaDeQuemEhAVezDeJogar(jogador);

	JogadorSolicitado = jogador;

	if (m_Instance == 1 && TwoInstances && jogador == partida->ObtemJogadorHumano2())
	{
		partidaMessagesController->SolicitaJogadorAJogar();
	}
}

void CTrucoPaulistaDlg::onBotJogouACarta(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada, bool cartaCoberta)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onBotJogouACarta()\n"));

	std::string playerName = jogadorAjogar->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("Sua Vez %s..."), strPlayerName);
	AddOutput(str);

	JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::NaoEhSuaVez, partida->ObtemJogadorHumano1());
	JogadorView::AtualizaStatusDoJogadorEscolhido(this, StatusJogador::NaoEhSuaVez, partida->ObtemJogadorHumano1());

	if(jogadorAjogar == partida->ObtemJogadorBot1())
		m_JogadorBot1View->JogouACarta(cartaJogada, cartaCoberta);
	else
		m_JogadorBot2View->JogouACarta(cartaJogada, cartaCoberta);

	Invalidate();
}

void CTrucoPaulistaDlg::onPedeTruco(Jogador* jogador)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onPedeTruco()\n"));

	CString quantovale = partida->ObterMensagemDeQuantoVale();
	CString str;
	str.Format(_T("%s !!!!"), quantovale);
	AddOutput(str);

	str.Format(_T("Aceita o %s ?"), quantovale);
	int resultado = AfxMessageBox(str, MB_YESNO | MB_ICONQUESTION);

	if (resultado == IDYES)
	{
		partida->JogadorAceitou(jogador);
	}
	else
	{
		partida->JogadorCorreu(jogador);
		return;
	}
}

void CTrucoPaulistaDlg::onAcabouARodada(Jogador* JogadorQueGanhou)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onAcabouARodada()\n"));

	std::string playerName = JogadorQueGanhou->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("O jogador %s ganhou a rodada"), strPlayerName);
	AddOutput(str);

	if (m_Instance == 1 && TwoInstances)
		partidaMessagesController->EnviaFimDaPartida(JogadorQueGanhou->ObtemNumeroJogador());

	AtualizaPlacarDePartidas();
	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);

	bool botComeca = partida->InicializarRodada();
	InicializaRodada();
	if (botComeca)
		partida->ProximoJogadorJoga();
}

void CTrucoPaulistaDlg::onCartaJogada(int NumeroDaRodada, Jogador* jogador, const Carta* carta, bool _cartaCoberta)
{
	OutputDebugString(_T("CTrucoPaulistaDlg::onCartaJogada()\n"));

	if (TwoInstances && m_Instance == 1)
	{
		partidaMessagesController->AtualizaCartaJogada(NumeroDaRodada, jogador->ObtemNumeroJogador(), _cartaCoberta ? cartaCoberta->idResource : carta->idResource);
	}
}

void CTrucoPaulistaDlg::AtualizaPlacar()
{
	if (m_Instance == 1)
	{
		m_PlacarView->AtualizaPlacar(partida->PontosDaDupla1(), partida->PontosDaDupla2());

		if (TwoInstances)
			partidaMessagesController->EnviaMsgDeAtualizaPlacar(partida->PontosDaDupla1(), partida->PontosDaDupla2());
	}
}

void CTrucoPaulistaDlg::AtualizaTento()
{
	m_PlacarView->AtualizaTento();
	JogadorView::AtualizaStatusDosJogadores(this, StatusJogador::AtualizaTento);
	if (m_Instance == 1 && TwoInstances)
	{
		partidaMessagesController->EnviaMsgDeAtualizaTento(partida->ObterValorDaRodada());
	}
}

void CTrucoPaulistaDlg::AtualizaPlacarDePartidas()
{
	m_PlacarView->AtualizaPlacarDePartidas();
	if (TwoInstances)
		partidaMessagesController->EnviaMsgDeAtualizaPlacar(partida->PartidasVencidasDaDupla1(), partida->PartidasVencidasDaDupla2());
}

void CTrucoPaulistaDlg::InicializaRodada()
{
	m_Cliente->InicializaRodada();
	m_Cliente->JogadorPodePedirTruco();
	m_PlacarView->InicializaRodada();

	AtualizaPlacar();

	JogadorView::AtualizaStatusDosJogadores(this, StatusJogador::Inicia);

	if (m_Instance == 1)
	{
		JogadorView::AtualizaStatusDosJogadores(this, StatusJogador::RecebeuCartas);
		m_MesaView->InicializaRodada(partida->ObtemVira()->idResource);
		Jogador* jogadorDaVez = partida->QuemJoga();
		AtualizaDeQuemEhAVezDeJogar(jogadorDaVez);

		CString quantovale = partida->ObterMensagemDeQuantoVale();
		GetDlgItem(IDC_TRUCAR)->SetWindowTextW(quantovale);
		GetDlgItem(IDC_TRUCAR2)->SetWindowTextW(quantovale);
		AtualizaTento();
	}

	if (TwoInstances)
	{
		partidaMessagesController->EnviaInicializaRodada();

		Sleep(1000);//Espera instancia aparecer

		Jogador* jogador2 = partida->ObtemJogadorHumano2();
		int c1 = jogador2->PrimeiraCartaNaMao()->idResource;
		int c2 = jogador2->SegundaCartaNaMao()->idResource;
		int c3 = jogador2->TerceiraCartaNaMao()->idResource;
		int c4 = partida->ObtemVira()->idResource;
		partidaMessagesController->EnviaCartasParaJogador(c1, c2, c3, c4);
	}

	Invalidate();
}

void CTrucoPaulistaDlg::OnBnClickedTrucar()
{
	Jogador* jogador = partida->ObtemJogadorHumano1();
	if (JogadorSolicitado == jogador)
	{
		m_JogadorHumano1View->AtualizaStatusDoJogador(StatusJogador::Truca);
		partida->JogadorTrucou(jogador);
	}
}

void CTrucoPaulistaDlg::OnBnClickedCorrer()
{
	Jogador* jogador = partida->ObtemJogadorHumano1();
	if (JogadorSolicitado == jogador)
	{
		partida->JogadorCorreu(jogador);
	}
}

void CTrucoPaulistaDlg::OnBnClickedTrucar2()
{
	Jogador* jogador = partida->ObtemJogadorHumano2();
	if (JogadorSolicitado == jogador)
	{
		if (m_Instance == 2)
		{
			partidaMessagesController->EnviaTruco(jogador->ObtemNumeroJogador());
		}
		else
		{
			m_JogadorHumano2View->AtualizaStatusDoJogador(StatusJogador::Truca);
			partida->JogadorTrucou(jogador);
		}
	}
}

void CTrucoPaulistaDlg::OnBnClickedCorrer2()
{
	Jogador* jogador = partida->ObtemJogadorHumano2();
	if (JogadorSolicitado == jogador)
	{
		if (m_Instance == 2)
		{
			partidaMessagesController->EnviaCorreTruco(jogador->ObtemNumeroJogador());
		}
		else
		{
			partida->JogadorCorreu(jogador);
		}
	}
}


//Metodos da instancia Cliente

void CTrucoPaulistaDlg::AtualizaPlacarCliente(int PontosDaDupla1, int PontosDaDupla2)
{

	CString str;
	str.Format(_T("%d"), PontosDaDupla1);
	GetDlgItem(IDC_PONTOS_DUPLA1)->SetWindowText(str);

	str.Format(_T("%d"), PontosDaDupla2);
	GetDlgItem(IDC_PONTOS_DUPLA2)->SetWindowText(str);

}

void CTrucoPaulistaDlg::AtualizaCartasJogadasCliente(int numeroDaRodada, int numeroJogador, int carta)
{
	if (m_Instance == 2)
	{
		SetCurrectBitmapCliente(numeroDaRodada, numeroJogador, carta);
	}
}
void CTrucoPaulistaDlg::AtualizaTentoCliente(int tento)
{
	CString str;
	str.Format(_T("%d"), tento);
	GetDlgItem(IDC_TENTOS)->SetWindowText(str);

}

void CTrucoPaulistaDlg::InicializaRodadaCliente(int jogadorQueComeca)
{
	if (m_Instance == 2)
	{
		InicializaRodada();
	}
}

void CTrucoPaulistaDlg::ShowMessageJogadorAceitouTruco(int jogadorqueTrucou)
{
	Jogador* jogador = partida->GetJogadorByID(jogadorqueTrucou);
	std::string playerName = jogador->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("Jogador %s aceitou o Truco... Manda !"), strPlayerName);
	AddOutput(str);

	if (m_Instance == 1 && TwoInstances)
		partidaMessagesController->EnviaAceitouTruco(jogador->ObtemNumeroJogador());

	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
}
void CTrucoPaulistaDlg::ShowMessageQuemGanhouaRodada(int numeroRodada, int jogadorGanhouRodada)
{
	m_Cliente->ProximaRodada();

	Jogador* JogadorQueGanhou = partida->GetJogadorByID(jogadorGanhouRodada);
	if (JogadorQueGanhou == nullptr)
	{
		CString str;
		str.Format(_T("Empatou a rodada %d..."), numeroRodada);
		AddOutput(str);

		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);

		pCheckBox = (CButton*)GetDlgItem(baseCheckBox + 1);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);
	}
	else
	{
		std::string playerName = JogadorQueGanhou->ObtemNome();
		CString strPlayerName(playerName.c_str());
		CString str;
		str.Format(_T("Jogador %s ganhou a rodada %d..."), strPlayerName, numeroRodada);
		AddOutput(str);
		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		baseCheckBox = JogadorQueGanhou->EhUmBot() ? baseCheckBox + 1 : baseCheckBox;

		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);
	}
}
void CTrucoPaulistaDlg::Jogador2Correu(int jogadorGanhouPartida)
{
	Jogador* JogadorCorreu = partida->GetJogadorByID(jogadorGanhouPartida);
	partida->JogadorCorreu(JogadorCorreu);
}
void CTrucoPaulistaDlg::Jogador2Trucou(int jogadorGanhouPartida)
{
	Jogador* jogador = partida->GetJogadorByID(jogadorGanhouPartida);
	if (JogadorSolicitado == jogador)
	{
		GetDlgItem(IDC_TRUCAR)->ShowWindow(SW_HIDE);
		partida->JogadorTrucou(jogador);
	}
}
void CTrucoPaulistaDlg::ShowMessageQuemGanhoaPartida(int jogadorGanhador)
{
	AtualizaPlacarDePartidas();

	Jogador* JogadorQueGanhou = partida->GetJogadorByID(jogadorGanhador);
	std::string playerName = JogadorQueGanhou->ObtemNome();
	CString strPlayerName(playerName.c_str());
	CString str;
	str.Format(_T("PARABENS !!!! O jogador %s ganhou a PARTIDA!!!!"), strPlayerName);
	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
}

void CTrucoPaulistaDlg::SetCurrectBitmapCliente(int rodada, int numeroJogador, int carta)
{
	CartasBitmap bitmap(carta);

	if (numeroJogador == 1)
	{
		switch (rodada)
		{
		case 1:
			SetBitmapOnStaticControl(m_CartaH2_R1, *bitmap.Getbitmap());
			m_CartaH2_R1.ShowWindow(SW_SHOW);
			m_Pic1.ShowWindow(SW_HIDE);
			break;
		case 2:
			SetBitmapOnStaticControl(m_CartaH2_R2, *bitmap.Getbitmap());
			m_CartaH2_R2.ShowWindow(SW_SHOW);
			m_Pic2.ShowWindow(SW_HIDE);
			break;
		case 3:
			SetBitmapOnStaticControl(m_CartaH2_R3, *bitmap.Getbitmap());
			m_CartaH2_R3.ShowWindow(SW_SHOW);
			m_Pic3.ShowWindow(SW_HIDE);
			break;
		}
	}
	else if (numeroJogador == 2)
	{
		switch (rodada)
		{
		case 1:
			SetBitmapOnStaticControl(m_CartaBOT1_R1, *bitmap.Getbitmap());
			m_CartaBOT1_R1.ShowWindow(SW_SHOW);
			m_PicCartaOp1.ShowWindow(SW_HIDE);
			break;
		case 2:
			SetBitmapOnStaticControl(m_CartaBOT1_R2, *bitmap.Getbitmap());
			m_CartaBOT1_R2.ShowWindow(SW_SHOW);
			m_PicCartaOp2.ShowWindow(SW_HIDE);
			break;
		case 3:
			SetBitmapOnStaticControl(m_CartaBOT1_R3, *bitmap.Getbitmap());
			m_CartaBOT1_R3.ShowWindow(SW_SHOW);
			m_PicCartaOp3.ShowWindow(SW_HIDE);
			break;
		}
	}
	else if (numeroJogador == 3)
	{
		switch (rodada)
		{
		case 1:
			SetBitmapOnStaticControl(m_CartaH1_R1, *bitmap.Getbitmap());
			m_CartaH1_R1.ShowWindow(SW_SHOW);
			break;
		case 2:
			SetBitmapOnStaticControl(m_CartaH1_R2, *bitmap.Getbitmap());
			m_CartaH1_R2.ShowWindow(SW_SHOW);
			break;
		case 3:
			SetBitmapOnStaticControl(m_CartaH1_R3, *bitmap.Getbitmap());
			m_CartaH1_R3.ShowWindow(SW_SHOW);
			break;
		}
	}
	else if (numeroJogador == 4)
	{
		switch (rodada)
		{
		case 1:
			SetBitmapOnStaticControl(m_CartaBOT2_R1, *bitmap.Getbitmap());
			m_CartaBOT2_R1.ShowWindow(SW_SHOW);
			m_PicCartaOp21.ShowWindow(SW_HIDE);
			break;
		case 2:
			SetBitmapOnStaticControl(m_CartaBOT2_R2, *bitmap.Getbitmap());
			m_CartaBOT2_R2.ShowWindow(SW_SHOW);
			m_PicCartaOp22.ShowWindow(SW_HIDE);
			break;
		case 3:
			SetBitmapOnStaticControl(m_CartaBOT2_R3, *bitmap.Getbitmap());
			m_CartaBOT2_R3.ShowWindow(SW_SHOW);
			m_PicCartaOp23.ShowWindow(SW_HIDE);
			break;
		}
	}
	Invalidate();
}



void CTrucoPaulistaDlg::JogouACartaCliente(int numeroCarta, bool _cartaCoberta)
{
	if (m_Instance == 1)
	{
		Jogador* jogador = partida->ObtemJogadorHumano2();
		const Carta* carta = jogador->getjogadabot(numeroCarta - 1);
		m_JogadorHumano2View->JogouACarta(carta, _cartaCoberta);
		partida->JogadorJogouACarta(jogador, carta, _cartaCoberta);
	}
}


void CTrucoPaulistaDlg::SolicitaAcaoJogadorCliente()
{
	if (m_Instance == 2)
	{
		solicitaJogadorJogar(partida->ObtemJogadorHumano2());
	}
}

void CTrucoPaulistaDlg::AtualizaCartasCliente(int c1, int c2, int c3, int c4)
{
	if (m_Instance == 2)
	{
		AtualizaClientePodeTrucar(true);
		m_JogadorBot1View->AtualizaStatusDoJogador(StatusJogador::RecebeuCartas);
		m_JogadorBot2View->AtualizaStatusDoJogador(StatusJogador::RecebeuCartas);
		m_JogadorHumano1View->AtualizaStatusDoJogador(StatusJogador::RecebeuCartas);

		CartasBitmap cartaBitmap1(c1);
		CartasBitmap cartaBitmap2(c2);
		CartasBitmap cartaBitmap3(c3);

		SetBitmapOnStaticControl(m_PicCartaParc1, *cartaBitmap1.Getbitmap());
		SetBitmapOnStaticControl(m_PicCartaParc2, *cartaBitmap2.Getbitmap());
		SetBitmapOnStaticControl(m_PicCartaParc3, *cartaBitmap3.Getbitmap());
		m_PicCartaParc1.ModifyStyle(0, SS_NOTIFY);
		m_PicCartaParc2.ModifyStyle(0, SS_NOTIFY);
		m_PicCartaParc3.ModifyStyle(0, SS_NOTIFY);
		m_PicCartaParc1.ShowWindow(SW_SHOW);
		m_PicCartaParc2.ShowWindow(SW_SHOW);
		m_PicCartaParc3.ShowWindow(SW_SHOW);

		CartasBitmap cartaBitmap4(c4);
		SetBitmapOnStaticControl(m_PicVira, *cartaBitmap4.Getbitmap());
		m_PicVira.ShowWindow(SW_SHOW);

		Invalidate();
	}
}

void CTrucoPaulistaDlg::AtualizaClientePodeTrucar(bool trucar)
{
	m_Cliente->SetaPodePedirTruco(trucar);
}

void CTrucoPaulistaDlg::OnBnClickedSalvar()
{
	if (persistencia != nullptr) { // Somente primeira instância irá salvar?
		bool temJogoSalvo = persistencia->TemJogoSalvo();

		persistencia->AtualizarArquivo();
	}
}

void CTrucoPaulistaDlg::CleanCheckBox()
{
	for (int i = IDC_CHECK1; i <= IDC_CHECK6; i++)
	{
		CButton* pCheckBox = (CButton*)GetDlgItem(i);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_UNCHECKED);
	}
}

BOOL CTrucoPaulistaDlg::PreTranslateMessage(MSG* pMsg)
{
	// Msg trocada entre instancias
	if (pMsg->message >= WM_CUSTOM_MESSAGE_INICIO && pMsg->message <= WM_CUSTOM_MESSAGE_FIM)
	{
		partidaMessagesController->OnReceiveMessage(pMsg);
		return TRUE;
	}

	//Right click
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		CWnd* pWnd = ChildWindowFromPoint(point, CWP_ALL);
		if (pWnd)
		{
			MouseLeftClick(pWnd->GetDlgCtrlID());
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTrucoPaulistaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, m_Pic1);
	DDX_Control(pDX, IDC_PIC2, m_Pic2);
	DDX_Control(pDX, IDC_PIC3, m_Pic3);
	DDX_Control(pDX, IDC_PIC4, m_PicMesa);
	DDX_Control(pDX, IDC_PIC5, m_PicCartaOp1);
	DDX_Control(pDX, IDC_PIC7, m_PicCartaOp2);
	DDX_Control(pDX, IDC_PIC6, m_PicCartaOp3);
	DDX_Control(pDX, IDC_PIC9, m_PicCartaOp21);
	DDX_Control(pDX, IDC_PIC11, m_PicCartaOp22);
	DDX_Control(pDX, IDC_PIC10, m_PicCartaOp23);
	DDX_Control(pDX, IDC_PIC13, m_PicCartaParc1);
	DDX_Control(pDX, IDC_PIC12, m_PicCartaParc2);
	DDX_Control(pDX, IDC_PIC8, m_PicCartaParc3);
	DDX_Control(pDX, IDC_PIC15, m_PicBaralho);
	DDX_Control(pDX, IDC_PIC14, m_PicVira);
	DDX_Control(pDX, IDC_PIC_CARTA_H1_R1, m_CartaH1_R1);
	DDX_Control(pDX, IDC_PIC_CARTA_H2_R1, m_CartaH2_R1);
	DDX_Control(pDX, IDC_PIC_CARTA_H1_R2, m_CartaH1_R2);
	DDX_Control(pDX, IDC_PIC_CARTA_H2_R2, m_CartaH2_R2);
	DDX_Control(pDX, IDC_PIC_CARTA_H1_R3, m_CartaH1_R3);
	DDX_Control(pDX, IDC_PIC_CARTA_H2_R3, m_CartaH2_R3);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT1_R1, m_CartaBOT1_R1);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT1_R2, m_CartaBOT1_R2);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT1_R3, m_CartaBOT1_R3);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT2_R1, m_CartaBOT2_R1);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT2_R2, m_CartaBOT2_R2);
	DDX_Control(pDX, IDC_PIC_CARTA_BOT2_R3, m_CartaBOT2_R3);
}

BEGIN_MESSAGE_MAP(CTrucoPaulistaDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDM_ABOUTBOX, &CTrucoPaulistaDlg::OnBnClickedAbout)
	ON_BN_CLICKED(ID_SYNC, &CTrucoPaulistaDlg::OnBnClickedSync)
	ON_BN_CLICKED(IDC_BTN_START, &CTrucoPaulistaDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_PIC3, &CTrucoPaulistaDlg::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_PIC2, &CTrucoPaulistaDlg::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_PIC1, &CTrucoPaulistaDlg::OnStnClickedPic1)
	ON_BN_CLICKED(IDC_TRUCAR, &CTrucoPaulistaDlg::OnBnClickedTrucar)
	ON_BN_CLICKED(IDC_CORRER, &CTrucoPaulistaDlg::OnBnClickedCorrer)
	ON_STN_CLICKED(IDC_PIC_PARC3, &CTrucoPaulistaDlg::OnStnClickedPicParc3)
	ON_STN_CLICKED(IDC_PIC_PARC2, &CTrucoPaulistaDlg::OnStnClickedPicParc2)
	ON_STN_CLICKED(IDC_PIC_PARC1, &CTrucoPaulistaDlg::OnStnClickedPicParc1)
	ON_BN_CLICKED(IDC_TRUCAR2, &CTrucoPaulistaDlg::OnBnClickedTrucar2)
	ON_BN_CLICKED(IDC_CORRER2, &CTrucoPaulistaDlg::OnBnClickedCorrer2)
	ON_BN_CLICKED(IDC_SALVAR, &CTrucoPaulistaDlg::OnBnClickedSalvar)
END_MESSAGE_MAP()


HBRUSH CTrucoPaulistaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if (pWnd->GetSafeHwnd() == GetDlgItem(IDC_SUAVEZ_H1)->GetSafeHwnd() ||
			pWnd->GetSafeHwnd() == GetDlgItem(IDC_SUAVEZ_H2)->GetSafeHwnd())
		{
			pDC->SetTextColor(RGB(255, 0, 0));
			return (HBRUSH)GetStockObject(NULL_BRUSH);
		}
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	default:
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
}


BOOL CTrucoPaulistaDlg::VerifyInstances()
{
	m_Instance = 2;
	m_hMutex = CreateMutex(NULL, FALSE, _T("TrucoPaulista"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		SetWindowText(_T("Truco Paulista - HUMANO 2"));
		ReleaseMutex(m_hMutex);

		if (WaitForSingleObject(m_hMutex, 0) == WAIT_TIMEOUT)
		{
			// AfxMessageBox(_T("Apenas duas instâncias do aplicativo são permitidas."));
			PostMessage(WM_CLOSE);
		}
	}
	else
	{
		m_Instance = 1;
		SetWindowText(_T("Truco Paulista - HUMANO 1"));

	}
	return TRUE;
}

void CTrucoPaulistaDlg::InitFontToText(int idText)
{
	CStatic* pStaticText = (CStatic*)GetDlgItem(idText);
	if (pStaticText)
	{
		pStaticText->SetFont(&m_Font);
		pStaticText->ShowWindow(SW_HIDE);
	}
}

void CTrucoPaulistaDlg::SetBitmapOnStaticControl(CStatic& staticControl, CBitmap& bitmap)
{
	staticControl.ModifyStyle(SS_ENHMETAFILE, SS_BITMAP | SS_CENTERIMAGE);

	CRect rect;
	staticControl.GetClientRect(&rect);
	//rect.InflateRect(3, 3);

	CDC dc;
	dc.CreateCompatibleDC(nullptr);

	dc.SelectObject(&bitmap);

	BITMAP bmpInfo;
	bitmap.GetBitmap(&bmpInfo);
	int bmpWidth = bmpInfo.bmWidth;
	int bmpHeight = bmpInfo.bmHeight;

	CBitmap bmpResized;
	bmpResized.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CDC dcResized;
	dcResized.CreateCompatibleDC(nullptr);
	dcResized.SelectObject(&bmpResized);

	dcResized.SetStretchBltMode(HALFTONE);

	dcResized.SetBrushOrg(0, 0);
	dcResized.SetStretchBltMode(COLORONCOLOR);
	dcResized.SetBrushOrg(0, 0);
	dcResized.StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmpWidth, bmpHeight, SRCCOPY);

	staticControl.SetBitmap((HBITMAP)bmpResized.Detach());
}

void CTrucoPaulistaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CTrucoPaulistaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrucoPaulistaDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTrucoPaulistaDlg::CreateNewInstance()
{
	HWND hwndExistingInstance = ::FindWindow(NULL, m_Instance == 1 ? _T("Truco Paulista - HUMANO 2") : _T("Truco Paulista - HUMANO 1"));
	if (hwndExistingInstance == NULL)
	{
		TCHAR szExePath[MAX_PATH];
		if (GetModuleFileName(NULL, szExePath, MAX_PATH) != 0)
		{
			if (ShellExecute(NULL, _T("open"), szExePath, NULL, NULL, SW_SHOWNORMAL) <= (HINSTANCE)32)
			{
				AfxMessageBox(_T("Falha ao abrir a segunda instância do aplicativo."));
			}
		}
	}
}

TipoDePartida CTrucoPaulistaDlg::ObtemTipoDePartida()
{
	CButton* pRadioButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_RB2PLAYERS));
	if (pRadioButton && pRadioButton->GetCheck() == 1)
	{
		return TipoDePartida::DoisJogadores;
	}
	else
	{
		CButton* pRBNovaInstancia = reinterpret_cast<CButton*>(GetDlgItem(IDC_RB4PLAYERS_REMOTE));
		if (pRBNovaInstancia && pRBNovaInstancia->GetCheck() == 1)
		{
			return TipoDePartida::QuatroJogadores_umremoto;
		}
	}

	return TipoDePartida::QuatroJogadores;
}
