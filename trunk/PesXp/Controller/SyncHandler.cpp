#include "StdAfx.h"
#include "SyncHandler.h"
#include "WaitingDlg.h"

CSyncHandler::CSyncHandler(void)
{
    m_pUserItem = CUserItem::GetInstance();
}

CSyncHandler::~CSyncHandler(void)
{
}

//
// 用户登录
//
UINT32 CSyncHandler::Login(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;
    //
    // 请求服务器进行登录
    //
    Sleep(1000);

    return 0;
}

//
// 用户注册
//
UINT32 CSyncHandler::Register(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;
    //
    // 请求服务器进行注册
    //
    Sleep(5000);
    return 0;
}

//
// 获取用户中心信息
//
UINT32 CSyncHandler::RequestUserCenterInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;

    //
    // 请求用户基本数据
    //
    pWts->pWaitingDlg->m_textWaiting.SetWindowText(_T("获取用户信息..."));
    CSyncHandler::RequestUserInfo(pWts->pThreadFunParams);

    //
    // 请求联赛基本数据
    //
    pWts->pWaitingDlg->m_textWaiting.SetWindowText(_T("获取联赛信息..."));
    CSyncHandler::RequestLeagueInfo(pWts->pThreadFunParams);

    LPUserCenterInfo pUserCenterInfo = new UserCenterInfo();
    pUserCenterInfo->szMyAccount = _T("italyouxiao@gmail.com");
    pUserCenterInfo->szMyCredie = _T("3020");
    pUserCenterInfo->szWinCount = _T("86");
    pUserCenterInfo->szEqualCount = _T("22");
    pUserCenterInfo->szLoseCount = _T("12");
    pUserCenterInfo->szWinPercentCount = _T("76.53%");
    pUserCenterInfo->szTotalRank = _T("8");
    pUserCenterInfo->szGoalCount = _T("368");
    pUserCenterInfo->szLostCount = _T("135");
    pUserCenterInfo->szRedCount = _T("12");
    pUserCenterInfo->szYellowCount = _T("45");
    pUserCenterInfo->szNeedConfirmCount = _T("2");
    pUserCenterInfo->szNotConfirmCount = _T("3");
    pUserCenterInfo->szLeagueWinCount = _T("9");
    pUserCenterInfo->szLeagueEqualCount = _T("3");
    pUserCenterInfo->szLeagueLoseCount = _T("1");
    pUserCenterInfo->szLeagueWinPercentCount = _T("90.12%");
    pUserCenterInfo->szLeagueRank = _T("2");
    pUserCenterInfo->szLeagueMoney = _T("2541");
    pUserCenterInfo->szLeagueTheFirst = _T("AC米兰 - NesTa.xP");
    pUserCenterInfo->szLeagueTheEnd = _T("巴里 - YouXiao");
    pUserCenterInfo->szLeaguePlayerCount = _T("18");
    pUserCenterInfo->szLeagueInfo = _T("2011-03-28");
    pUserCenterInfo->szLeagueSignCount = _T("8");
    ::SendMessage(pWts->pParentDlg->m_hWnd, WM_UPDATE_USER_CENTER, 0, (LPARAM)pUserCenterInfo);

    return 0;
}

//
// 获取用户信息
//
UINT32 CSyncHandler::RequestUserInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // 请求服务器获取用户信息
    //
    Sleep(2000);

    return 0;
}
//
// 获取联赛信息
//
UINT32 CSyncHandler::RequestLeagueInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // 请求服务器获取联赛信息
    //
    Sleep(2000);

    return 0;
}
//
// 获取联赛详情
//
UINT32 CSyncHandler::RequestLeagueDetail(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // 请求服务器获取联赛详情
    //
    Sleep(5000);

    return 0;
}
//
// 获取荣誉殿堂信息
//
UINT32 CSyncHandler::RequestHonorInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // 请求服务器获取荣誉殿堂信息
    //
    Sleep(5000);

    return 0;
}
//
// 获取转会市场信息
//
UINT32 CSyncHandler::RequestMarketInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // 请求服务器获取转会市场信息
    //
    Sleep(5000);

    return 0;
}