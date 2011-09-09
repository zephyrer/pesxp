// View\LeagueHonorPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PesXp.h"
#include "View\LeagueHonorPage.h"


// CLeagueHonorPage 对话框

IMPLEMENT_DYNAMIC(CLeagueHonorPage, CPropertyPage)

CLeagueHonorPage::CLeagueHonorPage()
	: CPropertyPage(CLeagueHonorPage::IDD)
{

}

CLeagueHonorPage::~CLeagueHonorPage()
{
}

void CLeagueHonorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeagueHonorPage, CPropertyPage)
END_MESSAGE_MAP()


// CLeagueHonorPage 消息处理程序
