#include "pch.h"
#include "CStaticSub.h"
#include "Mandelbrot Experiment.h"
#include "Mandelbrot ExperimentDlg.h"


BEGIN_MESSAGE_MAP(CStaticSub, CStatic)
	ON_WM_MOUSEMOVE()
    ON_WM_MBUTTONDBLCLK()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CStaticSub::OnMouseMove(UINT nFlags, CPoint point)
{

    ScreenToClient(&point);
    CString strx;
    CString stry;
    strx.Format(_T("%d"), point.x);
    stry.Format(_T("%d"), point.y);
    this->GetParent()->GetDlgItem(IDC_EDIT20)->SetWindowText(strx);
    this->GetParent()->GetDlgItem(IDC_EDIT21)->SetWindowText(stry);

    CStatic::OnMouseMove(nFlags, point);

}


void CStaticSub::OnMButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    ScreenToClient(&point);
    CString strx;
    CString stry;
    strx.Format(_T("%d"), point.x);
    stry.Format(_T("%d"), point.y);
    this->GetParent()->GetDlgItem(IDC_EDIT16)->SetWindowText(strx);
    this->GetParent()->GetDlgItem(IDC_EDIT17)->SetWindowText(stry);

    CStatic::OnMButtonDblClk(nFlags, point);
}


void CStaticSub::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    ScreenToClient(&point);
    CString strx;
    CString stry;
    strx.Format(_T("%d"), point.x);
    stry.Format(_T("%d"), point.y);
    this->GetParent()->GetDlgItem(IDC_EDIT16)->SetWindowText(strx);
    this->GetParent()->GetDlgItem(IDC_EDIT17)->SetWindowText(stry);
    CStatic::OnLButtonDblClk(nFlags, point);
}
