#pragma once


// CLeagueCalendarPage �Ի���

class CLeagueCalendarPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueCalendarPage)

public:
	CLeagueCalendarPage();
	virtual ~CLeagueCalendarPage();

// �Ի�������
	enum { IDD = IDD_LEAGUE_CALENDAR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
