// .\View\UserCenterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PesXp.h"
#include "UserCenterDlg.h"
#include "WaitingDlg.h"
#include "SyncHandler.h"

// CUserCenterDlg dialog

IMPLEMENT_DYNAMIC(CUserCenterDlg, CDialog)

CUserCenterDlg::CUserCenterDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CUserCenterDlg::IDD, pParent)
{
    m_isDefaultDlg              = true;
    m_isSyncData                = false;
    m_pDlgSubmitScore           = NULL;
    m_pDlgAgreeScore            = NULL;
    m_pDlgLeagueSheet           = NULL;
    m_pDlgLeagueInfoPage        = NULL;
    m_pDlgLeagueCalendarPage    = NULL;
    m_pDlgLeagueGoalPage        = NULL;
    m_pDlgLeagueAssitantPage    = NULL;
    m_pDlgLeagueMyTeamPage      = NULL;
    m_pDlgLeagueTeamRankPage    = NULL;
    m_pDlgLeagueHonorPage       = NULL;
    m_pDlgLeagueMarketPage      = NULL;
    m_pUtilHandler              = CUtilHandler::GetInstance();
}

CUserCenterDlg::~CUserCenterDlg()
{
    m_pUtilHandler->FreeMemory(m_pDlgSubmitScore);
    m_pUtilHandler->FreeMemory(m_pDlgAgreeScore);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueSheet);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueInfoPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueCalendarPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueGoalPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueAssitantPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueMyTeamPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueTeamRankPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueHonorPage);
    m_pUtilHandler->FreeMemory(m_pDlgLeagueMarketPage);
}

void CUserCenterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_UC_TEXT_ACCOUNT, m_strMyAccount);
    DDX_Text(pDX, IDC_UC_TEXT_CREDIE, m_strMyCredie);
    DDX_Text(pDX, IDC_UC_TEXT_WIN, m_strWinCount);
    DDX_Text(pDX, IDC_UC_TEXT_EQUAL, m_strEqualCount);
    DDX_Text(pDX, IDC_UC_TEXT_LOSE, m_strLoseCount);
    DDX_Text(pDX, IDC_UC_TEXT_WIN_PERCENT, m_strWinPercentCount);
    DDX_Text(pDX, IDC_UC_TEXT_RANK, m_strTotalRank);
    DDX_Text(pDX, IDC_UC_TEXT_GOAL_COUNT, m_strGoalCount);
    DDX_Text(pDX, IDC_UC_TEXT_LOSE_COUNT, m_strLostCount);
    DDX_Text(pDX, IDC_UC_TEXT_RED_COUNT, m_strRedCount);
    DDX_Text(pDX, IDC_UC_TEXT_YELLOW_COUNT, m_strYellowCount);
    DDX_Text(pDX, IDC_UC_TEXT_NEED_CONFIRM, m_strNeedConfirmCount);
    DDX_Text(pDX, IDC_UC_TEXT_NOT_CONFIRM, m_strNotConfirmCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_WIN, m_strLeagueWinCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_EQUAL, m_strLeagueEqualCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_LOSE, m_strLeagueLoseCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_WIN_PERCENT, m_strLeagueWinPercentCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_RANK, m_strLeagueRank);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_MONEY, m_strLeagueMoney);
    DDX_Text(pDX, IDC_UC_TEXT_THE_FIRST, m_strLeagueTheFirst);
    DDX_Text(pDX, IDC_UC_TEXT_THE_END, m_strLeagueTheEnd);
    DDX_Text(pDX, IDC_UC_TEXT_PLAYER_COUNT, m_strLeaguePlayerCount);
    DDX_Text(pDX, IDC_UC_TEXT_LEAGUE_INFO, m_strLeagueInfo);
    DDX_Text(pDX, IDC_UC_TEXT_SIGN_COUNT, m_strLeagueSignCount);
    DDX_Control(pDX, IDC_UC_COMBO_JOIN_LEAGUE, m_cmbJoinLeague);
    DDX_Control(pDX, IDC_UC_COMBO_OTHER_LEAGUE, m_cmbOtherLeague);
    DDX_Control(pDX, IDC_UC_COMBO_SIGN_LEAGUE, m_cmbSignLeague);
}


