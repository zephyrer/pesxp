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
// �û���¼
//
UINT32 CSyncHandler::Login(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;
    //
    // ������������е�¼
    //
    Sleep(1000);

    return 0;
}

//
// �û�ע��
//
UINT32 CSyncHandler::Register(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;
    //
    // �������������ע��
    //
    Sleep(5000);
    return 0;
}

//
// ��ȡ�û�������Ϣ
//
UINT32 CSyncHandler::RequestUserCenterInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    LPWaitingDlgThreadStruct pWts = (LPWaitingDlgThreadStruct)params;
    LPUserLoginInfo pUserInfo = (LPUserLoginInfo)pWts->pThreadFunParams;

    //
    // �����û���������
    //
    pWts->pWaitingDlg->m_textWaiting.SetWindowText(_T("��ȡ�û���Ϣ..."));
    CSyncHandler::RequestUserInfo(pWts->pThreadFunParams);

    //
    // ����������������
    //
    pWts->pWaitingDlg->m_textWaiting.SetWindowText(_T("��ȡ������Ϣ..."));
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
    pUserCenterInfo->szLeagueTheFirst = _T("AC���� - NesTa.xP");
    pUserCenterInfo->szLeagueTheEnd = _T("���� - YouXiao");
    pUserCenterInfo->szLeaguePlayerCount = _T("18");
    pUserCenterInfo->szLeagueInfo = _T("2011-03-28");
    pUserCenterInfo->szLeagueSignCount = _T("8");
    ::SendMessage(pWts->pParentDlg->m_hWnd, WM_UPDATE_USER_CENTER, 0, (LPARAM)pUserCenterInfo);

    return 0;
}

//
// ��ȡ�û���Ϣ
//
UINT32 CSyncHandler::RequestUserInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // �����������ȡ�û���Ϣ
    //
    Sleep(2000);

    return 0;
}
//
// ��ȡ������Ϣ
//
UINT32 CSyncHandler::RequestLeagueInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // �����������ȡ������Ϣ
    //
    Sleep(2000);

    return 0;
}
//
// ��ȡ��������
//
UINT32 CSyncHandler::RequestLeagueDetail(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // �����������ȡ��������
    //
    Sleep(5000);

    return 0;
}
//
// ��ȡ����������Ϣ
//
UINT32 CSyncHandler::RequestHonorInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // �����������ȡ����������Ϣ
    //
    Sleep(5000);

    return 0;
}
//
// ��ȡת���г���Ϣ
//
UINT32 CSyncHandler::RequestMarketInfo(LPVOID params)
{
    if (params == NULL)
        return 1;

    //
    // �����������ȡת���г���Ϣ
    //
    Sleep(5000);

    return 0;
}