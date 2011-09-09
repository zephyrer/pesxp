// View\LeagueMarketPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueMarketPage.h"


// CLeagueMarketPage 对话框

IMPLEMENT_DYNAMIC(CLeagueMarketPage, CPropertyPage)

CLeagueMarketPage::CLeagueMarketPage()
	: CPropertyPage(CLeagueMarketPage::IDD)
{

}

CLeagueMarketPage::~CLeagueMarketPage()
{
}

void CLeagueMarketPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueMarketPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueMarketPage 消息处理程序
