
// TrucoPaulistaDlg.h : header file
//

#pragma once

class Partida;
class Jogador;
class Carta;
class PartidaMessagesController;

#include "IEventosDaPartida.h"  

// CTrucoPaulistaDlg dialog
class CTrucoPaulistaDlg : public CDialogEx, public IEventosDaPartida
{
// Construction
public:
	CTrucoPaulistaDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CTrucoPaulistaDlg();
	void SetBitmapOnStaticControl(CStatic& staticControl, CBitmap& bitmap);
	void SetBitmapCartasAvesso();
	
	void CleanOutput();
	void AddOutput(const CString& novaLinha);

	void SetBitmapMesa();
	void InicializaTelaInicial();
	void InicializaPartida();
	void InicializarPartidaCliente();
	BOOL VerifyInstances();
	void CreateNewInstance();
	HANDLE m_hMutex; // Identificador do mutex
	int m_Instance;
	Partida* partida;
	PartidaMessagesController* partidaMessagesController;
	bool DoisJogadores;
	Jogador* JogadorSolicitado;
	bool TwoInstances;

	void InicializaRodada();
	void CleanCheckBox();
	void AtualizaPlacar();
	void AtualizaPlacarDePartidas();

	void SetCurrectBitmapFromBot(Jogador* bot, const Carta* carta);
	void SetCurrectBitmapFromHumano(Jogador* bot, const Carta* carta);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void onInicioDaPartida();
	virtual void onFimDaPartida(Jogador* ganhou);

	virtual void onInicioDaRodada(int numeroRodada);
	virtual void onFimDaRodada(int numeroRodada, Jogador* JogadorQueGanhou);
	virtual void solicitaJogadorJogar(Jogador* jogador);
	virtual void onBotJogouACarta(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada);
	virtual void onAcabouARodada(Jogador* JogadorQueGanhou);
	virtual void onPedeTruco();
	virtual void onAceitouTruco(Jogador* jogador);
	virtual void onCartaJogada(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada);

	//Cliente
	void AtualizaPlacar(int PontosDaDupla1, int PontosDaDupla2);
	void AtualizaCartasCliente(int c1,int c2, int c3, int c4);
	void AtualizaClientePodeTrucar(bool trucar);
	void SolicitaAcaoJogadorCliente();
	void JogouACartaCliente(int numeroCarta);
	void AtualizaCartasJogadasCliente(int numeroDaRodada, int numeroJogador, int carta);
	void SetCurrectBitmapCliente(int rodada, int numeroJogador, int carta);
	void CTrucoPaulistaDlg::ShowMessageJogadorAceitouTruco(int jogadorqueTrucou);
	void CTrucoPaulistaDlg::ShowMessageQuemGanhouaRodada(int rodada, int jogadorGanhouRodada);
	void CTrucoPaulistaDlg::ShowMessageQuemGanhoaPartida(int jogadorGanhouPartida);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRUCOPAULISTA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedSync();
	void GetBotAction();
	CStatic m_Pic1;
	CStatic m_Pic2;
	CStatic m_Pic3;
	CStatic m_PicMesa;
	CStatic m_PicCartaOp1;
	CStatic m_PicCartaOp2;
	CStatic m_PicCartaOp3;
	CStatic m_PicCartaOp21;
	CStatic m_PicCartaOp22;
	CStatic m_PicCartaOp23;
	CStatic m_PicCartaParc1;
	CStatic m_PicCartaParc2;
	CStatic m_PicCartaParc3;
	CStatic m_PicBaralho;
	CStatic m_PicVira;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedPic3();
	afx_msg void OnStnClickedPic2();
	afx_msg void OnStnClickedPic1();
	CStatic m_CartaH1_R1;
	CStatic m_CartaH2_R1;
	CStatic m_CartaH1_R2;
	CStatic m_CartaH2_R2;
	CStatic m_CartaH1_R3;
	CStatic m_CartaH2_R3;
	CStatic m_CartaBOT1_R1;
	CStatic m_CartaBOT1_R2;
	CStatic m_CartaBOT1_R3;
	CStatic m_CartaBOT2_R1;
	CStatic m_CartaBOT2_R2;
	CStatic m_CartaBOT2_R3;
	afx_msg void OnBnClickedTrucar();
	afx_msg void OnBnClickedCorrer();
	afx_msg void OnStnClickedPicParc3();
	afx_msg void OnStnClickedPicParc2();
	afx_msg void OnStnClickedPicParc1();
	afx_msg void OnBnClickedTrucar2();
	afx_msg void OnBnClickedCorrer2();
};
