#pragma once


// CLeagueGoalPage �Ի���

class CLeagueGoalPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueGoalPage)

public:
	CLeagueGoalPage();
	virtual ~CLeagueGoalPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_GOAL_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
