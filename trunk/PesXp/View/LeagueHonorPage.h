#pragma once


// CLeagueHonorPage �Ի���

class CLeagueHonorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueHonorPage)

public:
	CLeagueHonorPage();
	virtual ~CLeagueHonorPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_HONOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
