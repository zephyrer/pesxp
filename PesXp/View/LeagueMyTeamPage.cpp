// View\LeagueMyTeamPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueMyTeamPage.h"


// CLeagueMyTeamPage 对话框

IMPLEMENT_DYNAMIC(CLeagueMyTeamPage, CPropertyPage)

CLeagueMyTeamPage::CLeagueMyTeamPage()
	: CPropertyPage(CLeagueMyTeamPage::IDD)
{

}

CLeagueMyTeamPage::~CLeagueMyTeamPage()
{
}

void CLeagueMyTeamPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueMyTeamPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueMyTeamPage 消息处理程序
