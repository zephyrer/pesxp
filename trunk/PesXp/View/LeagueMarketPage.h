#pragma once


// CLeagueMarketPage �Ի���

class CLeagueMarketPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueMarketPage)

public:
	CLeagueMarketPage();
	virtual ~CLeagueMarketPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_MARKET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
