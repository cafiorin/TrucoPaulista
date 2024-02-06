
// TrucoPaulistaDlg.h : header file
//

#pragma once

class Partida;
class Jogador;
class Carta;
class PartidaMessagesController;
class PersistenciaController;
class JogadorView;
class MesaView;
class DadosInstanciaCliente;
class PlacarView;


#include "IEventosDaPartida.h"  
#include "CartaCoberta.h"
#include "Enums.h"

// CTrucoPaulistaDlg dialog
class CTrucoPaulistaDlg : public CDialogEx, public IEventosDaPartida
{
	// Construction
public:
	CTrucoPaulistaDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CTrucoPaulistaDlg();
	void SetBitmapOnStaticControl(CStatic& staticControl, CBitmap& bitmap);
	void InitFontToText(int idText);
	TipoDePartida ObtemTipoDePartida();
	JogadorView* GetJogadorViewByID(int numeroJogador);
	void AddOutput(const CString& novaLinha);
	void AtualizaTento();
	void JogadorCobriuACarta(int idControl);
	void AtualizaDeQuemEhAVezDeJogar(Jogador* jogador);
	void ShowQuemGanhouARodada(int jogador);

	void InicializaTelaInicial();
	void InicializaPartida();
	void InicializarPartidaCliente();
	BOOL VerifyInstances();
	void CreateNewInstance();
	HANDLE m_hMutex; // Identificador do mutex
	int m_Instance;
	Partida* partida;
	PartidaMessagesController* partidaMessagesController;
	CartaCoberta* cartaCoberta;
	bool DoisJogadores;
	Jogador* JogadorSolicitado;
	bool TwoInstances;
	bool PartidaInicializada;
	CFont m_Font;
	JogadorView* m_JogadorHumano1View;
	JogadorView* m_JogadorHumano2View;
	JogadorView* m_JogadorBot1View;
	JogadorView* m_JogadorBot2View;
	MesaView* m_MesaView;
	PlacarView* m_PlacarView;
	DadosInstanciaCliente* m_Cliente;

	void InicializaRodada();
	void RecomecarRodada();
	void AtualizaPlacar();
	void AtualizaPlacarDePartidas();
	void JogadorClicouNaCarta(Jogador* jogador, int posicaoDaCarta);
	void JogadorParceiroClicouNaCarta(Jogador* jogador, int posicaoDaCarta);
	void JogarCartasNaMesa();
	void AtualizarCartaJogadaNaMesa(JogadorView* jogador, std::vector<std::tuple<Carta*, bool>> cartas);
	void JogarCartasHistorico(int idJogador, const Carta* cartaJogada, int numeroDaRodad);

	void MouseLeftClick(int idControl);
	int ObtemNumeroDaRodada();

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void onInicioDaPartida();
	virtual void onFimDaPartida(Jogador* ganhou);

	virtual void onInicioDaRodada(int numeroRodada);
	virtual void onFimDaRodada(int numeroRodada, Jogador* JogadorQueGanhou);
	virtual void solicitaJogadorJogar(Jogador* jogador);
	virtual void onBotJogouACarta(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada, bool cartaCoberta);
	virtual void onAcabouARodada(Jogador* JogadorQueGanhou);
	virtual void onPedeTruco(Jogador* jogador);
	virtual void onAceitouTruco(Jogador* jogador);
	virtual void onCartaJogada(int NumeroDaRodada, Jogador* jogadorAjogar, const Carta* cartaJogada, bool cartaCoberta);

	//Cliente
	void AtualizaCartasCliente(int c1, int c2, int c3, int c4);
	void AtualizaClientePodeTrucar(bool trucar);
	void SolicitaAcaoJogadorCliente();
	void AtualizaPlacarCliente(int PontosDaDupla1, int PontosDaDupla2);
	void JogouACartaCliente(int numeroCarta, bool _cartaCoberta);
	void AtualizaCartasJogadasCliente(int numeroDaRodada, int numeroJogador, int carta);
	void AtualizaTentoCliente(int tento);
	void SetCurrectBitmapCliente(int rodada, int numeroJogador, int carta);
	void ShowMessageJogadorAceitouTruco(int jogadorqueTrucou);
	void ShowMessageQuemGanhouaRodada(int rodada, int jogadorGanhouRodada);
	void ShowMessageQuemGanhoaPartida(int jogadorGanhouPartida);
	void InicializaRodadaCliente(int jogadorQueComeca);
	void Jogador2Correu(int jogadorCorreu);
	void Jogador2Trucou(int jogadorCorreu);

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
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedSync();
	afx_msg void OnBnClickedSalvar();
	afx_msg void OnBnClickedRecarregar();
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
	afx_msg void OnBnClickedStart();
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
	afx_msg void OnBnClickedRb4playersRemote();
	afx_msg void OnBnClickedRb4players();
	afx_msg void OnBnClickedRb2players();
};
