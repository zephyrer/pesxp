#pragma once
#include "afxcmn.h"


// CLeagueGoalPage 对话框

class CLeagueGoalPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueGoalPage)

public:
	CLeagueGoalPage();
	virtual ~CLeagueGoalPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_GOAL_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CListCtrl m_listCtrl;
};
