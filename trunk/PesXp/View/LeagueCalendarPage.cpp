// View\LeagueCalendarPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueCalendarPage.h"


// CLeagueCalendarPage 对话框

IMPLEMENT_DYNAMIC(CLeagueCalendarPage, CPropertyPage)

CLeagueCalendarPage::CLeagueCalendarPage()
	: CPropertyPage(CLeagueCalendarPage::IDD)
{

}

CLeagueCalendarPage::~CLeagueCalendarPage()
{
}

void CLeagueCalendarPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueCalendarPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueCalendarPage 消息处理程序
