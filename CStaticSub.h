#pragma once
#include <afxdialogex.h>


class CStaticSub :
	public CStatic
{
public:
	CStatic m_pic;


	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

