#pragma once


// CLeagueMarketPage 对话框

class CLeagueMarketPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueMarketPage)

public:
	CLeagueMarketPage();
	virtual ~CLeagueMarketPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_MARKET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