BEGIN_MESSAGE_MAP(CUserCenterDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_LEAGUE_DOING, &CUserCenterDlg::OnBnClickedButtonLeagueDoing)
    ON_WM_SHOWWINDOW()
    ON_WM_CTLCOLOR()
    ON_BN_CLICKED(IDC_BUTTON_GLORY, &CUserCenterDlg::OnBnClickedButtonGlory)
    ON_BN_CLICKED(IDC_BUTTON_CALENDAR, &CUserCenterDlg::OnBnClickedButtonCalendar)
    ON_BN_CLICKED(IDC_BUTTON_SUBMIT_SCORE, &CUserCenterDlg::OnBnClickedButtonSubmitScore)
    ON_BN_CLICKED(IDC_BUTTON_AGREE_SCORE, &CUserCenterDlg::OnBnClickedButtonAgreeScore)
    ON_BN_CLICKED(IDC_BUTTON_ENTER_MY_LEAGUE, &CUserCenterDlg::OnBnClickedButtonEnterMyLeague)
    ON_BN_CLICKED(IDC_BUTTON_WATCH_LEAGUE, &CUserCenterDlg::OnBnClickedButtonWatchLeague)
    ON_BN_CLICKED(IDC_BUTTON_LEAGUE_SIGN, &CUserCenterDlg::OnBnClickedButtonLeagueSign)
    ON_WM_PAINT()
    ON_MESSAGE(WM_UPDATE_USER_CENTER, OnUpdateUserCenter)
END_MESSAGE_MAP()


LRESULT CUserCenterDlg::OnUpdateUserCenter(WPARAM wParam, LPARAM lParam)
{
    LPUserCenterInfo pUserCenterInfo = (LPUserCenterInfo)lParam;
    m_strMyAccount = pUserCenterInfo->szMyAccount;
    m_strMyCredie = pUserCenterInfo->szMyCredie;
    m_strWinCount = pUserCenterInfo->szWinCount;
    m_strEqualCount = pUserCenterInfo->szEqualCount;
    m_strLoseCount = pUserCenterInfo->szLoseCount;
    m_strWinPercentCount = pUserCenterInfo->szWinPercentCount;
    m_strTotalRank = pUserCenterInfo->szTotalRank;
    m_strGoalCount = pUserCenterInfo->szGoalCount;
    m_strLostCount = pUserCenterInfo->szLostCount;
    m_strRedCount = pUserCenterInfo->szRedCount;
    m_strYellowCount = pUserCenterInfo->szYellowCount;
    m_strNeedConfirmCount = pUserCenterInfo->szNeedConfirmCount;
    m_strNotConfirmCount = pUserCenterInfo->szNotConfirmCount;
    m_strLeagueWinCount = pUserCenterInfo->szLeagueWinCount;
    m_strLeagueEqualCount = pUserCenterInfo->szLeagueEqualCount;
    m_strLeagueLoseCount = pUserCenterInfo->szLeagueLoseCount;
    m_strLeagueWinPercentCount = pUserCenterInfo->szLeagueWinPercentCount;
    m_strLeagueRank = pUserCenterInfo->szLeagueRank;
    m_strLeagueMoney = pUserCenterInfo->szLeagueMoney;
    m_strLeagueTheFirst = pUserCenterInfo->szLeagueTheFirst;
    m_strLeagueTheEnd = pUserCenterInfo->szLeagueTheEnd;
    m_strLeaguePlayerCount = pUserCenterInfo->szLeaguePlayerCount;
    m_strLeagueInfo = pUserCenterInfo->szLeagueInfo;
    m_strLeagueSignCount = pUserCenterInfo->szLeagueSignCount;

    UpdateData(false);

    return 0;
}

// CUserCenterDlg message handlers

void CUserCenterDlg::OnBnClickedButtonLeagueDoing()
{
    if (m_isDefaultDlg)
    {
        SetWindowPos(NULL, 0, 0, m_rectLarge.Width(), m_rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
        m_isDefaultDlg = false;
    }
    else
    {
        SetWindowPos(NULL, 0, 0, m_rectSmall.Width(), m_rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
        m_isDefaultDlg = true;
    }
}


HBRUSH CUserCenterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    if (GetDlgItem(IDC_UC_FLAG)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0, 240));
    }
    else if (GetDlgItem(IDC_UC_TEXT_ACCOUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_CREDIE)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_WIN)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_EQUAL)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LOSE)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_WIN_PERCENT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_RANK)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_NEED_CONFIRM)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_NOT_CONFIRM)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_GOAL_COUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LOSE_COUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_RED_COUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_YELLOW_COUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_WIN)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_EQUAL)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_LOSE)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_WIN_PERCENT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_RANK)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_MONEY)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_THE_FIRST)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_THE_END)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_PLAYER_COUNT)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_LEAGUE_INFO)->m_hWnd == pWnd->m_hWnd || \
             GetDlgItem(IDC_UC_TEXT_SIGN_COUNT)->m_hWnd == pWnd->m_hWnd)
    {
        pDC->SetTextColor(RGB(0, 0,240));
    }

    // TODO:  Return a different brush if the default is not desired
    return hbr;
}

