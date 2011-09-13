#pragma once
#include "afxcmn.h"


// CLeagueHonorPage 对话框

class CLeagueHonorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueHonorPage)

public:
	CLeagueHonorPage();
	virtual ~CLeagueHonorPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_HONOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CListCtrl m_listCtrl;
};
