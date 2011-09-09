#pragma once


// CLeagueAssitantPage 对话框

class CLeagueAssitantPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueAssitantPage)

public:
	CLeagueAssitantPage();
	virtual ~CLeagueAssitantPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_ASSITANT_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
