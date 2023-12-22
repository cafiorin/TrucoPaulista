// TrucoPaulistaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TrucoPaulista.h"
#include "TrucoPaulistaDlg.h"
#include "afxdialogex.h"
#include "CartasBitmap.h"
#include "Baralho.h"
#include "Jogador.h"
#include "Partida.h"
#include "resource.h"

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
}

BEGIN_MESSAGE_MAP(CTrucoPaulistaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDM_ABOUTBOX, &CTrucoPaulistaDlg::OnBnClickedAbout)
	ON_BN_CLICKED(ID_SYNC, &CTrucoPaulistaDlg::OnBnClickedSync)
END_MESSAGE_MAP()


// CTrucoPaulistaDlg message handlers

BOOL CTrucoPaulistaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!VerifyInstances())
		return FALSE;

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	Baralho baralho;

	CartasBitmap cartaBitmap1(baralho.PegarCartaDoTopo());
	CartasBitmap cartaBitmap2(baralho.PegarCartaDoTopo());
	CartasBitmap cartaBitmap3(baralho.PegarCartaDoTopo());
	CartasBitmap cartaBitmap4(baralho.PegarCartaDoTopo());

	/*Partida partida;
	partida.InicializarPartida();

	Jogador* jogadorHumano1 = partida.ObtemJogadorHumano1();

	CartasBitmap cartaBitmap1(*jogadorHumano1->PrimeiraCartaNaMao());
	CartasBitmap cartaBitmap2(*jogadorHumano1->SegundaCartaNaMao());
	CartasBitmap cartaBitmap3(*jogadorHumano1->TerceiraCartaNaMao());
	Carta *Vira = new Carta(partida.ObtemVira());
	CartasBitmap cartaBitmap4(*Vira);*/

	SetBitmapOnStaticControl(m_Pic1, *cartaBitmap1.Getbitmap());
	SetBitmapOnStaticControl(m_Pic2, *cartaBitmap2.Getbitmap());
	SetBitmapOnStaticControl(m_Pic3, *cartaBitmap3.Getbitmap());

	SetBitmapMesa();

	SetBitmapCartasAvesso();

	SetBitmapOnStaticControl(m_PicVira, *cartaBitmap4.Getbitmap());

	return TRUE;  // return TRUE  unless you set the focus to a control
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
			//AfxMessageBox(_T("Apenas duas instâncias do aplicativo são permitidas."));
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
