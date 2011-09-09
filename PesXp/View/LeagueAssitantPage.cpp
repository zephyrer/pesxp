// View\LeagueAssitantPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueAssitantPage.h"


// CLeagueAssitantPage 对话框

IMPLEMENT_DYNAMIC(CLeagueAssitantPage, CPropertyPage)

CLeagueAssitantPage::CLeagueAssitantPage()
	: CPropertyPage(CLeagueAssitantPage::IDD)
{

}

CLeagueAssitantPage::~CLeagueAssitantPage()
{
}

void CLeagueAssitantPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueAssitantPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueAssitantPage 消息处理程序
