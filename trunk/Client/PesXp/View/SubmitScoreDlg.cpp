// SubmitScoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PesXp.h"
#include "SubmitScoreDlg.h"


// CSubmitScoreDlg dialog

IMPLEMENT_DYNAMIC(CSubmitScoreDlg, CDialog)

CSubmitScoreDlg::CSubmitScoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubmitScoreDlg::IDD, pParent)
{

}

CSubmitScoreDlg::~CSubmitScoreDlg()
{
}

void CSubmitScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubmitScoreDlg, CDialog)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSubmitScoreDlg message handlers

HBRUSH CSubmitScoreDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    if (GetDlgItem(IDC_SUBMIT_TEXT_TIP_INFO)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(255, 0, 0));
    }
    else if (GetDlgItem(IDC_SUBMIT_TEXT_OWNER_TEAM)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0, 255));
    }
    // TODO:  Return a different brush if the default is not desired
    return hbr;
}
