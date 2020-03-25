
// Mandelbrot ExperimentDlg.h : header file
//
#include <string>
#include "CStaticSub.h"


#pragma once

namespace brightland{
// CMandelbrotExperimentDlg dialog
class CMandelbrotExperimentDlg : public CDialogEx
{
// Construction
public:
	CMandelbrotExperimentDlg(CWnd* pParent = nullptr);	// standard constructor
	CStaticSub m_pic;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANDELBROTEXPERIMENT_DIALOG };
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
	afx_msg void OnBnClickedBtnCompile();
	afx_msg void OnBnClickedBtnTest();
	int finishUp();
	bool isNumber(std::string s);
	void OnTimer(UINT_PTR nIDEvent); //Thread Manager.
	void messenger(std::string s);
	static UINT compileMandelbrot(LPVOID pParam);
	void ChangeStaticCtrl(LPCTSTR lpszImagePath, UINT nCtrlID);
	void updateImage(LPCTSTR str);

	void OnLButtonDown(UINT nFlags, CPoint point);
;

	CBitmap bmp;
	CString m_output;
	CString text1;
	CString red_value;
	CString m_red1;
//	CStatic m_Picture;
	CRect m_rectangle;
	
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);


};
}