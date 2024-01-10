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

#include <atlimage.h>
#include <windows.h>

#define WM_CUSTOM_MESSAGE (WM_USER + 1)

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrucoPaulistaDlg dialog
CTrucoPaulistaDlg::CTrucoPaulistaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRUCOPAULISTA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CTrucoPaulistaDlg::PreTranslateMessage(MSG* pMsg)
{
	// Verificar se é a mensagem personalizada
	if (pMsg->message == WM_CUSTOM_MESSAGE)
	{
		// Faça algo em resposta à mensagem personalizada
		// Por exemplo, exiba uma mensagem
		AfxMessageBox(_T("Mensagem Personalizada Recebida"));

		// Retorne TRUE para indicar que a mensagem foi processada
		return TRUE;
	}

	// Chame a implementação padrão para outras mensagens
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
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDM_ABOUTBOX, &CTrucoPaulistaDlg::OnBnClickedAbout)
	ON_BN_CLICKED(ID_SYNC, &CTrucoPaulistaDlg::OnBnClickedSync)
	ON_BN_CLICKED(IDC_BUTTON1, &CTrucoPaulistaDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_PIC3, &CTrucoPaulistaDlg::OnStnClickedPic3)
	ON_STN_CLICKED(IDC_PIC2, &CTrucoPaulistaDlg::OnStnClickedPic2)
	ON_STN_CLICKED(IDC_PIC1, &CTrucoPaulistaDlg::OnStnClickedPic1)
	ON_BN_CLICKED(IDC_TRUCAR, &CTrucoPaulistaDlg::OnBnClickedTrucar)
	ON_BN_CLICKED(IDC_CORRER, &CTrucoPaulistaDlg::OnBnClickedCorrer)
END_MESSAGE_MAP()


// CTrucoPaulistaDlg message handlers
BOOL CTrucoPaulistaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!VerifyInstances())
		return FALSE;

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//obs: não consegui debugar o conteudo da segunda instancia, caso você tem algum problema recomendo comentar a linha a baixo.
	//CreateNewInstance();

	InicializaTelaInicial();//Espera evento de iniciar a partida
	partida = new Partida(this);

	if (m_Instance == 1)
	{
	}
	else
	{
		partida->InicializarPartidaCliente(); //So inicializa o placar e a tela, precisa receber as cartas do Servidor (o metodo InicializarPartida deve enviar as cartas)
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrucoPaulistaDlg::InicializaTelaInicial()
{
	SetBitmapMesa();

	CBitmap bitmapVerso;
	bitmapVerso.LoadBitmap(IDB_BITMAP_VERSO);
	SetBitmapOnStaticControl(m_PicBaralho, bitmapVerso);

	m_Pic1.ShowWindow(SW_HIDE);
	m_Pic2.ShowWindow(SW_HIDE);
	m_Pic3.ShowWindow(SW_HIDE);
	m_PicCartaOp1.ShowWindow(SW_HIDE);
	m_PicCartaOp2.ShowWindow(SW_HIDE);
	m_PicCartaOp3.ShowWindow(SW_HIDE);
	m_PicCartaOp21.ShowWindow(SW_HIDE);
	m_PicCartaOp22.ShowWindow(SW_HIDE);
	m_PicCartaOp23.ShowWindow(SW_HIDE);
	m_PicCartaParc1.ShowWindow(SW_HIDE);
	m_PicCartaParc2.ShowWindow(SW_HIDE);
	m_PicCartaParc3.ShowWindow(SW_HIDE);
	m_PicVira.ShowWindow(SW_HIDE);
	
	GetDlgItem(IDC_TRUCAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CORRER)->ShowWindow(SW_HIDE);
	
	CButton* pRadioButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_RADIO7));
	if (pRadioButton)
	{
		pRadioButton->SetCheck(BST_CHECKED);
	}
}

void CTrucoPaulistaDlg::InicializaPartida()
{
	bool doisJogadores = false;
	CButton* pRadioButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_RADIO7));
	if (pRadioButton)
	{
		doisJogadores = pRadioButton->GetCheck() == 1;
	}

	DoisJogadores = doisJogadores;

	partida->InicializarPartida(doisJogadores ? 2 : 4);
	InicializaRodada();
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


