// View\LeagueTeamRankPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueTeamRankPage.h"


// CLeagueTeamRankPage 对话框

IMPLEMENT_DYNAMIC(CLeagueTeamRankPage, CPropertyPage)

CLeagueTeamRankPage::CLeagueTeamRankPage()
	: CPropertyPage(CLeagueTeamRankPage::IDD)
{

}

CLeagueTeamRankPage::~CLeagueTeamRankPage()
{
}

void CLeagueTeamRankPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_TEAM_RANK, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueTeamRankPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueTeamRankPage 消息处理程序

BOOL CLeagueTeamRankPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // 初始化球队排名列表
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

    m_listCtrl.InsertColumn( 0, _T("排名"), LVCFMT_LEFT, 40);//插入列
    m_listCtrl.InsertColumn( 1, _T("球队"), LVCFMT_LEFT, 65);
    m_listCtrl.InsertColumn( 2, _T("进球"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 3, _T("失球"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 4, _T("净胜球"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 5, _T("胜率"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 6, _T("红牌"), LVCFMT_LEFT, 40);
    m_listCtrl.InsertColumn( 7, _T("黄牌"), LVCFMT_LEFT, 40);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
