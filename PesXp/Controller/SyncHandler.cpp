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
    Sleep(5000);

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
    Sleep(5000);

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