void CTrucoPaulistaDlg::SetBitmapMesa()
{
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_MESA);

	SetBitmapOnStaticControl(m_PicMesa, bitmap);
}

void CTrucoPaulistaDlg::SetBitmapCartasAvesso()
{
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_VERSO_90);

	SetBitmapOnStaticControl(m_PicCartaOp1, bitmap);
	SetBitmapOnStaticControl(m_PicCartaOp2, bitmap);
	SetBitmapOnStaticControl(m_PicCartaOp3, bitmap);

	SetBitmapOnStaticControl(m_PicCartaOp21, bitmap);
	SetBitmapOnStaticControl(m_PicCartaOp22, bitmap);
	SetBitmapOnStaticControl(m_PicCartaOp23, bitmap);

	CBitmap bitmapVerso;
	bitmapVerso.LoadBitmap(IDB_BITMAP_VERSO);

	SetBitmapOnStaticControl(m_PicCartaParc1, bitmapVerso);
	SetBitmapOnStaticControl(m_PicCartaParc2, bitmapVerso);
	SetBitmapOnStaticControl(m_PicCartaParc3, bitmapVerso);

	SetBitmapOnStaticControl(m_PicBaralho, bitmapVerso);
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
	// TODO: Add your control notification handler code here
	InicializaPartida();
}

void CTrucoPaulistaDlg::SetCurrectBitmapFromBot(Jogador* bot, const Carta* carta)
{

	CartasBitmap bitmap(*carta);
	switch (partida->ObtemNumeroDaRodada())
	{
	case 1:
		SetBitmapOnStaticControl(m_CartaBOT1_R1, *bitmap.Getbitmap());
		m_CartaBOT1_R1.ShowWindow(SW_SHOW);
		m_PicCartaParc1.ShowWindow(SW_HIDE);
		break;
	case 2:
		SetBitmapOnStaticControl(m_CartaBOT1_R2, *bitmap.Getbitmap());
		m_CartaBOT1_R2.ShowWindow(SW_SHOW);
		m_PicCartaParc2.ShowWindow(SW_HIDE);
		break;
	case 3:
		SetBitmapOnStaticControl(m_CartaBOT1_R3, *bitmap.Getbitmap());
		m_CartaBOT1_R3.ShowWindow(SW_SHOW);
		m_PicCartaParc3.ShowWindow(SW_HIDE);
		break;
	}
}

void CTrucoPaulistaDlg::SetCurrectBitmapFromHumano(Jogador* bot, const Carta* carta)
{
	// exemplo adicionar a class bot aqui para ele jogar a carta correta.

	CartasBitmap bitmap(*carta);
	switch (partida->ObtemNumeroDaRodada())
	{
	case 1:
		SetBitmapOnStaticControl(m_CartaH2_R1, *bitmap.Getbitmap());
		m_CartaH2_R1.ShowWindow(SW_SHOW);
		break;
	case 2:
		SetBitmapOnStaticControl(m_CartaH2_R2, *bitmap.Getbitmap());
		m_CartaH2_R2.ShowWindow(SW_SHOW);
		break;
	case 3:
		SetBitmapOnStaticControl(m_CartaH2_R3, *bitmap.Getbitmap());
		m_CartaH2_R3.ShowWindow(SW_SHOW);
		break;
	}
}

void CTrucoPaulistaDlg::OnStnClickedPic3()
{
	// Joga a Carta1
	if (m_Instance == 1 || partida->ObtemNumeroDeJogadores() == 2)
	{
		Jogador* jogador = partida->ObtemJogadorHumano1();
		const Carta* carta = jogador->TerceiraCartaNaMao();

		SetCurrectBitmapFromHumano(jogador, carta);
		m_Pic3.ShowWindow(SW_HIDE);
		partida->JogadorJogouACarta(jogador, carta);
	}
}


