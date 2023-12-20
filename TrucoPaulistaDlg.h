
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
	void SetBitmapMesa();

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
	CStatic m_Pic1;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedAbout();
	CStatic m_Pic2;
	CStatic m_Pic3;
	afx_msg void OnStnClickedPic3();
	CStatic m_PicMesa;
};
