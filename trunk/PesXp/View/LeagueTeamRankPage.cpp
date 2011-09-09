// View\LeagueTeamRankPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueTeamRankPage.h"


// CLeagueTeamRankPage 对话框

IMPLEMENT_DYNAMIC(CLeagueTeamRankPage, CPropertyPage)

CLeagueTeamRankPage::CLeagueTeamRankPage()
	: CPropertyPage(CLeagueTeamRankPage::IDD)
{

}

CLeagueTeamRankPage::~CLeagueTeamRankPage()
{
}

void CLeagueTeamRankPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueTeamRankPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueTeamRankPage 消息处理程序
