#pragma once


// CLeagueCalendarPage 对话框

class CLeagueCalendarPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLeagueCalendarPage)

public:
	CLeagueCalendarPage();
	virtual ~CLeagueCalendarPage();

// 对话框数据
	enum { IDD = IDD_LEAGUE_CALENDAR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
