#pragma once
#include "afxcmn.h"


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
public:
    virtual BOOL OnInitDialog();
    CListCtrl m_listCtrl;
};