void CTrucoPaulistaDlg::OnStnClickedPic2()
{
	// Joga a carta 2
	if (m_Instance == 1 || partida->ObtemNumeroDeJogadores() == 2)
	{
		Jogador* jogador = partida->ObtemJogadorHumano1();
		const Carta* carta = jogador->SegundaCartaNaMao();

		SetCurrectBitmapFromHumano(jogador, carta);
		m_Pic2.ShowWindow(SW_HIDE);
		partida->JogadorJogouACarta(jogador, carta);
	}
}


void CTrucoPaulistaDlg::OnStnClickedPic1()
{
	//Joga a carta 3
	if (m_Instance == 1 || partida->ObtemNumeroDeJogadores() == 2)
	{
		Jogador* jogador = partida->ObtemJogadorHumano1();
		const Carta* carta = jogador->PrimeiraCartaNaMao();

		SetCurrectBitmapFromHumano(jogador, carta);
		m_Pic1.ShowWindow(SW_HIDE);
		partida->JogadorJogouACarta(jogador, carta);
	}
}


//TODO: 
void CTrucoPaulistaDlg::onInicioDaPartida() {}
void CTrucoPaulistaDlg::onFimDaPartida(Jogador* JogadorQueGanhou)
{
	std::string playerName = JogadorQueGanhou->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("O jogador %s ganhou a partida"), strPlayerName);

	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);

	partida->InicializarPartida(DoisJogadores ? 2 : 4);
	InicializaRodada();

}

void CTrucoPaulistaDlg::onInicioDaRodada(int numeroRodada)
{
	CleanCheckBox();
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

void CTrucoPaulistaDlg::onAceitouTruco(Jogador *jogador)
{
	std::string playerName = jogador->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("Jogador %s aceitou o Truco... Manda !"), strPlayerName);

	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
}


void CTrucoPaulistaDlg::onFimDaRodada(int numeroRodada, Jogador* JogadorQueGanhou)
{
	if (JogadorQueGanhou == nullptr)
	{
		CString str;
		str.Format(_T("Empatou a rodada %d..."), numeroRodada);

		GetDlgItem(IDC_EDIT1)->SetWindowText(str);

		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);

		pCheckBox = (CButton*)GetDlgItem(baseCheckBox+1);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);
	}
	else
	{
		std::string playerName = JogadorQueGanhou->ObtemNome();
		CString strPlayerName(playerName.c_str());

		CString str;
		str.Format(_T("Jogador %s ganhou a rodada %d..."), strPlayerName, numeroRodada);

		GetDlgItem(IDC_EDIT1)->SetWindowText(str);

		int baseCheckBox = IDC_CHECK1 + ((numeroRodada - 1) * 2);
		baseCheckBox = JogadorQueGanhou->EhUmBot() ? baseCheckBox + 1 : baseCheckBox;

		CButton* pCheckBox = (CButton*)GetDlgItem(baseCheckBox);
		if (pCheckBox != nullptr)
			pCheckBox->SetCheck(BST_CHECKED);

	}
}

void CTrucoPaulistaDlg::solicitaJogadorJogar(Jogador* jogador)
{
	std::string playerName = jogador->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("Sua Vez %s..."), strPlayerName);

	GetDlgItem(IDC_EDIT1)->SetWindowText(str);
}

void CTrucoPaulistaDlg::onBotJogouACarta(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada)
{
	SetCurrectBitmapFromBot(jogadorAjogar, cartaJogada);
	Invalidate();
}

void CTrucoPaulistaDlg::onPedeTruco()
{
	Jogador* jogador = partida->ObtemJogadorHumano1();

	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("Truco !!!!"));
	int resultado = AfxMessageBox(_T("Aceita o Truco?"), MB_YESNO | MB_ICONQUESTION);
	GetDlgItem(IDC_TRUCAR)->ShowWindow(SW_SHOW);

	if (resultado == IDYES) 
	{
		partida->JogadorAceitou(jogador);
	}
	else 
	{
		partida->JogadorCorreu(jogador);
	}
}