//
// 荣誉殿堂
//
void CUserCenterDlg::OnBnClickedButtonGlory()
{
    // TODO: Add your control notification handler code here
}

//
// 我的赛程
//
void CUserCenterDlg::OnBnClickedButtonCalendar()
{
    // TODO: Add your control notification handler code here
}

//
// 上报比分
//
void CUserCenterDlg::OnBnClickedButtonSubmitScore()
{
    // TODO: Add your control notification handler code here
    if (m_pDlgSubmitScore == NULL)
    {
        m_pDlgSubmitScore = new CSubmitScoreDlg();
        m_pDlgSubmitScore->Create(IDD_SUBMIT_SCORE_DIALOG);
    }
    m_pDlgSubmitScore->ShowWindow(SW_NORMAL);

}

//
// 确认比分
//
void CUserCenterDlg::OnBnClickedButtonAgreeScore()
{
    // TODO: Add your control notification handler code here
    if (m_pDlgAgreeScore == NULL)
    {
        m_pDlgAgreeScore = new CAgreeScoreDlg();
        m_pDlgAgreeScore->Create(IDD_AGREE_SCORE_DIALOG);
    }
    m_pDlgAgreeScore->ShowWindow(SW_NORMAL);
}

//
// 进入我的联赛
//
void CUserCenterDlg::OnBnClickedButtonEnterMyLeague()
{
    ShowLeagueInfoDlg();
}

//
// 查看其他联赛
//
void CUserCenterDlg::OnBnClickedButtonWatchLeague()
{
    ShowLeagueInfoDlg(false, false, true, true, true, true, true, false);
}

//
// 报名参加联赛
//
void CUserCenterDlg::OnBnClickedButtonLeagueSign()
{
    ShowLeagueInfoDlg(true, false, false, false, false, false, true, false);
}

