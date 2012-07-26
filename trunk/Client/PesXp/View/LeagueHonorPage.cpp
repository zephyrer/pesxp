// View\LeagueHonorPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "LeagueHonorPage.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CLeagueHonorPage 对话框

IMPLEMENT_DYNAMIC(CLeagueHonorPage, CPropertyPage)

CLeagueHonorPage::CLeagueHonorPage()
    : CPropertyPage(CLeagueHonorPage::IDD)
{
    m_bInitData = false;
}

CLeagueHonorPage::~CLeagueHonorPage()
{
}

void CLeagueHonorPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_HONOR, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CLeagueHonorPage, CPropertyPage)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CLeagueHonorPage 消息处理程序

BOOL CLeagueHonorPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    //
    // 初始化荣耀殿堂列表
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

    m_listCtrl.InsertColumn( 0, _T("赛事"), LVCFMT_LEFT, 80);//插入列
    m_listCtrl.InsertColumn( 1, _T("球队数"), LVCFMT_LEFT, 55);
    m_listCtrl.InsertColumn( 2, _T("冠军"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 3, _T("亚军"), LVCFMT_LEFT, 60);
    m_listCtrl.InsertColumn( 5, _T("金靴奖"), LVCFMT_LEFT, 70);
    m_listCtrl.InsertColumn( 6, _T("助攻王"), LVCFMT_LEFT, 70);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CLeagueHonorPage::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (!m_bInitData)
    {
        CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg((CDialog*)(CPropertySheet*)this->GetParent(), _T("获取荣耀大殿信息"), CSyncHandler::RequestHonorInfo , this);
        m_bInitData = true;
    }
    // 不为绘图消息调用 CPropertyPage::OnPaint()
}
