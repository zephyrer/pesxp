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
    Sleep(5000);

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
    Sleep(5000);

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