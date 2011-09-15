#pragma once
#include "afxwin.h"
#include "UtilHandler.h"
#include "SubmitScoreDlg.h"
#include "AgreeScoreDlg.h"
#include "LeagueInfoPage.h"
#include "LeagueCalendarPage.h"
#include "LeagueAssitantPage.h"
#include "LeagueGoalPage.h"
#include "LeagueHonorPage.h"
#include "LeagueMyTeamPage.h"
#include "LeagueTeamRankPage.h"
#include "LeagueMarketPage.h"

// CUserCenterDlg dialog

class CUserCenterDlg : public CDialog
{
    DECLARE_DYNAMIC(CUserCenterDlg)

public:
    CUserCenterDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CUserCenterDlg();
    
    //
    // 显示联赛信息对话框
    //
    void ShowLeagueInfoDlg(bool isShowJoinButton = false,
                           bool isShowMyTeam = true,
                           bool isShowCalendar = true,
                           bool isShowTeamRank = true,
                           bool isShowGoalRank = true,
                           bool isShowAssitantRank = true,
                           bool isShowHonor = true,
                           bool isShowMarket = true);

// Dialog Data
    enum { IDD = IDD_USER_CENTER_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnUpdateUserCenter(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnBnClickedButtonLeagueDoing();

private:
    CRect               m_rectLarge;                // 完整对话框的大小
    CRect               m_rectSmall;                // 默认对话框的大小
    CRect               m_rectSeparator;            // 完整与默认对话框的分隔线
    bool                m_isDefaultDlg;             // 当前是否显示默认对话框
    CSubmitScoreDlg     *m_pDlgSubmitScore;         // 上报比分对话框
    CAgreeScoreDlg      *m_pDlgAgreeScore;          // 确认比分对话框
    CPropertySheet      *m_pDlgLeagueSheet;         // 联赛信息对话框
    CLeagueInfoPage     *m_pDlgLeagueInfoPage;      // 联赛基本信息
    CLeagueCalendarPage *m_pDlgLeagueCalendarPage;  // 联赛赛程信息
    CLeagueGoalPage     *m_pDlgLeagueGoalPage;      // 联赛进球榜信息
    CLeagueAssitantPage *m_pDlgLeagueAssitantPage;  // 联赛助攻榜信息
    CLeagueMyTeamPage   *m_pDlgLeagueMyTeamPage;    // 联赛我的球队信息
    CLeagueTeamRankPage *m_pDlgLeagueTeamRankPage;  // 联赛球队排行榜信息
    CLeagueHonorPage    *m_pDlgLeagueHonorPage;     // 联赛荣耀大殿信息
    CLeagueMarketPage   *m_pDlgLeagueMarketPage;    // 联赛转会市场信息
    CUtilHandler        *m_pUtilHandler;             // 公共函数类
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnBnClickedButtonGlory();
    afx_msg void OnBnClickedButtonCalendar();
    afx_msg void OnBnClickedButtonSubmitScore();
    afx_msg void OnBnClickedButtonAgreeScore();
    afx_msg void OnBnClickedButtonEnterMyLeague();
    afx_msg void OnBnClickedButtonWatchLeague();
    afx_msg void OnBnClickedButtonLeagueSign();
private:
    // 我的账号名称
    CString m_strMyAccount;
    // 我的个人积分
    CString m_strMyCredie;
    // 个人总共胜利次数
    CString m_strWinCount;
    // 个人总共平局次数
    CString m_strEqualCount;
    // 个人总共失利次数
    CString m_strLoseCount;
    // 个人总战绩胜率
    CString m_strWinPercentCount;
    // 个人平台总排名
    CString m_strTotalRank;
    // 个人总进球数
    CString m_strGoalCount;
    // 个人总失球数
    CString m_strLostCount;
    // 个人总红牌数
    CString m_strRedCount;
    // 个人总黄牌数
    CString m_strYellowCount;
    // 等待你确认的比分数量
    CString m_strNeedConfirmCount;
    // 等待对方确认的比分数量
    CString m_strNotConfirmCount;
    // 个人联赛胜利次数
    CString m_strLeagueWinCount;
    // 个人联赛平局次数
    CString m_strLeagueEqualCount;
    // 个人联赛失利次数
    CString m_strLeagueLoseCount;
    // 个人联赛胜率
    CString m_strLeagueWinPercentCount;
    // 个人联赛排名
    CString m_strLeagueRank;
    // 个人联赛资产
    CString m_strLeagueMoney;
    // 联赛领头羊
    CString m_strLeagueTheFirst;
    // 联赛副班长
    CString m_strLeagueTheEnd;
    // 联赛参赛人数统计
    CString m_strLeaguePlayerCount;
    // 联赛简单介绍
    CString m_strLeagueInfo;
    // 联赛已报名人数
    CString m_strLeagueSignCount;
    // 我参与的联赛列表
    CComboBox m_cmbJoinLeague;
    // 正在进行的联赛列表
    CComboBox m_cmbOtherLeague;
    // 正在报名的联赛
    CComboBox m_cmbSignLeague;
    // 是否已经同步服务器数据
    bool m_isSyncData;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
};
