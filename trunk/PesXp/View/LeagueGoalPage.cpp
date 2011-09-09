// View\LeagueGoalPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueGoalPage.h"


// CLeagueGoalPage 对话框

IMPLEMENT_DYNAMIC(CLeagueGoalPage, CPropertyPage)

CLeagueGoalPage::CLeagueGoalPage()
	: CPropertyPage(CLeagueGoalPage::IDD)
{

}

CLeagueGoalPage::~CLeagueGoalPage()
{
}

void CLeagueGoalPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueGoalPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueGoalPage 消息处理程序
