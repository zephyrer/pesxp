#pragma once
#include "afxcmn.h"


// CLeagueTeamRankPage �Ի���

class CLeagueTeamRankPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueTeamRankPage)

public:
	CLeagueTeamRankPage();
	virtual ~CLeagueTeamRankPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_TEAM_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_listCtrl;
    virtual BOOL OnInitDialog();
};
