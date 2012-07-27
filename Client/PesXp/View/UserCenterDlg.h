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
    // ��ʾ������Ϣ�Ի���
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
    CRect               m_rectLarge;                // �����Ի���Ĵ�С
    CRect               m_rectSmall;                // Ĭ�϶Ի���Ĵ�С
    CRect               m_rectSeparator;            // ������Ĭ�϶Ի���ķָ���
    bool                m_isDefaultDlg;             // ��ǰ�Ƿ���ʾĬ�϶Ի���
    CSubmitScoreDlg     *m_pDlgSubmitScore;         // �ϱ��ȷֶԻ���
    CAgreeScoreDlg      *m_pDlgAgreeScore;          // ȷ�ϱȷֶԻ���
    CPropertySheet      *m_pDlgLeagueSheet;         // ������Ϣ�Ի���
    CLeagueInfoPage     *m_pDlgLeagueInfoPage;      // ����������Ϣ
    CLeagueCalendarPage *m_pDlgLeagueCalendarPage;  // ����������Ϣ
    CLeagueGoalPage     *m_pDlgLeagueGoalPage;      // �����������Ϣ
    CLeagueAssitantPage *m_pDlgLeagueAssitantPage;  // ������������Ϣ
    CLeagueMyTeamPage   *m_pDlgLeagueMyTeamPage;    // �����ҵ������Ϣ
    CLeagueTeamRankPage *m_pDlgLeagueTeamRankPage;  // ����������а���Ϣ
    CLeagueHonorPage    *m_pDlgLeagueHonorPage;     // ������ҫ�����Ϣ
    CLeagueMarketPage   *m_pDlgLeagueMarketPage;    // ����ת���г���Ϣ
    CUtilHandler        *m_pUtilHandler;             // ����������
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
    // �ҵ��˺�����
    CString m_strMyAccount;
    // �ҵĸ��˻���
    CString m_strMyCredie;
    // �����ܹ�ʤ������
    CString m_strWinCount;
    // �����ܹ�ƽ�ִ���
    CString m_strEqualCount;
    // �����ܹ�ʧ������
    CString m_strLoseCount;
    // ������ս��ʤ��
    CString m_strWinPercentCount;
    // ����ƽ̨������
    CString m_strTotalRank;
    // �����ܽ�����
    CString m_strGoalCount;
    // ������ʧ����
    CString m_strLostCount;
    // �����ܺ�����
    CString m_strRedCount;
    // �����ܻ�����
    CString m_strYellowCount;
    // �ȴ���ȷ�ϵıȷ�����
    CString m_strNeedConfirmCount;
    // �ȴ��Է�ȷ�ϵıȷ�����
    CString m_strNotConfirmCount;
    // ��������ʤ������
    CString m_strLeagueWinCount;
    // ��������ƽ�ִ���
    CString m_strLeagueEqualCount;
    // ��������ʧ������
    CString m_strLeagueLoseCount;
    // ��������ʤ��
    CString m_strLeagueWinPercentCount;
    // ������������
    CString m_strLeagueRank;
    // ���������ʲ�
    CString m_strLeagueMoney;
    // ������ͷ��
    CString m_strLeagueTheFirst;
    // �������೤
    CString m_strLeagueTheEnd;
    // ������������ͳ��
    CString m_strLeaguePlayerCount;
    // �����򵥽���
    CString m_strLeagueInfo;
    // �����ѱ�������
    CString m_strLeagueSignCount;
    // �Ҳ���������б�
    CComboBox m_cmbJoinLeague;
    // ���ڽ��е������б�
    CComboBox m_cmbOtherLeague;
    // ���ڱ���������
    CComboBox m_cmbSignLeague;
    // �Ƿ��Ѿ�ͬ������������
    bool m_isSyncData;
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
};