void CTrucoPaulistaDlg::onAcabouARodada(Jogador* JogadorQueGanhou)
{
	std::string playerName = JogadorQueGanhou->ObtemNome();
	CString strPlayerName(playerName.c_str());

	CString str;
	str.Format(_T("O jogador %s ganhou a rodada"), strPlayerName);

	AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);

	partida->InicializarRodada();
	InicializaRodada();
}

void CTrucoPaulistaDlg::AtualizaPlacar()
{
	CString str;

	str.Format(_T("%d"), partida->PontosDaDupla1());
	GetDlgItem(IDC_PONTOS_DUPLA1)->SetWindowText(str);

	str.Format(_T("%d"), partida->PontosDaDupla2());
	GetDlgItem(IDC_PONTOS_DUPLA2)->SetWindowText(str);

}

void CTrucoPaulistaDlg::InicializaRodada()
{
	AtualizaPlacar();

	GetDlgItem(IDC_RADIO7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T("Sua Vez Humano 1...\n"));

	m_Pic1.ShowWindow(SW_SHOW);
	m_Pic2.ShowWindow(SW_SHOW);
	m_Pic3.ShowWindow(SW_SHOW);
	m_PicCartaParc1.ShowWindow(SW_SHOW);
	m_PicCartaParc2.ShowWindow(SW_SHOW);
	m_PicCartaParc3.ShowWindow(SW_SHOW);

	if (!DoisJogadores)
	{
		m_PicCartaOp1.ShowWindow(SW_SHOW);
		m_PicCartaOp2.ShowWindow(SW_SHOW);
		m_PicCartaOp3.ShowWindow(SW_SHOW);
		m_PicCartaOp21.ShowWindow(SW_SHOW);
		m_PicCartaOp22.ShowWindow(SW_SHOW);
		m_PicCartaOp23.ShowWindow(SW_SHOW);
	}

	m_PicVira.ShowWindow(SW_SHOW);

	Jogador* jogador = partida->ObtemJogadorHumano1();

	CartasBitmap cartaBitmap1(*jogador->PrimeiraCartaNaMao());
	CartasBitmap cartaBitmap2(*jogador->SegundaCartaNaMao());
	CartasBitmap cartaBitmap3(*jogador->TerceiraCartaNaMao());
	Carta Vira(partida->ObtemVira());

	SetBitmapOnStaticControl(m_Pic1, *cartaBitmap1.Getbitmap());
	SetBitmapOnStaticControl(m_Pic2, *cartaBitmap2.Getbitmap());
	SetBitmapOnStaticControl(m_Pic3, *cartaBitmap3.Getbitmap());
	m_Pic1.ModifyStyle(0, SS_NOTIFY);
	m_Pic2.ModifyStyle(0, SS_NOTIFY);
	m_Pic3.ModifyStyle(0, SS_NOTIFY);

	//SetBitmapMesa();

	m_CartaH2_R1.ShowWindow(SW_HIDE);
	m_CartaH2_R2.ShowWindow(SW_HIDE);
	m_CartaH2_R3.ShowWindow(SW_HIDE);

	m_CartaBOT1_R1.ShowWindow(SW_HIDE);
	m_CartaBOT1_R2.ShowWindow(SW_HIDE);
	m_CartaBOT1_R3.ShowWindow(SW_HIDE);

	GetDlgItem(IDC_TRUCAR)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CORRER)->ShowWindow(SW_SHOW);

	SetBitmapCartasAvesso();

	CartasBitmap cartaBitmap4(Vira);
	SetBitmapOnStaticControl(m_PicVira, *cartaBitmap4.Getbitmap());
	Invalidate();
}


void CTrucoPaulistaDlg::OnBnClickedTrucar()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TRUCAR)->ShowWindow(SW_HIDE);

	Jogador* jogador = partida->ObtemJogadorHumano1();
	partida->JogadorTrucou(jogador);

}


void CTrucoPaulistaDlg::OnBnClickedCorrer()
{
	// TODO: Add your control notification handler code here
	Jogador* jogador = partida->ObtemJogadorHumano1();
	partida->JogadorCorreu(jogador);
}


