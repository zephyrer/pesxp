#pragma once


// CLeagueAssitantPage �Ի���

class CLeagueAssitantPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueAssitantPage)

public:
	CLeagueAssitantPage();
	virtual ~CLeagueAssitantPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_ASSITANT_RANK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
