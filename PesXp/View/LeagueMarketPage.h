#pragma once
#include "afxcmn.h"


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
public:
    CListCtrl m_listCtrl;
    virtual BOOL OnInitDialog();
    CListCtrl m_listCtrlMyTeam;
    afx_msg void OnBnClickedMarketButton();
};
