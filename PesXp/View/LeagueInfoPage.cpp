// View\LeagueInfoPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "LeagueInfoPage.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CLeagueInfoPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueInfoPage, CPropertyPage)

CLeagueInfoPage::CLeagueInfoPage()
    : CPropertyPage(CLeagueInfoPage::IDD)
{
    m_bShowJoinButton   = false;
    m_bInitData         = false;
}

CLeagueInfoPage::~CLeagueInfoPage()
{
}

void CLeagueInfoPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}

//
// �����Ƿ��Ѿ���������
//
void CLeagueInfoPage::ShowJoinButton(bool show)
{
    m_bShowJoinButton = show;
}

BEGIN_MESSAGE_MAP(CLeagueInfoPage, CPropertyPage)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BUTTON_LEAGUE_UPDATE, OnButtonUpdate)
END_MESSAGE_MAP()


// CLeagueInfoPage ��Ϣ�������

BOOL CLeagueInfoPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    CWnd *pWnd = GetDlgItem(IDC_JOIN_LEAGUE);
    if (m_bShowJoinButton) {
        pWnd->ShowWindow(SW_SHOWNORMAL);
    }
    else {
        pWnd->ShowWindow(SW_HIDE);
    }

    m_bShowJoinButton = false;

    //
    // ȥ��ȷ����ȡ����ť
    //
    CPropertySheet *pPropertySheet = (CPropertySheet *)GetParent();
    pWnd = pPropertySheet->GetDlgItem(IDCANCEL);
    pWnd->SetWindowText(_T("�ر�"));
    pWnd = pPropertySheet->GetDlgItem(IDOK);
    pWnd->ShowWindow(SW_HIDE);

    //
    // ���Ӹ��°�ť
    //
    CRect rect;
    pWnd->GetWindowRect(rect);
    ScreenToClient(rect);
    m_btnUpdate.Create(
        _T("����"), 
        BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP,
        rect, 
        pPropertySheet, 
        IDC_BUTTON_LEAGUE_UPDATE);
    m_btnUpdate.SetFont(GetFont());
    m_btnUpdate.ShowWindow(SW_SHOW);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CLeagueInfoPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    if (GetDlgItem(IDC_LEAGUE_INFO_PROGRESS_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_START_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_STOP_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_POST_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_TEAM_COUNT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_MATCH_COUNT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_GOAL_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_ASSITANT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_FIRST_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_LAST_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_RED_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_LEAGUE_INFO_YELLOW_TEXT)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0,240));
    }

    return hbr;
}

void CLeagueInfoPage::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (!m_bInitData)
    {
        CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg((CDialog*)(CPropertySheet*)this->GetParent(), _T("��ȡ��������"), CSyncHandler::RequestLeagueDetail , this);
        m_bInitData = true;
    }

    // ��Ϊ��ͼ��Ϣ���� CPropertyPage::OnPaint()
}

void CLeagueInfoPage::OnButtonUpdate()
{
    m_bInitData = false;
    SendMessage(WM_PAINT);
}