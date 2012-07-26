// View\LeagueMyTeamPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueMyTeamPage.h"


// CLeagueMyTeamPage �Ի���

IMPLEMENT_DYNAMIC(CLeagueMyTeamPage, CPropertyPage)

CLeagueMyTeamPage::CLeagueMyTeamPage()
	: CPropertyPage(CLeagueMyTeamPage::IDD)
{

}

CLeagueMyTeamPage::~CLeagueMyTeamPage()
{
}

void CLeagueMyTeamPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_MY_TEAM, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueMyTeamPage, CPropertyPage)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CLeagueMyTeamPage ��Ϣ�������

BOOL CLeagueMyTeamPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // ��ʼ�������Ա�б�
    //
    LONG lStyle;
    lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
    lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
    lStyle |= LVS_REPORT; //����style
    SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

    DWORD dwStyles = m_listCtrl.GetExtendedStyle();
    dwStyles |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyles |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    m_listCtrl.SetExtendedStyle(dwStyles); //������չ���

    m_listCtrl.InsertColumn( 0, _T("����"), LVCFMT_LEFT, 95);//������
    m_listCtrl.InsertColumn( 1, _T("���"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 2, _T("λ��"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 3, _T("����"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 4, _T("����"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 5, _T("����"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 6, _T("����"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 7, _T("����"), LVCFMT_LEFT, 40);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH CLeagueMyTeamPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

    if (GetDlgItem(IDC_MY_TEAM_LOSE_COUNT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_ASSITANT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_GOAL_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_MONEY_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_RANK_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_RED_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_YELLOW_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_WIN_PERCENT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_WIN_COUNT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_TIE_COUNT_TEXT)->m_hWnd == pWnd->m_hWnd || \
        GetDlgItem(IDC_MY_TEAM_NAME_TEXT)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0,240));
    }

    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
    return hbr;
}
