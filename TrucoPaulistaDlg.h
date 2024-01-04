
// TrucoPaulistaDlg.h : header file
//

#pragma once


// CTrucoPaulistaDlg dialog
class CTrucoPaulistaDlg : public CDialogEx
{
// Construction
public:
	CTrucoPaulistaDlg(CWnd* pParent = nullptr);	// standard constructor
	void SetBitmapOnStaticControl(CStatic& staticControl, CBitmap& bitmap);
	void SetBitmapCartasAvesso();
	void SetBitmapMesa();
	BOOL VerifyInstances();
	void CreateNewInstance();
	HANDLE m_hMutex; // Identificador do mutex
	int m_Instance;

	virtual BOOL PreTranslateMessage(MSG* pMsg);

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
};
