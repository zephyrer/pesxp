// View\LeagueMarketPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "LeagueMarketPage.h"
#include "PlayerLibDlg.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CLeagueMarketPage 对话框

IMPLEMENT_DYNAMIC(CLeagueMarketPage, CPropertyPage)

CLeagueMarketPage::CLeagueMarketPage()
    : CPropertyPage(CLeagueMarketPage::IDD)
{
    m_bInitData = false;
}

CLeagueMarketPage::~CLeagueMarketPage()
{
}

void CLeagueMarketPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_MARKET, m_listCtrl);
    DDX_Control(pDX, IDC_LIST_MY_MARKET, m_listCtrlMyTeam);
}


BEGIN_MESSAGE_MAP(CLeagueMarketPage, CPropertyPage)
    ON_BN_CLICKED(IDC_MARKET_BUTTON, &CLeagueMarketPage::OnBnClickedMarketButton)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CLeagueMarketPage 消息处理程序

BOOL CLeagueMarketPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // 初始化转会市场列表
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

    m_listCtrl.InsertColumn( 0, _T("日期"), LVCFMT_LEFT, 55);//插入列
    m_listCtrl.InsertColumn( 1, _T("球员"), LVCFMT_LEFT, 65);
    m_listCtrl.InsertColumn( 2, _T("身价"), LVCFMT_LEFT, 50);
    m_listCtrl.InsertColumn( 3, _T("等级"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 5, _T("转入"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 6, _T("转出"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 7, _T("进程"), LVCFMT_LEFT, 50);

    //
    // 我的转会动态
    //
    lStyle = GetWindowLong(m_listCtrlMyTeam.m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT; //设置style
    SetWindowLong(m_listCtrlMyTeam.m_hWnd, GWL_STYLE, lStyle);//设置style

    dwStyles = m_listCtrlMyTeam.GetExtendedStyle();
    dwStyles |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyles |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    m_listCtrlMyTeam.SetExtendedStyle(dwStyles); //设置扩展风格

    m_listCtrlMyTeam.InsertColumn( 0, _T("日期"), LVCFMT_LEFT, 55);//插入列
    m_listCtrlMyTeam.InsertColumn( 1, _T("球员"), LVCFMT_LEFT, 65);
    m_listCtrlMyTeam.InsertColumn( 2, _T("身价"), LVCFMT_LEFT, 55);
    m_listCtrlMyTeam.InsertColumn( 3, _T("等级"), LVCFMT_LEFT, 55);
    m_listCtrlMyTeam.InsertColumn( 7, _T("进程"), LVCFMT_LEFT, 50);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CLeagueMarketPage::OnBnClickedMarketButton()
{
    CPlayerLibDlg* pPlayerLibDlg = new CPlayerLibDlg();
    pPlayerLibDlg->DoModal();
}

void CLeagueMarketPage::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    
    if (!m_bInitData)
    {
        CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg((CDialog*)(CPropertySheet*)this->GetParent(), _T("获取转会市场信息"), CSyncHandler::RequestMarketInfo , this);
        m_bInitData = true;
    }
    // 不为绘图消息调用 CPropertyPage::OnPaint()
}
