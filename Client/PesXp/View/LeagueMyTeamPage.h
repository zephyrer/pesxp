#pragma once
#include "afxcmn.h"


// CLeagueMyTeamPage �Ի���

class CLeagueMyTeamPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CLeagueMyTeamPage)

public:
    CLeagueMyTeamPage();
    virtual ~CLeagueMyTeamPage();

// �Ի�������
    enum { IDD = IDD_LEAGUE_MY_TEAM_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_listCtrl;
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