//
// 显示联赛信息对话框
//
void CUserCenterDlg::ShowLeagueInfoDlg(bool isShowJoinButton,
                                       bool isShowMyTeam,
                                       bool isShowCalendar,
                                       bool isShowTeamRank,
                                       bool isShowGoalRank,
                                       bool isShowAssitantRank,
                                       bool isShowHonor,
                                       bool isShowMarket)
{
    if (m_pDlgLeagueSheet == NULL)
    {
        m_pDlgLeagueSheet           = new CPropertySheet(_T("联赛信息"));

        m_pDlgLeagueInfoPage        = new CLeagueInfoPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueInfoPage);
        m_pDlgLeagueInfoPage->m_psp.dwFlags &= ~(PSP_HASHELP);

        if (isShowMyTeam)
        {
            m_pDlgLeagueMyTeamPage = new CLeagueMyTeamPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueMyTeamPage);
            m_pDlgLeagueMyTeamPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowCalendar)
        {
            m_pDlgLeagueCalendarPage = new CLeagueCalendarPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueCalendarPage);
            m_pDlgLeagueCalendarPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowTeamRank)
        {
            m_pDlgLeagueTeamRankPage = new CLeagueTeamRankPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueTeamRankPage);
            m_pDlgLeagueTeamRankPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowGoalRank)
        {
            m_pDlgLeagueGoalPage = new CLeagueGoalPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueGoalPage);
            m_pDlgLeagueGoalPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowAssitantRank)
        {
            m_pDlgLeagueAssitantPage = new CLeagueAssitantPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueAssitantPage);
            m_pDlgLeagueAssitantPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowHonor)
        {
            m_pDlgLeagueHonorPage = new CLeagueHonorPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueHonorPage);
            m_pDlgLeagueHonorPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        if (isShowMarket)
        {
            m_pDlgLeagueMarketPage = new CLeagueMarketPage();
            m_pDlgLeagueSheet->AddPage(m_pDlgLeagueMarketPage);
            m_pDlgLeagueMarketPage->m_psp.dwFlags &= ~(PSP_HASHELP);
        }

        m_pDlgLeagueSheet->m_psh.dwFlags        |= PSH_NOAPPLYNOW;
        m_pDlgLeagueSheet->m_psh.dwFlags        &= ~(PSH_HASHELP);
    }

    m_pDlgLeagueInfoPage->ShowJoinButton(isShowJoinButton);

    if (!isShowMyTeam && m_pDlgLeagueMyTeamPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueMyTeamPage);
        delete m_pDlgLeagueMyTeamPage;
        m_pDlgLeagueMyTeamPage = NULL;
    }
    else if (isShowMyTeam && m_pDlgLeagueMyTeamPage == NULL)
    {
        m_pDlgLeagueMyTeamPage = new CLeagueMyTeamPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueMyTeamPage);
        m_pDlgLeagueMyTeamPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowCalendar && m_pDlgLeagueCalendarPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueCalendarPage);
        delete m_pDlgLeagueCalendarPage;
        m_pDlgLeagueCalendarPage = NULL;
    }
    else if (isShowCalendar && m_pDlgLeagueCalendarPage == NULL)
    {
        m_pDlgLeagueCalendarPage = new CLeagueCalendarPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueCalendarPage);
        m_pDlgLeagueCalendarPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowTeamRank && m_pDlgLeagueTeamRankPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueTeamRankPage);
        delete m_pDlgLeagueTeamRankPage;
        m_pDlgLeagueTeamRankPage = NULL;
    }
    else if (isShowTeamRank && m_pDlgLeagueTeamRankPage == NULL)
    {
        m_pDlgLeagueTeamRankPage = new CLeagueTeamRankPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueTeamRankPage);
        m_pDlgLeagueTeamRankPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowGoalRank && m_pDlgLeagueGoalPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueGoalPage);
        delete m_pDlgLeagueGoalPage;
        m_pDlgLeagueGoalPage = NULL;
    }
    else if (isShowGoalRank && m_pDlgLeagueGoalPage == NULL)
    {
        m_pDlgLeagueGoalPage = new CLeagueGoalPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueGoalPage);
        m_pDlgLeagueGoalPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowAssitantRank && m_pDlgLeagueAssitantPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueAssitantPage);
        delete m_pDlgLeagueAssitantPage;
        m_pDlgLeagueAssitantPage = NULL;
    }
    else if (isShowAssitantRank && m_pDlgLeagueAssitantPage == NULL)
    {
        m_pDlgLeagueAssitantPage = new CLeagueAssitantPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueAssitantPage);
        m_pDlgLeagueAssitantPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowHonor && m_pDlgLeagueHonorPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueHonorPage);
        delete m_pDlgLeagueHonorPage;
        m_pDlgLeagueHonorPage = NULL;
    }
    else if (isShowHonor && m_pDlgLeagueHonorPage == NULL)
    {
        m_pDlgLeagueHonorPage = new CLeagueHonorPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueHonorPage);
        m_pDlgLeagueHonorPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    if (!isShowMarket && m_pDlgLeagueMarketPage)
    {
        m_pDlgLeagueSheet->RemovePage(m_pDlgLeagueMarketPage);
        delete m_pDlgLeagueMarketPage;
        m_pDlgLeagueMarketPage = NULL;
    }
    else if (isShowMarket && m_pDlgLeagueMarketPage == NULL)
    {
        m_pDlgLeagueMarketPage = new CLeagueMarketPage();
        m_pDlgLeagueSheet->AddPage(m_pDlgLeagueMarketPage);
        m_pDlgLeagueMarketPage->m_psp.dwFlags &= ~(PSP_HASHELP);
    }

    m_pDlgLeagueSheet->DoModal();
}
BOOL CUserCenterDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    //
    // 获取整个对话框位置参数
    //
    GetWindowRect(&m_rectLarge);
    //
    // 获取登陆与注册分隔线的位置参数（有用的是right）
    //
    GetDlgItem(IDC_UC_SEPARATOR)->GetWindowRect(&m_rectSeparator);
    //
    // 保存登陆对话框位置参数
    //
    m_rectSmall.left   = m_rectLarge.left;
    m_rectSmall.top    = m_rectLarge.top;
    m_rectSmall.right  = m_rectSeparator.left;
    m_rectSmall.bottom = m_rectLarge.bottom;

    //
    // 默认显示登陆对话框
    //
    SetWindowPos(NULL, 0, 0, m_rectSmall.Width(), m_rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CUserCenterDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (m_isSyncData)
    {
        return;
    }

    CWaitingDlg::GetInstance()->PerformSelectorAndBeginWaitingDlg(this, _T("初始化数据..."), CSyncHandler::RequestUserCenterInfo, this);
    //
    // TODO 初始化测试数据
    //

    m_cmbJoinLeague.AddString(_T("第一届PES2011钻石联赛"));
    m_cmbJoinLeague.AddString(_T("第一届PES2011黄金联赛"));
    m_cmbJoinLeague.SetCurSel(1);

    m_cmbOtherLeague.AddString(_T("第一届PES2011大师联赛"));
    m_cmbOtherLeague.AddString(_T("第一届PES2011联SB赛"));
    m_cmbOtherLeague.SetCurSel(0);

    m_cmbSignLeague.AddString(_T("第二届PES2011黄金联赛"));
    m_cmbSignLeague.AddString(_T("第二届PES2011大师联赛"));
    m_cmbSignLeague.SetCurSel(1);

    

    m_isSyncData = true;
    // 不为绘图消息调用 CDialog::OnPaint()
}
