// View\LeagueMyTeamPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueMyTeamPage.h"


// CLeagueMyTeamPage 对话框

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


// CLeagueMyTeamPage 消息处理程序

BOOL CLeagueMyTeamPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // 初始化球队球员列表
    //
    LONG lStyle;
    lStyle = GetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT; //设置style
    SetWindowLong(m_listCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style

    DWORD dwStyles = m_listCtrl.GetExtendedStyle();
    dwStyles |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyles |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_listCtrl.SetExtendedStyle(dwStyles); //设置扩展风格

    m_listCtrl.InsertColumn( 0, _T("姓名"), LVCFMT_LEFT, 95);//插入列
    m_listCtrl.InsertColumn( 1, _T("身价"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 2, _T("位置"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 3, _T("能力"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 4, _T("进球"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 5, _T("助攻"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 6, _T("红牌"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 7, _T("黄牌"), LVCFMT_LEFT, 40);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
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

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}
