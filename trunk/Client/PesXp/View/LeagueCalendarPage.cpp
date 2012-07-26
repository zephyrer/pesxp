// View\LeagueCalendarPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueCalendarPage.h"


// CLeagueCalendarPage 对话框

IMPLEMENT_DYNAMIC(CLeagueCalendarPage, CPropertyPage)

CLeagueCalendarPage::CLeagueCalendarPage()
	: CPropertyPage(CLeagueCalendarPage::IDD)
{

}

CLeagueCalendarPage::~CLeagueCalendarPage()
{
}

void CLeagueCalendarPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CALENDAR, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueCalendarPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueCalendarPage 消息处理程序

BOOL CLeagueCalendarPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // 初始化赛程列表
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

    m_listCtrl.InsertColumn( 0, _T("场次"), LVCFMT_LEFT, 60);//插入列
    m_listCtrl.InsertColumn( 1, _T("日期"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 2, _T("主队"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 3, _T("客队"), LVCFMT_LEFT, 75);
    m_listCtrl.InsertColumn( 4, _T("状态"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 5, _T("比分"), LVCFMT_LEFT, 60);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
