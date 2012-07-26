#pragma once
#include "afxcmn.h"


// CLeagueTeamRankPage 对话框

class CLeagueTeamRankPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueTeamRankPage)

public:
	CLeagueTeamRankPage();
	virtual ~CLeagueTeamRankPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_TEAM_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_listCtrl;
    virtual BOOL OnInitDialog();
};
