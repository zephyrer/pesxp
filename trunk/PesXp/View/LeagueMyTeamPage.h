#pragma once


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
};
