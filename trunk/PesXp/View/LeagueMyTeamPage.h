#pragma once


// CLeagueMyTeamPage 对话框

class CLeagueMyTeamPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueMyTeamPage)

public:
	CLeagueMyTeamPage();
	virtual ~CLeagueMyTeamPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_MY_TEAM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
